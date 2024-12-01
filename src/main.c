// =============================================================================
// Project:   USB mouse jiggler for CH32X035
// Version:   v0.9
// Year:      2024
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

// =============================================================================
// Main Function
// =============================================================================
int main(void) {
  // Init GPIO LED
  PIN_output(IND1_PIN);

  // Init USB mouse
  MOUSE_init();

  // Loop
  while(1) {
    PIN_high(IND1_PIN);
    MOUSE_move(DELTA, 0);  // move right
    DLY_ms(200);
    MOUSE_move(-DELTA, 0); // move left
    PIN_low(IND1_PIN);
    DLY_ms(DELAY/2 * 1000);
    DLY_ms(DELAY/2 * 1000);
  }
}
