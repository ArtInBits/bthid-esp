
#include "blehiddata.h"

const unsigned char ComboReportMap[] = {
    0x05, 0x01,                    // Usage Page (Generic Desktop)        0
    0x09, 0x06,                    // Usage (Keyboard)                    2
    0xa1, 0x01,                    // Collection (Application)            4
    0x85, 0x01,                    //  Report ID (1)                      <<<< this is patched to provide report id for the keyboard
    0x05, 0x08,                    //  Usage Page (LEDs)                  6
    0x19, 0x01,                    //  Usage Minimum (1)                  8
    0x29, 0x03,                    //  Usage Maximum (3)                  10
    0x15, 0x00,                    //  Logical Minimum (0)                12
    0x25, 0x01,                    //  Logical Maximum (1)                14
    0x75, 0x01,                    //  Report Size (1)                    16
    0x95, 0x03,                    //  Report Count (3)                   18
    0x91, 0x02,                    //  Output (Data,Var,Abs)              20
    0x95, 0x05,                    //  Report Count (5)                   22
    0x91, 0x01,                    //  Output (Cnst,Arr,Abs)              24
    0x05, 0x07,                    //  Usage Page (Keyboard)              26
    0x1a, 0xe0, 0x00,              //  Usage Minimum (224)                28
    0x2a, 0xe7, 0x00,              //  Usage Maximum (231)                31
    0x95, 0x08,                    //  Report Count (8)                   34
    0x81, 0x02,                    //  Input (Data,Var,Abs)               36
    0x75, 0x08,                    //  Report Size (8)                    38
    0x95, 0x01,                    //  Report Count (1)                   40
    0x81, 0x01,                    //  Input (Cnst,Arr,Abs)               42
    0x19, 0x00,                    //  Usage Minimum (0)                  44
    0x2a, 0x91, 0x00,              //  Usage Maximum (145)                46
    0x26, 0xff, 0x00,              //  Logical Maximum (255)              49
    0x95, 0x06,                    //  Report Count (6)                   52
    0x81, 0x00,                    //  Input (Data,Arr,Abs)               54
    0xc0,                          // End Collection                      56
//};

//const unsigned char MouseReportMap[] = {
    0x05, 0x01,        // Usage Page (Generic Desktop Ctrls)
    0x09, 0x02,        // Usage (Mouse)
    0xA1, 0x01,        // Collection (Application)
    0x05, 0x01,        //   Usage Page (Generic Desktop Ctrls)
    0x09, 0x02,        //   Usage (Mouse)
    0xA1, 0x02,        //   Collection (Logical)
    0x85, 0x1A,        //     Report ID (26)
    0x09, 0x01,        //     Usage (Pointer)
    0xA1, 0x00,        //     Collection (Physical)
    0x05, 0x09,        //       Usage Page (Button)
    0x19, 0x01,        //       Usage Minimum (0x01)
    0x29, 0x05,        //       Usage Maximum (0x05)
    0x95, 0x05,        //       Report Count (5)
    0x75, 0x01,        //       Report Size (1)
    0x15, 0x00,        //       Logical Minimum (0)
    0x25, 0x01,        //       Logical Maximum (1)
    0x81, 0x02,        //       Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x75, 0x03,        //       Report Size (3)
    0x95, 0x01,        //       Report Count (1)
    0x81, 0x01,        //       Input (Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x05, 0x01,        //       Usage Page (Generic Desktop Ctrls)
    0x09, 0x30,        //       Usage (X)
    0x09, 0x31,        //       Usage (Y)
    0x95, 0x02,        //       Report Count (2)
    0x75, 0x10,        //       Report Size (16)
    0x16, 0x01, 0x80,  //       Logical Minimum (-32767)
    0x26, 0xFF, 0x7F,  //       Logical Maximum (32767)
    0x81, 0x06,        //       Input (Data,Var,Rel,No Wrap,Linear,Preferred State,No Null Position)
    0xA1, 0x02,        //       Collection (Logical)
//    0x85, 0x12,        //         Report ID (18)
    0x09, 0x48,        //         Usage (0x48)
    0x95, 0x01,        //         Report Count (1)
    0x75, 0x02,        //         Report Size (2)
    0x15, 0x00,        //         Logical Minimum (0)
    0x25, 0x01,        //         Logical Maximum (1)
    0x35, 0x01,        //         Physical Minimum (1)
    0x45, 0x10,        //         Physical Maximum (16)
    0xB1, 0x02,        //         Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
//    0x85, 0x1A,        //         Report ID (26)
    0x09, 0x38,        //         Usage (Wheel)
    0x35, 0x00,        //         Physical Minimum (0)
    0x45, 0x00,        //         Physical Maximum (0)
    0x95, 0x01,        //         Report Count (1)
    0x75, 0x10,        //         Report Size (16)
    0x16, 0x01, 0x80,  //         Logical Minimum (-32767)
    0x26, 0xFF, 0x7F,  //         Logical Maximum (32767)
    0x81, 0x06,        //         Input (Data,Var,Rel,No Wrap,Linear,Preferred State,No Null Position)
    0xC0,              //       End Collection
    0xA1, 0x02,        //       Collection (Logical)
//    0x85, 0x12,        //         Report ID (18)
    0x09, 0x48,        //         Usage (0x48)
    0x75, 0x02,        //         Report Size (2)
    0x15, 0x00,        //         Logical Minimum (0)
    0x25, 0x01,        //         Logical Maximum (1)
    0x35, 0x01,        //         Physical Minimum (1)
    0x45, 0x10,        //         Physical Maximum (16)
    0xB1, 0x02,        //         Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0x35, 0x00,        //         Physical Minimum (0)
    0x45, 0x00,        //         Physical Maximum (0)
    0x75, 0x04,        //         Report Size (4)
    0xB1, 0x01,        //         Feature (Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
//    0x85, 0x1A,        //         Report ID (26)
    0x05, 0x0C,        //         Usage Page (Consumer)
    0x95, 0x01,        //         Report Count (1)
    0x75, 0x10,        //         Report Size (16)
    0x16, 0x01, 0x80,  //         Logical Minimum (-32767)
    0x26, 0xFF, 0x7F,  //         Logical Maximum (32767)
    0x0A, 0x38, 0x02,  //         Usage (AC Pan)
    0x81, 0x06,        //         Input (Data,Var,Rel,No Wrap,Linear,Preferred State,No Null Position)
    0xC0,              //       End Collection
    0xC0,              //     End Collection
    0xC0,              //   End Collection
    0xC0,              // End Collection
    0x05, 0x0C,        // Usage Page (Consumer)
    0x09, 0x01,        // Usage (Consumer Control)
    0xA1, 0x01,        // Collection (Application)
    0x05, 0x01,        //   Usage Page (Generic Desktop Ctrls)
    0x09, 0x02,        //   Usage (Mouse)
    0xA1, 0x02,        //   Collection (Logical)
    0x85, 0x1F,        //     Report ID (31)
    0x05, 0x0C,        //     Usage Page (Consumer)
    0x0A, 0x38, 0x02,  //     Usage (AC Pan)
    0x95, 0x01,        //     Report Count (1)
    0x75, 0x10,        //     Report Size (16)
    0x16, 0x01, 0x80,  //     Logical Minimum (-32767)
    0x26, 0xFF, 0x7F,  //     Logical Maximum (32767)
    0x81, 0x06,        //     Input (Data,Var,Rel,No Wrap,Linear,Preferred State,No Null Position)
    0x85, 0x17,        //     Report ID (23)
    0x06, 0x00, 0xFF,  //     Usage Page (Vendor Defined 0xFF00)
    0x0A, 0x06, 0xFF,  //     Usage (0xFF06)
    0x0A, 0x0F, 0xFF,  //     Usage (0xFF0F)
    0x15, 0x00,        //     Logical Minimum (0)
    0x25, 0x01,        //     Logical Maximum (1)
    0x35, 0x01,        //     Physical Minimum (1)
    0x45, 0x10,        //     Physical Maximum (16)
    0x95, 0x02,        //     Report Count (2)
    0x75, 0x02,        //     Report Size (2)
    0xB1, 0x02,        //     Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0x0A, 0x04, 0xFF,  //     Usage (0xFF04)
    0x35, 0x00,        //     Physical Minimum (0)
    0x45, 0x00,        //     Physical Maximum (0)
    0x95, 0x01,        //     Report Count (1)
    0x75, 0x01,        //     Report Size (1)
    0xB1, 0x02,        //     Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0x75, 0x03,        //     Report Size (3)
    0xB1, 0x01,        //     Feature (Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0xC0,              //   End Collection
    0x85, 0x16,        //   Report ID (22)
    0x05, 0x0C,        //   Usage Page (Consumer)
    0x19, 0x00,        //   Usage Minimum (Unassigned)
    0x2A, 0xFF, 0x03,  //   Usage Maximum (0x03FF)
    0x95, 0x01,        //   Report Count (1)
    0x75, 0x10,        //   Report Size (16)
    0x15, 0x00,        //   Logical Minimum (0)
    0x26, 0xFF, 0x03,  //   Logical Maximum (1023)
    0x81, 0x00,        //   Input (Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x06, 0x00, 0xFF,  //   Usage Page (Vendor Defined 0xFF00)
    0x1A, 0x01, 0xFD,  //   Usage Minimum (0xFD01)
    0x2A, 0xFF, 0xFD,  //   Usage Maximum (0xFDFF)
    0x15, 0x01,        //   Logical Minimum (1)
    0x26, 0xFF, 0x00,  //   Logical Maximum (255)
    0x75, 0x08,        //   Report Size (8)
    0x81, 0x00,        //   Input (Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x81, 0x01,        //   Input (Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x85, 0x1C,        //   Report ID (28)
    0x06, 0x00, 0xFF,  //   Usage Page (Vendor Defined 0xFF00)
    0x0A, 0x25, 0xFF,  //   Usage (0xFF25)
    0x15, 0x00,        //   Logical Minimum (0)
    0x25, 0x04,        //   Logical Maximum (4)
    0x75, 0x08,        //   Report Size (8)
    0x95, 0x01,        //   Report Count (1)
    0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x0A, 0x26, 0xFF,  //   Usage (0xFF26)
    0x75, 0x10,        //   Report Size (16)
    0x15, 0x00,        //   Logical Minimum (0)
    0x27, 0xFF, 0xFF, 0x00, 0x00,  //   Logical Maximum (65534)
    0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0xC0,              // End Collection
};

const unsigned char ConsumerDevReportMap[] = {
    0x05, 0x0C,        // Usage Page (Consumer)
    0x09, 0x01,        // Usage (Consumer Control)
    0xA1, 0x01,        // Collection (Application)
    0x85, 0x20,        //   Report ID (32)
    0x06, 0x00, 0xFF,  //   Usage Page (Vendor Defined 0xFF00)
    0x15, 0x00,        //   Logical Minimum (0)
    0x26, 0xFF, 0x00,  //   Logical Maximum (255)
    0x75, 0x08,        //   Report Size (8)
    0x95, 0x12,        //   Report Count (18)
    0x0A, 0x0A, 0xFA,  //   Usage (0xFA0A)
    0xB1, 0x02,        //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0x85, 0x21,        //   Report ID (33)
    0x06, 0x00, 0xFF,  //   Usage Page (Vendor Defined 0xFF00)
    0x15, 0x00,        //   Logical Minimum (0)
    0x25, 0x01,        //   Logical Maximum (1)
    0x75, 0x01,        //   Report Size (1)
    0x95, 0x10,        //   Report Count (16)
    0x1A, 0x10, 0xFA,  //   Usage Minimum (0xFA10)
    0x2A, 0x1F, 0xFA,  //   Usage Maximum (0xFA1F)
    0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x85, 0x28,        //   Report ID (40)
    0x06, 0x00, 0xFF,  //   Usage Page (Vendor Defined 0xFF00)
    0x1A, 0x10, 0xFA,  //   Usage Minimum (0xFA10)
    0x2A, 0x1F, 0xFA,  //   Usage Maximum (0xFA1F)
    0xB1, 0x02,        //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0x85, 0x22,        //   Report ID (34)
    0x06, 0x00, 0xFF,  //   Usage Page (Vendor Defined 0xFF00)
    0x15, 0x00,        //   Logical Minimum (0)
    0x26, 0xFF, 0x00,  //   Logical Maximum (255)
    0x75, 0x08,        //   Report Size (8)
    0x95, 0x1A,        //   Report Count (26)
    0x0A, 0x0A, 0xFA,  //   Usage (0xFA0A)
    0xB1, 0x02,        //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0x85, 0x23,        //   Report ID (35)
    0x06, 0x00, 0xFF,  //   Usage Page (Vendor Defined 0xFF00)
    0x0A, 0x0A, 0xFA,  //   Usage (0xFA0A)
    0xB1, 0x02,        //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0x85, 0x24,        //   Report ID (36)
    0x06, 0x00, 0xFF,  //   Usage Page (Vendor Defined 0xFF00)
    0x95, 0x1F,        //   Report Count (31)
    0x0A, 0x0A, 0xFA,  //   Usage (0xFA0A)
    0xB1, 0x02,        //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0x85, 0x25,        //   Report ID (37)
    0x06, 0x00, 0xFF,  //   Usage Page (Vendor Defined 0xFF00)
    0x0A, 0x0A, 0xFA,  //   Usage (0xFA0A)
    0xB1, 0x02,        //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0x85, 0x26,        //   Report ID (38)
    0x06, 0x00, 0xFF,  //   Usage Page (Vendor Defined 0xFF00)
    0x0A, 0x0A, 0xFA,  //   Usage (0xFA0A)
    0xB1, 0x02,        //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0x85, 0x27,        //   Report ID (39)
    0x06, 0x00, 0xFF,  //   Usage Page (Vendor Defined 0xFF00)
    0x0A, 0x0A, 0xFA,  //   Usage (0xFA0A)
    0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x85, 0x14,        //   Report ID (20)
    0x06, 0x00, 0xFF,  //   Usage Page (Vendor Defined 0xFF00)
    0x15, 0x00,        //   Logical Minimum (0)
    0x25, 0x03,        //   Logical Maximum (3)
    0x75, 0x02,        //   Report Size (2)
    0x95, 0x01,        //   Report Count (1)
    0x0A, 0x01, 0xFE,  //   Usage (0xFE01)
    0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x75, 0x06,        //   Report Size (6)
    0x81, 0x01,        //   Input (Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x85, 0x04,        //   Report ID (4)
    0x06, 0x00, 0xFF,  //   Usage Page (Vendor Defined 0xFF00)
    0x15, 0x00,        //   Logical Minimum (0)
    0x25, 0x03,        //   Logical Maximum (3)
    0x75, 0x02,        //   Report Size (2)
    0x95, 0x01,        //   Report Count (1)
    0x0A, 0x01, 0xFE,  //   Usage (0xFE01)
    0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x75, 0x06,        //   Report Size (6)
    0x81, 0x01,        //   Input (Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0xC0,              // End Collection
    0x05, 0x0C,        // Usage Page (Consumer)
    0x09, 0x01,        // Usage (Consumer Control)
    0xA1, 0x01,        // Collection (Application)
    0x85, 0x07,        //   Report ID (7)
    0x05, 0x0C,        //   Usage Page (Consumer)
    0x19, 0x00,        //   Usage Minimum (Unassigned)
    0x2A, 0xFF, 0x03,  //   Usage Maximum (0x03FF)
    0x95, 0x01,        //   Report Count (1)
    0x75, 0x10,        //   Report Size (16)
    0x15, 0x00,        //   Logical Minimum (0)
    0x26, 0xFF, 0x03,  //   Logical Maximum (1023)
    0x81, 0x00,        //   Input (Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x05, 0x07,        //   Usage Page (Kbrd/Keypad)
    0x19, 0x00,        //   Usage Minimum (0x00)
    0x29, 0xFF,        //   Usage Maximum (0xFF)
    0x75, 0x08,        //   Report Size (8)
    0x26, 0xFF, 0x00,  //   Logical Maximum (255)
    0x81, 0x00,        //   Input (Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x81, 0x01,        //   Input (Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x06, 0x00, 0xFF,  //   Usage Page (Vendor Defined 0xFF00)
    0x0A, 0x03, 0xFE,  //   Usage (0xFE03)
    0x0A, 0x04, 0xFE,  //   Usage (0xFE04)
    0x75, 0x01,        //   Report Size (1)
    0x95, 0x02,        //   Report Count (2)
    0x25, 0x01,        //   Logical Maximum (1)
    0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x0A, 0x05, 0xFF,  //   Usage (0xFF05)
    0x95, 0x01,        //   Report Count (1)
    0x75, 0x05,        //   Report Size (5)
    0x25, 0x1F,        //   Logical Maximum (31)
    0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x75, 0x01,        //   Report Size (1)
    0x81, 0x01,        //   Input (Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x1A, 0x01, 0xFD,  //   Usage Minimum (0xFD01)
    0x2A, 0xFF, 0xFD,  //   Usage Maximum (0xFDFF)
    0x15, 0x01,        //   Logical Minimum (1)
    0x26, 0xFF, 0x00,  //   Logical Maximum (255)
    0x75, 0x08,        //   Report Size (8)
    0x81, 0x00,        //   Input (Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x0A, 0x02, 0xFF,  //   Usage (0xFF02)
    0x26, 0xFF, 0x00,  //   Logical Maximum (255)
    0x15, 0x00,        //   Logical Minimum (0)
    0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0xC0,              // End Collection
    0x06, 0xBC, 0xFF,  // Usage Page (Vendor Defined 0xFFBC)
    0x09, 0x88,        // Usage (0x88)
    0xA1, 0x01,        // Collection (Application)
    0x85, 0x08,        //   Report ID (8)
    0x19, 0x01,        //   Usage Minimum (0x01)
    0x29, 0xFF,        //   Usage Maximum (0xFF)
    0x15, 0x01,        //   Logical Minimum (1)
    0x26, 0xFF, 0x00,  //   Logical Maximum (255)
    0x95, 0x01,        //   Report Count (1)
    0x75, 0x08,        //   Report Size (8)
    0x81, 0x00,        //   Input (Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0xC0,              // End Collection
    0x05, 0x01,        // Usage Page (Generic Desktop Ctrls)
    0x09, 0x80,        // Usage (Sys Control)
    0xA1, 0x01,        // Collection (Application)
    0x85, 0x03,        //   Report ID (3)
    0x19, 0x00,        //   Usage Minimum (Undefined)
    0x29, 0xFF,        //   Usage Maximum (0xFF)
    0x15, 0x00,        //   Logical Minimum (0)
    0x26, 0xFF, 0x00,  //   Logical Maximum (255)
    0x81, 0x00,        //   Input (Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0xC0,              // End Collection
};

esp_hid_raw_report_map_t ble_report_maps[] = {
    {
        .data = ComboReportMap,
        .len = sizeof(ComboReportMap)
    }
};

esp_hid_device_config_t ble_hid_config = {
    .vendor_id          = 0x16C0,
    .product_id         = 0x05DF,
    .version            = 0x0100,
    .device_name        = "BTHID-ESP32S3",
    .manufacturer_name  = "Espressif/ArtInBits",
    .serial_number      = "0000000000",
    .report_maps        = ble_report_maps,
    .report_maps_len    = 1
};
