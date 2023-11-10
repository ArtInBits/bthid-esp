idf_component_register(
    SRCS
        "blehid.c" "esp_hid_gap.c" "blehiddata.c"
    INCLUDE_DIRS
        "."

    REQUIRES app_common usbhid bt esp_hid_multi_conn
)