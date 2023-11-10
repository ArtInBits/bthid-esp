#ifndef __LOGGING_H__
#define __LOGGING_H__

#include "esp_log.h"
#include "esp_err.h"
#define PDEBUG(fmt, ...) ESP_LOGD(__func__, "%s:%d - "fmt, __FILE__, __LINE__, ##__VA_ARGS__)
#define PINFO(fmt, ...) ESP_LOGI(__func__, "%s:%d - "fmt, __FILE__, __LINE__, ##__VA_ARGS__)
#define PWARN(fmt, ...) ESP_LOGW(__func__, "%s:%d - "fmt, __FILE__, __LINE__, ##__VA_ARGS__)
#define PERR(fmt, ...) ESP_LOGE(__func__, "%s:%d - "fmt, __FILE__, __LINE__, ##__VA_ARGS__)
#define HEXDUMP(buf, len) ESP_LOG_BUFFER_HEX_LEVEL(__func__, (buf), (len), ESP_LOG_INFO)

#endif //__LOGGING_H__

