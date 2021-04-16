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
// @Module        Arduino-compatible timer implementation.
// @Filename      wiringime.c
// @Project       Arduino_AURIX
//----------------------------------------------------------------------------
// @Controller    Infineon TC275 Lite Kit
//
// @Compiler
//
// @Codegenerator
//
// @Description   This file contains low level functions to implement the
//                  Wiring Delay language opcodes.
//
// @Link          http://arduino.cc/en/Reference/Delay
//
//----------------------------------------------------------------------------
// @Date          15/04/2021
//
//****************************************************************************




//****************************************************************************
// @Project Includes
//****************************************************************************

#include "Arduino.h"
#include "Bsp.h"

//****************************************************************************
// @Macros
//****************************************************************************


//****************************************************************************
// @Defines
//****************************************************************************
#define TIMER_1mSec 1000              /*!< Millisecond to Microsecond ratio */
#define TIMER_mSecTouSec_RATIO  \
                (TIMER_1mSec/TIMER_ISR_RATIO)   /*!< mS to uS scaling factor*/

//****************************************************************************
// @Typedefs
//****************************************************************************


//****************************************************************************
// @Imported Global Variables
//****************************************************************************


//****************************************************************************
// @Global Variables
//****************************************************************************
//static volatile bool bTimerExpired;


//****************************************************************************
// @External Prototypes
//****************************************************************************


//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************
//void m_Timer(void* v);


//****************************************************************************
// @Function     millis
//
//----------------------------------------------------------------------------
// @Description   Returns the number of milliseconds since the Arduino board
//                  began running the current program.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Link          http://arduino.cc/en/Reference/Millis
//----------------------------------------------------------------------------
// @Date          15/04/2021
//
//****************************************************************************

uint32 millis(void)
{
    return (0); //SYSTM002_GetTime());
}

//****************************************************************************
// @Function     micros
//
//----------------------------------------------------------------------------
// @Description   Returns the number of microseconds  since the Arduino board
//                  began running the current program.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Link          http://arduino.cc/en/Reference/Micros
//----------------------------------------------------------------------------
// @Date          15/04/2021
//
//****************************************************************************

uint32 micros(void)
{
    return (1000); //SYSTM002_GetTime();
}

//****************************************************************************
// @Function     delay
//
//----------------------------------------------------------------------------
// @Description   Pauses the program for the amount of time (in miliseconds)
//                  specified as parameter.
//                  There are 1000 milliseconds in a second.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Link          http://arduino.cc/en/Reference/Delay
//----------------------------------------------------------------------------
// @Date          15/04/2021
//
//****************************************************************************

void delay(uint32 dwMs)
{
    waitTime(IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, dwMs));
}

//****************************************************************************
// @Function     delayMicroseconds
//
//----------------------------------------------------------------------------
// @Description   Pauses the program for the amount of time (in microseconds)
//                  specified as parameter.
//                  There are a thousand microseconds in a millisecond, and
//                  a million microseconds in a second.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Link          http://arduino.cc/en/Reference/DelayMicroseconds
//----------------------------------------------------------------------------
// @Date          15/04/2021
//
//****************************************************************************

void delayMicroseconds(uint32 dwUs)
{
    waitTime(IfxStm_getTicksFromMicroseconds(BSP_DEFAULT_TIMER, dwUs));
}


//****************************************************************************
// @Local Functions
//****************************************************************************
#if TODO
void m_Timer(void* Temp)
{
    bTimerExpired = TRUE;
}
#endif



//****************************************************************************
//                                 END OF FILE
//****************************************************************************
