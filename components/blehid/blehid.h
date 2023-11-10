
#ifndef __BLEHID_H__
#define __BLEHID_H__

#include <stdint.h>
/**
 * @brief ble control task
 *
 * Creates queue and get new events from the queue
 *
 * @param[in] pvParameters Not used
 */
void ble_ctl_task(void *pvParameters);

/**
 * @brief manage clients.
 *
 * add a connected central to the list of served clients
 *
 * @param[in] pvParameters mac address of the client
 */
void blehid_add_client(uint8_t addr[]);

/**
 * @brief manage clients.
 *
 * remove a connected central to the list of served clients
 *
 * @param[in] pvParameters mac address of the client
 */
void blehid_rm_client(uint8_t addr[]);

extern QueueHandle_t hid_report_queue;

#endif //__BLEHID_H__
