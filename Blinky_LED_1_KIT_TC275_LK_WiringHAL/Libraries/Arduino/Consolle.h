//****************************************************************************
// @Module        Arduino-compatible Consolle (Serial port communication).
// @Filename      Consolle.h
// @Project       Arduino_AURIX
//----------------------------------------------------------------------------
// @Controller    Infineon TC275 Lite Kit
//
// @Compiler      ADS
//
// @Codegenerator
//
// @Description   This file contains low level functions to implement the
//                  Serial language opcodes.
//                  The Serial serial port allows for easily reading
//                  and writing data to and from external devices. It allows
//                  two machines to communicate and gives you the flexibility
//                  to make your own devices and use them as the input or
//                  output to your programs. The serial port used to be a
//                  nine pin I/O port that existed on most PCs and can be
//                  emulated through a USB serial adapter.
//
// @Link          https://www.arduino.cc/reference/en/language/functions/communication/serial/
//
//----------------------------------------------------------------------------
// @Date          14/04/2021
//
//****************************************************************************

#ifndef CONSOLLE_H_
#define CONSOLLE_H_

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
**                      Include Files                                        **
******************************************************************************/
#include "IfxAsclin_Asc.h"
#include "IfxCpu_Irq.h"


//****************************************************************************
// @Defines
//****************************************************************************
#define ENDLINE     "\n\r"

/******************************************************************************
** FUNCTION PROTOTYPES                                                       **
******************************************************************************/
extern void Consolle_init(void);                    // Initialization function

/**
 * \brief Writes data (int, float, byte, char, char[],
 *
 * numbers in base (DEC, BIN, OCT or HEX) or Strings to the serial port.
 *
 * \return null
 */
extern void Consolle_print(const void *data);


/**
 * \brief Works like print(), but sends a new line character for each call to the function
 *
 * \return null
 */
extern void Consolle_println(const void *data);


#ifdef __cplusplus
}
#endif


#endif /* CONSOLLE_H_ */
