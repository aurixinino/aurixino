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
// @Filename      wiring_digital.C
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



//****************************************************************************
// @Project Includes
//****************************************************************************

#include "Arduino.h"

//****************************************************************************
// @Macros
//****************************************************************************


//****************************************************************************
// @Defines
//****************************************************************************


//****************************************************************************
// @Typedefs
//****************************************************************************


//****************************************************************************
// @Imported Global Variables
//****************************************************************************


//****************************************************************************
// @Global Variables
//****************************************************************************

const IfxPort_Pin pinDigitalList[] = {
        {D0_P},
        {D1_P},
        {D2_P},
        {D3_P},
        {D4_P},
        {D5_P},
        {D6_P},
        {D7_P},
        {D8_P},
        {D9_P},
        {D10_P},
        {D11_P},
        {D12_P},
        {D13_P},
        {D14_P},
        {D15_P},
        {D16_P},
        {D17_P},
        {LED1_P},
        {LED2_P},
        {BUTTON_P}
};


//****************************************************************************
// @External Prototypes
//****************************************************************************


//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************

//****************************************************************************
// @Function      wiring_digital_init
//
//----------------------------------------------------------------------------
// @Description   Initialize the I/O ports.
//                  The Arduino board contains a 13 digital I/Os.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Link          http://arduino.cc/en/Reference/Digital
//----------------------------------------------------------------------------
// @Date          12/04/2021
//
//****************************************************************************

void wiring_digital_init(void)
{
#if TODO
    // General Port Initialization
            //  D0      Device transmit UART signal-RXD
            //  D1      Device received UART signal-TXD
            //  D2      External interrupt
            //  D3      External interrupt / PWM output
            //  D4      GPIO
            //  D5      PWM output
            //  D6      PWM output
            //  D7      GPIO
            //  D8      GPIO
            //  D9      PWM output
            //  D10     SPI-SS / PWM output
            //  D11     SPI-MOSI / PWM output
            //  D12     SPI-MISO
            //  D13     SPI-SCK / LED output
            //  D14     Ground
            //  D15     Analog reference voltage
            //  D16     I2C Data / Address
            //  D17     I2C Clock

        IfxPort_Io_initModule(&confDigital);

#else
    // LED1 Port Initialization
        /* Initialization of the LED1 available on board and Switch OFF the LED (low-level active) */
        IfxPort_setPinModeOutput(LED1_P, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
        IfxPort_setPinHigh(LED1_P);
    // LED2 Port Initialization
        /* Initialization of the LED2 available on board and Switch OFF the LED (low-level active) */
        IfxPort_setPinModeOutput(LED2_P, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
        IfxPort_setPinLow(LED2_P);

    // BUTTON Port Initialization
        IfxPort_setPinModeInput(BUTTON_P, IfxPort_Mode_inputPullUp);

#endif
}


//****************************************************************************
// @Function     pinMode
//
//----------------------------------------------------------------------------
// @Description   Configures the specified pin to behave either as an input or
//                  an output. See the description of digital pins for details
//                  on the functionality of the pins.
//                  As of Arduino 1.0.1, it is possible to enable the internal
//                  pullup resistors with the mode INPUT_PULLUP.
//                  Additionally, the INPUT mode explicitly disables the
//                  internal pullups.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    pin: the number of the pin whose mode you wish to set
//                mode: INPUT, OUTPUT, or INPUT_PULLUP
//
//----------------------------------------------------------------------------
// @Link          http://arduino.cc/en/Reference/PinMode
//----------------------------------------------------------------------------
// @Date          27/01/2014
//
//****************************************************************************

void pinMode(uint8 pin, uint8 mode)
{
    uint16 outputMode = -1;

    // Select mode
    switch(mode)
    {
        case INPUT:
            outputMode = IfxPort_Mode_inputNoPullDevice;            // Input TriState
            break;

        case INPUT_PULLDW:                                          // Input Pull-Down
            outputMode = IfxPort_Mode_inputPullDown;
            break;

        case INPUT_PULLUP:                                          // Input Pull-Up
            outputMode = IfxPort_Mode_inputPullUp;
            break;

        case OUTPUT:
            outputMode = IfxPort_Mode_outputPushPullGeneral;        // Output Push-Pull
            break;
    }

    // Set the pin mode
    IfxPort_setPinMode(pinDigitalList[pin].port, pinDigitalList[pin].pinIndex, outputMode);
#if 0
    switch(pin)
    {
        // LED2 30  Extended Leds P0.5
        case LED2:
            if (mode == PWM)
                PWMSP001_Start(&PWMSP001_Handle0);
            else
                P0_5_set_mode(outputMode);
            break;

        // A0   P2.6        AA
        case A0:
            P2_6_set_mode(outputMode);
            break;

        // A1   P2.8        AB
        case A1:
            P2_8_set_mode(outputMode);
            break;

        // A2   P2.9        AC
        case A2:
            P2_9_set_mode(outputMode);
            break;

        // A3   P2.10       AD
        case A3:
            P2_10_set_mode(outputMode);
            break;

        // A4   P2.11       AE
        case A4:
            P2_11_set_mode(outputMode);
            break;

        // A5   P2.2        AF
        case A5:
            P2_2_set_mode(outputMode);
            break;
    }
#endif
}

//****************************************************************************
// @Function     digitalRead
//
//----------------------------------------------------------------------------
// @Description   Reads the value from a specified digital pin, either HIGH or LOW.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    pin: the number of the digital pin you want to read
//
//----------------------------------------------------------------------------
// @Link          http://arduino.cc/en/Reference/DigitalRead
//----------------------------------------------------------------------------
// @Date          12/04/2021
//
//****************************************************************************

uint32 digitalRead(uint8 pin)
{
    boolean bVal = IfxPort_getPinState(pinDigitalList[pin].port, pinDigitalList[pin].pinIndex);

    return ((bVal?HIGH:LOW));
}


//****************************************************************************
// @Function     digitalWrite
//
//----------------------------------------------------------------------------
// @Description   Write a HIGH or a LOW value to a digital pin.
//                  If the pin has been configured as an OUTPUT with pinMode(),
//                  its voltage will be set to the corresponding value:
//                  5V (or 3.3V on 3.3V boards) for HIGH, 0V (ground) for LOW.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    pin: the pin number
//                value: HIGH or LOW
//
//----------------------------------------------------------------------------
// @Link          http://arduino.cc/en/Reference/DigitalWrite
//----------------------------------------------------------------------------
// @Date          27/01/2014
//
//****************************************************************************

void digitalWrite(uint8 pin, uint8 value)
{
    // Set the pin
    if (value == HIGH)
        IfxPort_setPinState(pinDigitalList[pin].port, pinDigitalList[pin].pinIndex, IfxPort_State_high);
    else
        IfxPort_setPinState(pinDigitalList[pin].port, pinDigitalList[pin].pinIndex, IfxPort_State_low);

}

//****************************************************************************
//                                 END OF FILE
//****************************************************************************
