/*
 * SPDX-FileCopyrightText: 2022-2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Unlicense OR CC0-1.0
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "freertos/queue.h"
#include "esp_err.h"
#include "esp_log.h"
#include "usb/usb_host.h"
#include "errno.h"
#include "driver/gpio.h"

#include "usb/hid_usage_keyboard.h"
#include "usb/hid_usage_mouse.h"
#include "logging.h"
#include "usbhid.h"

QueueHandle_t hid_host_event_queue;
struct repdesc report_desc[NREPORTS] = {0};

/**
 * @brief HID Host event
 *
 * This event is used for delivering the HID Host event from callback to a task.
 */
typedef struct {
    hid_host_device_handle_t hid_device_handle;
    hid_host_driver_event_t event;
    void *arg;
} hid_host_event_queue_t;

/**
 * @brief USB HID Host Generic Interface report callback handler
 *
 * 'generic' means anything else than mouse or keyboard
 *
 * @param[in] data    Pointer to input report data buffer
 * @param[in] length  Length of input report data buffer
 */
static void hid_host_report_callback(const uint8_t *const data, const int length)
{
    /* Yanir: replace the print with a proper handler */
    hid_report_t report;
    memcpy(&report.data, data, length);
    report.len = length;
    xQueueSend(hid_report_queue, &report, 0);

    // ESP_LOG_BUFFER_HEX_LEVEL(__func__, data, length, ESP_LOG_INFO);
}

/**
 * @brief USB HID Host interface callback
 *
 * @param[in] hid_device_handle  HID Device handle
 * @param[in] event              HID Host interface event
 * @param[in] arg                Pointer to arguments, does not used
 */
void hid_host_interface_callback_cc(hid_host_device_handle_t hid_device_handle,
                                 const hid_host_interface_event_t event,
                                 void *arg)
{
    return;
}

/**
 * @brief USB HID Host interface callback
 *
 * @param[in] hid_device_handle  HID Device handle
 * @param[in] event              HID Host interface event
 * @param[in] arg                Pointer to arguments, does not used
 */
void hid_host_interface_callback_mouse(hid_host_device_handle_t hid_device_handle,
                                 const hid_host_interface_event_t event,
                                 void *arg)
{
    uint8_t data[64] = { 0 };
    size_t data_length = 0;
    hid_host_dev_params_t dev_params;
    ESP_ERROR_CHECK( hid_host_device_get_params(hid_device_handle, &dev_params));

    switch (event) {
    case HID_HOST_INTERFACE_EVENT_INPUT_REPORT:
        ESP_ERROR_CHECK( hid_host_device_get_raw_input_report_data(hid_device_handle,
                         data,
                         64,
                         &data_length));
        hid_host_report_callback(data, data_length);
        break;
    case HID_HOST_INTERFACE_EVENT_DISCONNECTED:
        ESP_ERROR_CHECK( hid_host_device_close(hid_device_handle) );
        break;
    case HID_HOST_INTERFACE_EVENT_TRANSFER_ERROR:
    default:
        PERR("HID Device, protocol %d Unhandled event %d", dev_params.proto, event);
        break;
    }
}

/**
 * @brief USB HID Host interface callback
 *
 * @param[in] hid_device_handle  HID Device handle
 * @param[in] event              HID Host interface event
 * @param[in] arg                Pointer to arguments, does not used
 */
void hid_host_interface_callback_kb(hid_host_device_handle_t hid_device_handle,
                                 const hid_host_interface_event_t event,
                                 void *arg)
{
    uint8_t data[64] = { 0 };
    size_t data_length = 0;
    data[0] = 1;
    hid_host_dev_params_t dev_params;
    ESP_ERROR_CHECK( hid_host_device_get_params(hid_device_handle, &dev_params));

    switch (event) {
    case HID_HOST_INTERFACE_EVENT_INPUT_REPORT:
        ESP_ERROR_CHECK( hid_host_device_get_raw_input_report_data(hid_device_handle,
                         data+1,
                         64,
                         &data_length));
        hid_host_report_callback(data, 1+data_length);
        break;
    case HID_HOST_INTERFACE_EVENT_DISCONNECTED:
        ESP_ERROR_CHECK( hid_host_device_close(hid_device_handle) );
        break;
    case HID_HOST_INTERFACE_EVENT_TRANSFER_ERROR:
    default:
        PERR("HID Device, protocol %d Unhandled event %d", dev_params.proto, event);
        break;
    }
}

/**
 * @brief USB HID Host Device event
 *
 * @param[in] hid_device_handle  HID Device handle
 * @param[in] event              HID Host Device event
 * @param[in] arg                Pointer to arguments, does not used
 */
void hid_host_device_event(hid_host_device_handle_t hid_device_handle,
                           const hid_host_driver_event_t event,
                           void *arg)
{
    int i;
    hid_host_dev_params_t dev_params;
    ESP_ERROR_CHECK( hid_host_device_get_params(hid_device_handle, &dev_params));

    switch (event) {
    case HID_HOST_DRIVER_EVENT_CONNECTED:
        PINFO("HID Device, protocol '%d' CONNECTED", dev_params.proto);
        if (dev_params.proto == HID_PROTOCOL_KEYBOARD) {
            const hid_host_device_config_t dev_config = {
                .callback = hid_host_interface_callback_kb,
                .callback_arg = NULL,
            };
            ESP_ERROR_CHECK( hid_host_device_open(hid_device_handle, &dev_config) );

        } else if(dev_params.proto == HID_PROTOCOL_MOUSE) {
            const hid_host_device_config_t dev_config = {
                .callback = hid_host_interface_callback_mouse,
                .callback_arg = NULL,
            };
            ESP_ERROR_CHECK( hid_host_device_open(hid_device_handle, &dev_config) );
        } else{
            const hid_host_device_config_t dev_config = {
                .callback = hid_host_interface_callback_cc,
                .callback_arg = NULL,
            };
            ESP_ERROR_CHECK( hid_host_device_open(hid_device_handle, &dev_config) );
        }
        if (HID_SUBCLASS_BOOT_INTERFACE == dev_params.sub_class) {
            ESP_ERROR_CHECK( hid_class_request_set_protocol(hid_device_handle, HID_REPORT_PROTOCOL_REPORT));
            if (HID_PROTOCOL_KEYBOARD == dev_params.proto) {
                ESP_ERROR_CHECK( hid_class_request_set_idle(hid_device_handle, 0, 0));
            }
        }
        for (i=0; i<NREPORTS; i++)
        {
            if(report_desc[i].len == 0)
                break;
        }
        report_desc[i].buf = hid_host_get_report_descriptor(hid_device_handle, &report_desc[i].len);
        PINFO("Yanir: report desc len = %u", report_desc[i].len);
        //HEXDUMP(report_desc[i].buf, report_desc[i].len);
        ESP_ERROR_CHECK( hid_host_device_start(hid_device_handle) );
        break;
    default:
        break;
    }
}

/**
 * @brief Start USB Host install and handle common USB host library events while app pin not low
 *
 * @param[in] arg  Not used
 */
void usb_lib_task(void *arg)
{
    const usb_host_config_t host_config = {
        .skip_phy_setup = false,
        .intr_flags = ESP_INTR_FLAG_LEVEL1,
    };

    ESP_ERROR_CHECK( usb_host_install(&host_config) );
    xTaskNotifyGive(arg);

    while (1) {
        uint32_t event_flags;
        usb_host_lib_handle_events(portMAX_DELAY, &event_flags);

        // Release devices once all clients has deregistered
        if (event_flags & USB_HOST_LIB_EVENT_FLAGS_NO_CLIENTS) {
            usb_host_device_free_all();
            PINFO("USB Event flags: NO_CLIENTS");
        }
        // All devices were removed
        if (event_flags & USB_HOST_LIB_EVENT_FLAGS_ALL_FREE) {
            PINFO("USB Event flags: ALL_FREE");
        }
    }
    // Clean up USB Host
    vTaskDelay(10); // Short delay to allow clients clean-up
    ESP_ERROR_CHECK( usb_host_uninstall());
    vTaskDelete(NULL);
}

/**
 * @brief HID Host main task
 *
 * Creates queue and get new event from the queue
 *
 * @param[in] pvParameters Not used
 */
void hid_host_task(void *pvParameters)
{
    hid_host_event_queue_t evt_queue;
    // Create queue
    hid_host_event_queue = xQueueCreate(10, sizeof(hid_host_event_queue_t));

    // Wait queue
    while (1) {
        if (xQueueReceive(hid_host_event_queue, &evt_queue, pdMS_TO_TICKS(50))) {
            hid_host_device_event(evt_queue.hid_device_handle,
                                  evt_queue.event,
                                  evt_queue.arg);
        }
    }

    xQueueReset(hid_host_event_queue);
    vQueueDelete(hid_host_event_queue);
    vTaskDelete(NULL);
}

/**
 * @brief HID Host Device callback
 *
 * Puts new HID Device event to the queue
 *
 * @param[in] hid_device_handle HID Device handle
 * @param[in] event             HID Device event
 * @param[in] arg               Not used
 */
void hid_host_device_callback(hid_host_device_handle_t hid_device_handle,
                              const hid_host_driver_event_t event,
                              void *arg)
{
    const hid_host_event_queue_t evt_queue = {
        .hid_device_handle = hid_device_handle,
        .event = event,
        .arg = arg
    };
    xQueueSend(hid_host_event_queue, &evt_queue, 0);
}
