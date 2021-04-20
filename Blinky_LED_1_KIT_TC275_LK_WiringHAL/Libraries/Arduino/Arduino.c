/*


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
// @Module        Arduino main hardware interface layer
// @Filename      Arduino.c
// @Project       Arduino_AURIX
//----------------------------------------------------------------------------
// @Controller    Infineon TC275 Lite Kit
//
// @Compiler      ADS
//
// @Codegenerator none
//
// @Description   This file contains low level functions to implement the
//                  Wiring language infrastructure
//
// @Link          https://www.arduino.cc/reference/en/
//
//----------------------------------------------------------------------------
// @Date          12/04/2021
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


//****************************************************************************
// @External Prototypes
//****************************************************************************


//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************

//****************************************************************************
// @Function      arduino_init
//
//----------------------------------------------------------------------------
// @Description   Initialize the Arduino layer.
//
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Link
//----------------------------------------------------------------------------
// @Date          12/04/2021
//
//****************************************************************************

void arduino_init(void)
{
      /*
       *  Periferals Initialization
       */
      wiring_digital_init();
      //wiring_analog_init(); TODO

      // Serial Initialization
      Consolle_init();
}

//****************************************************************************
//                                 END OF FILE
//****************************************************************************
