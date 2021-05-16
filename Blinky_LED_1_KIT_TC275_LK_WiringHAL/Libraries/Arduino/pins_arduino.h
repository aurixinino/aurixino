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
// @Filename      pins_arduino.h
// @Project       Arduino_AURIX
//----------------------------------------------------------------------------
// @Controller    Infineon TC275 Lite Kit
//
// @Compiler      ADS
//
// @Codegenerator none
//
// @Description   XMC1100 pin mapping to Arduino Uno board.
//
// @Link          http://arduino.cc/en/Hacking/PinMapping
//
//----------------------------------------------------------------------------
// @Date          11/04/2021
//
//****************************************************************************

#ifndef PINS_ARDUINO_H_
#define PINS_ARDUINO_H_

//****************************************************************************
// @Project Includes
//****************************************************************************
#include "Platform_Types.h"

//****************************************************************************
// @Defines
//****************************************************************************

#define NUM_DIGITAL_PINS    21
#define NUM_ANALOG_INPUTS   6

//------------------------------------------------------
// Arduino      AURIX        Arduino Meaning
//------------------------------------------------------
//  0           P15.3        Device transmit UART signal-RXD
//  1           P15.2        Device received UART signal-TXD
//  2           P02.0        External interrupt
//  3           P02.1        External interrupt / PWM output
//  4           P10.4        GPIO
//  5           P02.3        PWM output
//  6           P02.5        PWM output
//  7           P02.4        GPIO
//  8           P02.6        GPIO
//  9           P02.7        PWM output
// 10           P10.5        SPI-SS / PWM output
// 11           P10.3        SPI-MOSI / PWM output
// 12           P10.1        SPI-MISO
// 13           P10.2        SPI-SCK
// 14           GND          Ground
// 15           VAREF        Analog reference voltage
// 16           P13.2        I2C Data / Address
// 17           P13.1        I2C Clock
// 30           Extended Leds P0.5
// 31           Extended Leds P0.6
// 32           Extended Button 1
//------------------------------------------------------


// Port Numeric Definition - Digital Pins
#define D0      0
#define D1      1
#define D2      2
#define D3      3
#define D4      4
#define D5      5
#define D6      6
#define D7      7
#define D8      8
#define D9      9
#define D10     10
#define D11     11
#define D12     12
#define D13     13
#define D14     -1  // Cannot drive GND
#define D15     -1  // Cannot drive VAREF
#define D16     16
#define D17     17
#define LED     18  // Cannot use standard Arduino LED pin 13
#define LED1    LED
#define LED2    19  // Extended Led
#define BUTTON  20
//...


// Port Address Definition - Digital Pins
#define D0_P        &MODULE_P15,3                                           /* Arduino: Port, Pin definition      */
#define D1_P        &MODULE_P15,2                                           /* Arduino: Port, Pin definition      */
#define D2_P        &MODULE_P02,0                                           /* Arduino: Port, Pin definition      */
#define D3_P        &MODULE_P02,1                                           /* Arduino: Port, Pin definition      */
#define D4_P        &MODULE_P10,4                                           /* Arduino: Port, Pin definition      */
#define D5_P        &MODULE_P02,3                                           /* Arduino: Port, Pin definition      */
#define D6_P        &MODULE_P02,5                                           /* Arduino: Port, Pin definition      */
#define D7_P        &MODULE_P02,4                                           /* Arduino: Port, Pin definition      */
#define D8_P        &MODULE_P02,6                                           /* Arduino: Port, Pin definition      */
#define D9_P        &MODULE_P02,7                                           /* Arduino: Port, Pin definition      */
#define D10_P       &MODULE_P10,5                                           /* Arduino: Port, Pin definition      */
#define D11_P       &MODULE_P10,3                                           /* Arduino: Port, Pin definition      */
#define D12_P       &MODULE_P10,1                                           /* Arduino: Port, Pin definition      */
#define D13_P       &MODULE_P10,2                                           /* Arduino: Port, Pin definition      */
#define D14_P       &(*(Ifx_P*)0x0u),0
#define D15_P       &(*(Ifx_P*)0x0u),0
#define D16_P       &MODULE_P13,2                                           /* Arduino: Port, Pin definition      */
#define D17_P       &MODULE_P13,1                                           /* Arduino: Port, Pin definition      */
#define LED_P       &MODULE_P00,5                                           /* LED    : Port, Pin definition      */
#define LED1_P      LED_P                                                   /* LED1   : Port, Pin definition      */
#define LED2_P      &MODULE_P00,6                                           /* LED2   : Port, Pin definition      */
#define BUTTON_P    &MODULE_P00,7                                           /* BUTTON : Port, Pin definition      */
//...





//...

// Port Numeric Definition - Analogue Pins
#define A0      20
#define A1      21
#define A2      22
#define A3      23
#define A4      24
#define A5      25
#define TRIMM   26
//...


#if TODO
static const uint8 SS   = 10;
static const uint8 MOSI = 11;
static const uint8 MISO = 12;
static const uint8 SCK  = 13;

static const uint8 SDA = 18;
static const uint8 SCL = 19;
static const uint8 LED_BUILTIN = 13;
#endif






//****************************************************************************
// @Typedefs
//****************************************************************************

/* Definitions and types for pins */
typedef enum _EAnalogChannel
{
  NO_ADC=-1,
  ADC0=0,
  ADC1,
  ADC2,
  ADC3,
  ADC4,
  ADC5,
} EAnalogChannel ;


#endif /* PINS_ARDUINO_H_ */
