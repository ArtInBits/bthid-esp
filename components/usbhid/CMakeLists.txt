idf_component_register(
    SRCS
        "usbhid.c"
    INCLUDE_DIRS
        "."

    REQUIRES usb driver espressif__usb_host_hid app_common
)
