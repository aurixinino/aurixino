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
// @Module        Arduino-compatible implementation.
// @Filename      Arduino.h
// @Project       Arduino_AURIX
//----------------------------------------------------------------------------
// @Controller    Infineon TC275 Lite Kit
//
// @Compiler      ADS
//
// @Codegenerator none
//
// @Description   Constants are predefined variables in the Arduino language.
//                  They are used to make the programs easier to read.
//
// @Link          http://arduino.cc/en/Reference/Constants
//
//----------------------------------------------------------------------------
// @Date          11/04/2021
//
//****************************************************************************

#ifndef _ARDUINO_H_
#define _ARDUINO_H_

#ifdef __cplusplus
extern "C"{
#endif

//****************************************************************************
// @Project Includes
//****************************************************************************
// #include general HEADER FILES.
#include "Platform_Types.h"

// #include Arduino HEADER FILES.
#include "pins_arduino.h"
#include "wiring_digital.h"
//#include "wiring_analog.h"
//#include "wiring_shift.h"
#include "wiring_time.h"
//#include "wiring_clock.h"
//#include "itoa.h"
//#include "dtostrf.h"

#include "Consolle.h"
#include "semaphore.h"

/* Arduino wiring macros and bit defines  */
#define HIGH            1
#define LOW             0

#define INPUT           0
#define OUTPUT          1
#define INPUT_PULLUP    2
#define INPUT_PULLDW    3
#define PWM             4 /**< This is a special mode for when the pin will be used for
                               PWM output (a special case of digital output). */
#define PWM_OPEN_DRAIN  5 /**< Like PWM, except that instead of alternating
                               cycles of LOW and HIGH, the voltage on the pin
                               consists of alternating cycles of LOW and
                               floating (disconnected). */

#define true        0x1
#define false       0x0

#define clockCyclesPerMicrosecond() ( SystemCoreClock / 1000000L )
#define clockCyclesToMicroseconds(a) ( ((a) * 1000L) / (SystemCoreClock / 1000L) )
#define microsecondsToClockCycles(a) ( (a) * (SystemCoreClock / 1000000L) )

#define PI 3.1415926535897932384626433832795
#define HALF_PI 1.5707963267948966192313216916398
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105

#define SERIAL  0x0
#define DISPLAY 0x1

#define LSBFIRST 0
#define MSBFIRST 1

#define CHANGE 1
#define FALLING 2
#define RISING 3

#define DEFAULT 0
#define EXTERNAL 1
#define INTERNAL 2

#define lowByte(w)                     ((w) & 0xFF)
#define highByte(w)                    (((w) >> 8) & 0xFF)
#define bitRead(value, bit)            (((value) >> (bit)) & 0x01)
#define bitSet(value, bit)             ((value) |= (1UL << (bit)))
#define bitClear(value, bit)           ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : \
                                                   bitClear(value, bit))
#define bit(b)                         (1UL << (b))

// undefine stdlib's abs if encountered
#ifdef abs
#undef abs
#endif

#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define abs(x) ((x)>0?(x):-(x))
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#define round(x)     ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))
#define radians(deg) ((deg)*DEG_TO_RAD)
#define degrees(rad) ((rad)*RAD_TO_DEG)
#define sq(x) ((x)*(x))

#define map( x,  in_min,  in_max,  out_min,  out_max)   ((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min);

typedef uint8 byte;
typedef unsigned int word;

/******************************************************************************
** FUNCTION PROTOTYPES                                                       **
******************************************************************************/
extern void arduino_init(void);
extern void setup(void);
extern void cpu0_setup(void);
extern void cpu1_setup(void);
extern void cpu2_setup(void);

extern void loop(void);
extern void cpu0_loop(void);
extern void cpu1_loop(void);
extern void cpu2_loop(void);



#ifdef __cplusplus
} // extern "C"
#endif

#endif  /** ifndef _ARDUINO_H_ */

