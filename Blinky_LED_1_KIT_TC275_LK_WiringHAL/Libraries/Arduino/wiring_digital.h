/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

//****************************************************************************
// @Module        Arduino-compatible digital I/O implementation.
// @Filename      wiring_digital.h
// @Project       Arduino_AURIX
//----------------------------------------------------------------------------
// @Controller    Infineon TC275 Lite Kit
//
// @Compiler      ADS
//
// @Codegenerator none
//
// @Description   This file contains low level functions to implement the
//                  Wiring Digital language opcodes.
//
// @Link          http://arduino.cc/en/Tutorial/DigitalPins
//
//----------------------------------------------------------------------------
// @Date          11/04/2021
//
//****************************************************************************

#ifndef WIRING_DIGITAL_H_
#define WIRING_DIGITAL_H_

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
**                      Include Files                                        **
******************************************************************************/

#include "Platform_Types.h"
#include "IfxPort.h"

//****************************************************************************
// @Defines
//****************************************************************************


/******************************************************************************
** FUNCTION PROTOTYPES                                                       **
******************************************************************************/

extern void wiring_digital_init(void);

/**
 * Configure behavior of a GPIO pin.
 *
 * @param pin Number of pin to configure.
 * @param mode Mode corresponding to desired pin behavior.
 * @see WiringPinMode
 */
void pinMode(uint8 pin, uint8 mode);

/**
 * Writes a (digital) value to a pin.  The pin must have its
 * mode set to OUTPUT or OUTPUT_OPEN_DRAIN.
 *
 * @param pin Pin to write to.
 * @param value Either LOW (write a 0) or HIGH (write a 1).
 * @see pinMode()
 */
void digitalWrite(uint8 pin, uint8 value);

/**
 * Read a digital value from a pin.  The pin must have its mode set to
 * one of INPUT, INPUT_PULLUP, and INPUT_PULLDOWN.
 *
 * @param pin Pin to read from.
 * @return LOW or HIGH.
 * @see pinMode()
 */
uint32 digitalRead(uint8 pin);


/**
 * Toggle the LED.
 *
 * If the LED is on, turn it off.  If it is off, turn it on.
 *
 * The LED must its mode set to OUTPUT. This can be accomplished
 * portably over all LeafLabs boards by calling pinMode(BOARD_LED_PIN,
 * OUTPUT) before calling this function.
 *
 * @see pinMode()
 */
static inline void toggleLED() {
    IfxPort_togglePin(LED_P);
}
#define toggleLED1 toggleLED

static inline void toggleLED2() {
    IfxPort_togglePin(LED2_P);
}



#ifdef __cplusplus
}
#endif

#endif /* WIRING_DIGITAL_H_ */
