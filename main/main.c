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
#include "nvs_flash.h"
#include "usb/hid_host.h"
#include "usb/hid_usage_keyboard.h"
#include "usb/hid_usage_mouse.h"
#include "logging.h"
#include "usbhid.h"
#include "blehid.h"

QueueHandle_t hid_report_queue;


void hid_report_handler_task(void *pvParameters)
{
    hid_report_t report;
    while (1) {
        if (xQueueReceive(hid_report_queue, &report, pdMS_TO_TICKS(50))) {
            //Yanir: fix the loop to respond to user_shutdown
//            HEXDUMP(report.data, report.len);
        }
    }

    xQueueReset(hid_report_queue);
    vQueueDelete(hid_report_queue);
    vTaskDelete(NULL);
}




void app_main(void)
{
    BaseType_t task_created;
   
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK( ret );

    /*
    * Create usb_lib_task to:
    * - initialize USB Host library
    * - Handle USB Host events while APP pin in in HIGH state
    */
    task_created = xTaskCreatePinnedToCore(usb_lib_task,
                                           "usb_events",
                                           4096,
                                           xTaskGetCurrentTaskHandle(),
                                           2, NULL, 0);
    assert(task_created == pdTRUE);

    // Wait for notification from usb_lib_task to proceed
    ulTaskNotifyTake(false, 1000);

    /*
    * HID host driver configuration
    * - create background task for handling low level event inside the HID driver
    * - provide the device callback to get new HID Device connection event
    */
    const hid_host_driver_config_t hid_host_driver_config = {
        .create_background_task = true,
        .task_priority = 5,
        .stack_size = 4096,
        .core_id = 0,
        .callback = hid_host_device_callback,
        .callback_arg = NULL
    };

    ESP_ERROR_CHECK( hid_host_install(&hid_host_driver_config) );

    /* create a queue for the hid reports*/
    hid_report_queue = xQueueCreate(10, sizeof(hid_report_t));

    /*
    * Create HID Host task process for handle events
    * IMPORTANT: Task is necessary here while there is no possibility to interact
    * with USB device from the callback.
    */
    task_created = xTaskCreate(&hid_host_task, "hid_task", 4 * 1024, xTaskGetCurrentTaskHandle(), 2, NULL);
    assert(task_created == pdTRUE);
    // Wait for notification from usb_lib_task to proceed
    ulTaskNotifyTake(false, 1000);

    /* create the BLE control task */
    task_created = xTaskCreatePinnedToCore(ble_ctl_task,
                                           "BLE_ctl",
                                           4096,
                                           NULL,
                                           2, NULL, 1);
    assert(task_created == pdTRUE);
}
