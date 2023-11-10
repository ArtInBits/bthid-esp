
#ifndef __USBHID_H__
#define __USBHID_H__

#include "usb/hid_host.h"

struct repdesc {
    uint8_t *buf;
    size_t len;
};
#define NREPORTS 3

extern struct repdesc report_desc[NREPORTS];

typedef struct
{
    uint8_t data[12];
    int len;
} hid_report_t;

extern QueueHandle_t hid_report_queue;

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
                              void *arg);

/**
 * @brief HID Host main task
 *
 * Creates queue and get new event from the queue
 *
 * @param[in] pvParameters Not used
 */
void hid_host_task(void *pvParameters);

/**
 * @brief usb lib main task
 *
 * @param[in] pvParameters Not used
 */
void usb_lib_task(void *arg);

#endif //__USBHID_H__
