// =============================================================================
// User Configurations
// =============================================================================

#pragma once

// MCU supply voltage
#define USB_VDD             1         // 0: 3.3V, 1: 5V

// Indicator LEDs
#define IND1_PIN PB12

// Mouse movement
#define DELTA 1
#define DELAY 50

// USB device descriptor
#define USB_VENDOR_ID       0xCAFE
#define USB_PRODUCT_ID      0x4005
#define USB_DEVICE_VERSION  0x0009    // v0.9 (BCD-format)
#define USB_LANGUAGE        0x0409    // US English

// USB configuration descriptor
#define USB_MAX_POWER_mA    50        // max power in mA 

// USB descriptor strings
#define MANUF_STR           "Generic"
#define PROD_STR            "Mouse"
#define SERIAL_STR          "123457"
#define INTERF_STR          "HID-Mouse"
