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

#ifndef _WIRING_ANALOG_
#define _WIRING_ANALOG_

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
#define CHN_36   0                          /* Position of channel 4 group 4 (AN36) on the array of ADC channels    */
#define CHN_37   1                          /* Position of channel 5 group 4 (AN37) on the array of ADC channels    */
#define CHN_38   2                          /* Position of channel 6 group 4 (AN38) on the array of ADC channels    */
#define CHN_39   3                          /* Position of channel 7 group 4 (AN39) on the array of ADC channels    */
#define CHN_24   4                          /* Position of channel 0 group 3 (AN24) on the array of ADC channels    */
#define CHN_25   5                          /* Position of channel 1 group 3 (AN25) on the array of ADC channels    */
#define CHN_TR   6                          /* Position of channel 0 group 0 (AN0) on the array of ADC channels    */


/******************************************************************************
** FUNCTION PROTOTYPES                                                       **
******************************************************************************/

/*
 * \brief Configures the reference voltage used for analog input (i.e. the value used as the top of the input range).
 * This function is kept only for compatibility with existing AVR based API.
 *
 * \param ulMmode Should be set to AR_DEFAULT.
 */
extern void analogReference( uint8 ulMode ) ;

/*
 * \brief Writes an analog value (PWM wave) to a pin.
 *
 * \param ulPin
 * \param ulValue
 */
extern void analogWrite( uint8 ulPin, uint32 ulValue ) ;

/*
 * \brief Reads the value from the specified analog pin.
 *
 * \param ulPin
 *
 * \return Read value from selected pin, if no error.
 */
extern uint16 analogRead( uint8 ulPin ) ;

/*
 * \brief Set the resolution of analogRead return values. Default is 10 bits (range from 0 to 1023).
 *
 * \param res
 */
extern void analogReadResolution(int res);

/*
 * \brief Set the resolution of analogWrite parameters. Default is 8 bits (range from 0 to 255).
 *
 * \param res
 */
extern void analogWriteResolution(int res);

extern void wiring_analog_init(void) ;

#ifdef __cplusplus
}
#endif

#endif /* _WIRING_ANALOG_ */
