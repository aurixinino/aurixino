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
// @Filename      wiring_analog.c
// @Project       Arduino_AURIX
//----------------------------------------------------------------------------
// @Controller    Infineon TC275 Lite Kit
//
// @Compiler      ADS
//
// @Codegenerator
//
// @Description   This file contains low level functions to implement the
//                  analog language opcodes.
//
// @Link          http://arduino.cc/en/Reference
//
//----------------------------------------------------------------------------
// @Date          30/01/2014 01.06.23
//
//****************************************************************************




//****************************************************************************
// @Project Includes
//****************************************************************************

#include "Arduino.h"
#include "IfxVadc_Adc.h"
#include "wiring_analog.h"


//****************************************************************************
// @Macros
//****************************************************************************
#define CHANNELS_NUM    4                       /* Number of used channels                                          */


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
IfxVadc_Adc g_vadc;                                           /* Global variable for configuring the VADC module    */
IfxVadc_Adc_Group g_vadcGroup;                                /* Global variable for configuring the VADC group     */
IfxVadc_Adc_Channel g_vadcChannel[CHANNELS_NUM];              /* Global variable for configuring the VADC channels  */
/* Define the used channels */
IfxVadc_ChannelId g_vadcChannelIDs[] = {IfxVadc_ChannelId_4,  /* AN36: channel 4 of group 4                         */
                                        IfxVadc_ChannelId_5,  /* AN37: channel 5 of group 4                         */
                                        IfxVadc_ChannelId_6,  /* AN38: channel 6 of group 4                         */
                                        IfxVadc_ChannelId_7,  /* AN39: channel 7 of group 4                         */
                                        IfxVadc_ChannelId_0,  /* AN24: channel 3 of group 3                         */
                                        IfxVadc_ChannelId_1,  /* AN25: channel 3 of group 3                         */
};


//****************************************************************************
// @External Prototypes
//****************************************************************************


//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************
/*********************************************************************************************************************/
/*------------------------------------------------Function Prototypes------------------------------------------------*/
/*********************************************************************************************************************/
void initVADCModule(void);                      /* Function to initialize the VADC module with default parameters   */
void initVADCGroup(void);                       /* Function to initialize the VADC group                            */
void initVADCChannels(void);                    /* Function to initialize the VADC used channels                    */
uint16 readADCValue(uint8 channel);             /* Function to return the conversion value */

//****************************************************************************
// @Function      wiring_analog_init
//
//----------------------------------------------------------------------------
// @Description   Initialize the ADC channels.
//                  The Arduino board contains a 6 channel .
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Link          http://arduino.cc/en/Reference/Analog
//----------------------------------------------------------------------------
// @Date          31/01/2014
//
//****************************************************************************

void wiring_analog_init(void)
{
    initVADCModule();                                                   /* Initialize the VADC module               */
    initVADCGroup();                                                    /* Initialize the VADC group                */
    initVADCChannels();                                                 /* Initialize the used channels             */

    /* Start the scan */
    IfxVadc_Adc_startBackgroundScan(&g_vadc);
}


//****************************************************************************
// @Function      analogRead
//
//----------------------------------------------------------------------------
// @Description   Reads the value from the specified analog pin.
//                  The Arduino board contains a 6 ADC channels.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    pin: the number of the analog input pin to read from 0 to 5
//
//----------------------------------------------------------------------------
// @Link          http://arduino.cc/en/Reference/AnalogRead
//----------------------------------------------------------------------------
// @Date          30/01/2014
//
//****************************************************************************

uint16 analogRead(uint8 pin)
{

    uint16 value = 0;


    // Select the required channel in channel pending register
    switch(pin)
    {
        // A0   P40.9       ADC0: AN39 / VADCG4.7
        case A0:
            value = readADCValue(CHN_39);
            break;

        // A1   P40.8       ADC1: AN38 / VADCG4.6
        case A1:
            value = readADCValue(CHN_38);
            break;

        // A2   P40.7       ADC2: AN37 / VADCG4.5
        case A2:
            value = readADCValue(CHN_37);
            break;

        // A3   P40.6       ADC3: AN36 / VADCG4.4
        case A3:
            value = readADCValue(CHN_36);
            break;

        // A4   P40.0       ADC4: AN24 / VADCG3.0
        case A4:
            value = readADCValue(CHN_24);
            break;

        // A5   P40.1       ADC5: AN25 / VADCG3.1
        case A5:
            value = readADCValue(CHN_25);
            break;

        // TRIMM   AN0      ADC0: AN0 / VADCG0.0
        case TRIMM:
            value = readADCValue(CHN_TR);
            break;
    }

    // Return ADC Conversion
    return (value);
}

//****************************************************************************
// @Function     analogWrite
//
//----------------------------------------------------------------------------
// @Description   Writes an analog value (PWM wave) to a pin. Can be used to
//                  light a LED at varying brightnesses or drive a motor at
//                  various speeds. After a call to analogWrite(), the pin
//                  will generate a steady square wave of the specified duty
//                  cycle until the next call to analogWrite() (or a call to
//                  digitalRead() or digitalWrite() on the same pin).
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    pin: the pin to write to.
//                value: the duty cycle: between 0 (off) and 255 (full on).
//
//----------------------------------------------------------------------------
// @Link          http://arduino.cc/en/Reference/AnalogWrite
//----------------------------------------------------------------------------
// @Date          02/02/2014
//
//****************************************************************************

void analogWrite(uint8 pin, uint32 ulValue)
{
#if 0
float fDutyCycle;

    fDutyCycle = (float)ulValue*100.0/255.0;

    // Set the pin mode
    switch(pin)
    {
#if 0
        //  3   P0.0        External interrupt / PWM output
        case 3:
            PWMSP001_Start(&PWMSP001_Handle0);
            PWMSP001_SetDutyCycle(&PWMSP001_Handle0, fDutyCycle);
            break;

        //  5   P0.2        PWM output
        case 5:
            PWMSP001_Start(&PWMSP001_Handle1);
            PWMSP001_SetDutyCycle(&PWMSP001_Handle1, fDutyCycle);
            break;

        //  6   P0.3        PWM output
        case 6:
            PWMSP001_Start(&PWMSP001_Handle2);
            PWMSP001_SetDutyCycle(&PWMSP001_Handle2, fDutyCycle);
            break;

        //  9   P0.8        PWM output
        case 9:
            P0_8_set_mode(outputMode);
            break;

        // 10   P0.9        SPI-SS / PWM output
        case 10:
            P0_9_set_mode(outputMode);
            break;

        // 11   P1.1        SPI-MOSI / PWM output
        case 11:
            PWMSP001_Start(&PWMSP001_Handle3);
            PWMSP001_SetDutyCycle(&PWMSP001_Handle3, fDutyCycle);
            break;
#endif

        // 13   P0.7        SPI-SCK / LED output
        case 13:
            PWMSP001_SetDutyCycle(&PWMSP001_Handle1, fDutyCycle);
            break;

        case LED2:
            PWMSP001_SetDutyCycle(&PWMSP001_Handle0, fDutyCycle);
            break;

        default:
            if (ulValue < 128)
                digitalWrite(pin, LOW);
            else
                digitalWrite(pin, HIGH);
            break;

    }
#endif
}


//****************************************************************************
// @Local Functions
//****************************************************************************

/* Function to initialize the VADC module with default parameters */
void initVADCModule(void)
{
    IfxVadc_Adc_Config adcConf;                                         /* Define a configuration structure         */
    IfxVadc_Adc_initModuleConfig(&adcConf, &MODULE_VADC);               /* Fill it with default values              */
    IfxVadc_Adc_initModule(&g_vadc, &adcConf);                          /* Apply the configuration                  */
}

/* Function to initialize the VADC group */
void initVADCGroup(void)
{
    IfxVadc_Adc_GroupConfig adcGroupConf;                               /* Define a configuration structure         */
    IfxVadc_Adc_initGroupConfig(&adcGroupConf, &g_vadc);                /* Fill it with default values              */

    adcGroupConf.groupId = IfxVadc_GroupId_4;                           /* Select the Group 4                       */
    adcGroupConf.master = adcGroupConf.groupId;                         /* Set the same group as master group       */

    /* Enable the background scan source and the background auto scan functionality */
    adcGroupConf.arbiter.requestSlotBackgroundScanEnabled = TRUE;
    adcGroupConf.backgroundScanRequest.autoBackgroundScanEnabled = TRUE;

    /* Enable the gate in "always" mode (no edge detection) */
    adcGroupConf.backgroundScanRequest.triggerConfig.gatingMode = IfxVadc_GatingMode_always;

    IfxVadc_Adc_initGroup(&g_vadcGroup, &adcGroupConf);                 /* Apply the configuration                  */
}

/* Function to initialize the VADC used channels */
void initVADCChannels(void)
{
    IfxVadc_Adc_ChannelConfig adcChannelConf[CHANNELS_NUM];             /* Array of configuration structures        */

    uint16 chn;
    for(chn = 0; chn < CHANNELS_NUM; chn++)                             /* Initialize all the channels in a loop    */
    {
        /* Fill the configuration with default values */
        IfxVadc_Adc_initChannelConfig(&adcChannelConf[chn], &g_vadcGroup);

        /* Set the channel ID and the corresponding result register */
        adcChannelConf[chn].channelId = g_vadcChannelIDs[chn];          /* The channels 4..7 are initialized        */
        adcChannelConf[chn].resultRegister = (IfxVadc_ChannelResult)(chn);
        adcChannelConf[chn].backgroundChannel = TRUE;                   /* Enable background scan for the channel   */

        /* Apply the channel configuration */
        IfxVadc_Adc_initChannel(&g_vadcChannel[chn], &adcChannelConf[chn]);

        /* Add the channel to background scan */
        unsigned chnEnableBit = (1 << adcChannelConf[chn].channelId);   /* Set the the corresponding input channel  */
        unsigned mask = chnEnableBit;                                   /* of the respective group to be added in   */
        IfxVadc_Adc_setBackgroundScan(&g_vadc, &g_vadcGroup, chnEnableBit, mask); /* the background scan sequence.  */
    }
}

/* Function to read the VADC measurement */
uint16 readADCValue(uint8 channel)
{
    Ifx_VADC_RES conversionResult;
    do
    {
        conversionResult = IfxVadc_Adc_getResult(&g_vadcChannel[channel]);
    } while(!conversionResult.B.VF);

    return conversionResult.B.RESULT;
}


//****************************************************************************
//                                 END OF FILE
//****************************************************************************

