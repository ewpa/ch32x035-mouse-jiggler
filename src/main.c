// =============================================================================
// Project:   USB mouse jiggler for CH32X035
// Version:   v0.10
// Year:      2024, 2025
// Author:    Ewan Parker (based on USB code by Stefan Wagner)
// Web:       https://www.ewan.cc
// License:   http://creativecommons.org/licenses/by-sa/3.0/
// =============================================================================
//
// Description:
// ------------
// Emulate a mouse and jiggle it from time to time.
//
// References:
// -----------
// - WCH Nanjing Qinheng Microelectronics: http://wch.cn
//
// Compilation Instructions:
// -------------------------
// - Make sure GCC toolchain (gcc-riscv64-unknown-elf, newlib) and Python3
//   with chprog are installed. In addition, Linux requires access rights to
//   the USB bootloader.
// - Press the BOOT button on the MCU board and keep it pressed while
//   connecting it via USB to your PC.
// - Run 'make flash'.
//
// Operating Instructions:
// -----------------------
// - Connect the board via USB to your PC. It should be detected as a HID
//   device.

// =============================================================================
// Libraries, Definitions and Macros
// =============================================================================
#include <config.h>                               // user configurations
#include <system.h>                               // system functions
#include <gpio.h>                                 // GPIO functions
#include <usb_mouse.h>                            // USB HID mouse functions

#if IND_INVERT
#define LED_on PIN_low
#define LED_off PIN_high
#else
#define LED_on PIN_high
#define LED_off PIN_low
#endif

// =============================================================================
// Main Function
// =============================================================================
int main(void) {
  // Init GPIO LED
  PIN_output(IND1_PIN);
  PIN_output(IND2_PIN);
  PIN_output(IND3_PIN);

  LED_off(IND1_PIN);
  LED_off(IND2_PIN);
  LED_on(IND3_PIN);

  // Init USB mouse
  MOUSE_init();

  // Loops
  while(1) {
    if (!(USBFSD->DEV_ADDR & USBFS_USB_ADDR_MASK) || USBFSD->MIS_ST & USBFS_UMS_SUSPEND || USBFSD->MIS_ST & USBFS_UMS_BUS_RESET) {
      LED_off(IND2_PIN);
      DLY_ms(200);
      LED_on(IND2_PIN);
      DLY_ms(200);
    }
    else {
      LED_on(IND2_PIN);
      LED_on(IND1_PIN);
      MOUSE_move(DELTA, 0);  // move right
      DLY_ms(200);
      MOUSE_move(-DELTA, 0); // move left
      LED_off(IND1_PIN);
      DLY_ms(DELAY/2 * 1000);
      DLY_ms(DELAY/2 * 1000);
    }
  }
}
