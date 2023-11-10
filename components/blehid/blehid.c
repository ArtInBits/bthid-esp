
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_bt.h"
#include "esp_bt_defs.h"
#include "freertos/queue.h"
#include "esp_gap_ble_api.h"
#include "esp_gatts_api.h"
#include "esp_gatt_defs.h"

#include "esp_bt_main.h"
#include "esp_bt_device.h"

#include "esp_hidd.h"
#include "esp_hid_gap.h"

#include "logging.h"
#include "usbhid.h"
#include "blehid.h"
#include "blehiddata.h"

static esp_hidd_dev_t *s_hid_dev = NULL;

static void blehid_next_cli(esp_hidd_dev_t *dev)
{
    esp_hidd_dev_next_client(dev);
}

static void blehid_prev_cli(esp_hidd_dev_t *dev)
{
    esp_hidd_dev_prev_client(dev);
}

static void blehid_select_cli(esp_hidd_dev_t *dev, int idx)
{
    esp_hidd_dev_select_client(dev, idx);
}

static int filter_hotkey(hid_report_t *report)
{
    static int s_state = 0;
    if (s_state != 0) {
        /*
            we got a hot key, do nothing until the person leaves all keys
            or until he presses a different key to return to typing
        */
        uint8_t zbuf[15] = {0};
        zbuf[0] = 1;
        if (memcmp(zbuf, report->data, report->len))
            return 1;
        //send an empty keyboard before switching
        esp_hidd_dev_input_set(s_hid_dev, 0, report->data[0],report->data+1, report->len-1);
        if (s_state == 1) {
            blehid_next_cli(s_hid_dev);
        } else {
            blehid_prev_cli(s_hid_dev);
        }
        s_state = 0;
        return 1;
    }

    if ( report->data[1] == 0x07) { //ctrl+alt+shift
        switch(report->data[3])
        {
            case 0x50: //<-
                s_state = -1;
                break;
            case 0x4f: //->
                s_state = 1;
                break;
            case 0: //that is when we leave a key
                break;
            default: //that is for cancelling. if we hold ctrl+alt+shift and press an arrow, but want to revert, we press another key and leave everything
                s_state = 0;
                break;
        }
        return 1;
    }
    return 0;
}

static void hid_input_handler(hid_report_t *report)
{
    esp_err_t ret;
    HEXDUMP(report->data, report->len);
    switch(report->data[0] ) {
        case 1:
            if (0 != filter_hotkey(report))
                return;
        default:
            break;
    }
    ret = esp_hidd_dev_input_set(s_hid_dev, 0, report->data[0],report->data+1, report->len-1);
    if (ret != 0) {
        PERR("send report returned %d", ret);
    }
    
}

static void ble_hidd_event_callback(void *handler_args, esp_event_base_t base, int32_t id, void *event_data)
{
    esp_hidd_event_t event = (esp_hidd_event_t)id;
    esp_hidd_event_data_t *param = (esp_hidd_event_data_t *)event_data;
    PINFO(">> entering");
    switch (event) {
    case ESP_HIDD_START_EVENT: {
        PINFO("START");
        esp_hid_ble_gap_adv_start();
        break;
    }
    case ESP_HIDD_CONNECT_EVENT: {
        PINFO("CONNECT");
        break;
    }
    case ESP_HIDD_PROTOCOL_MODE_EVENT: {
        PINFO("PROTOCOL MODE[%u]: %s", param->protocol_mode.map_index, param->protocol_mode.protocol_mode ? "REPORT" : "BOOT");
        break;
    }
    case ESP_HIDD_CONTROL_EVENT: {
        PINFO("CONTROL[%u]: %sSUSPEND", param->control.map_index, param->control.control ? "EXIT_" : "");
        break;
    }
    case ESP_HIDD_OUTPUT_EVENT: {
        PINFO("OUTPUT[%u]: %8s ID: %2u, Len: %d, Data:", param->output.map_index, esp_hid_usage_str(param->output.usage), param->output.report_id, param->output.length);
        HEXDUMP(param->output.data, param->output.length);
        break;
    }
    case ESP_HIDD_FEATURE_EVENT: {
        PINFO("FEATURE[%u]: %8s ID: %2u, Len: %d, Data:", param->feature.map_index, esp_hid_usage_str(param->feature.usage), param->feature.report_id, param->feature.length);
        HEXDUMP(param->feature.data, param->feature.length);
        break;
    }
    case ESP_HIDD_DISCONNECT_EVENT: {
        PINFO("DISCONNECT: %s", esp_hid_disconnect_reason_str(esp_hidd_dev_transport_get(param->disconnect.dev), param->disconnect.reason));
        esp_hid_ble_gap_adv_start();
        break;
    }
    case ESP_HIDD_STOP_EVENT: {
        PINFO("STOP");
        break;
    }
    default:
        PINFO("event %d.", event);
        break;
    }
    PINFO("<< exiting");
    return;
}

static void init_ble_hid(void)
{
    esp_err_t ret;

    PINFO("setting hid gap, mode:%d", HID_DEV_MODE);
    ret = esp_hid_gap_init(HID_DEV_MODE);
    ESP_ERROR_CHECK( ret );

    ret = esp_hid_ble_gap_adv_init(ESP_HID_APPEARANCE_GENERIC, ble_hid_config.device_name);
    ESP_ERROR_CHECK( ret );

    if ((ret = esp_ble_gatts_register_callback(esp_hidd_gatts_event_handler)) != ESP_OK) {
        PERR("GATTS register callback failed: %d", ret);
        return;
    }
    PINFO("setting ble device");
    ESP_ERROR_CHECK(
        esp_hidd_dev_init(&ble_hid_config, ESP_HID_TRANSPORT_BLE, ble_hidd_event_callback, &s_hid_dev));
}

/**
 * @brief ble control task
 *
 * Creates queue and get new events from the queue
 *
 * @param[in] pvParameters Not used
 */
void ble_ctl_task(void *pvParameters)
{
    hid_report_t report;
    init_ble_hid();
    while (1) {
        if (xQueueReceive(hid_report_queue, &report, pdMS_TO_TICKS(50))) {
            //Yanir: fix the loop to respond to user_shutdown
            hid_input_handler(&report);
        }
    }

    xQueueReset(hid_report_queue);
    vQueueDelete(hid_report_queue);
    vTaskDelete(NULL);
}

