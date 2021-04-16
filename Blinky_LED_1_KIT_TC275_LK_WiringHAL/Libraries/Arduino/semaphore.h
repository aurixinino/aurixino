//****************************************************************************
// @Module        AURIX-compatible semaphore implementation.
// @Filename      semaphore.h
// @Project       Arduino_AURIX
//----------------------------------------------------------------------------
// @Controller    Infineon TC275 Lite Kit
//
// @Compiler      ADS
//
// @Codegenerator none
//
// @Description   This file contains low level functions to implement the
//                  Semaphore functionality to permit process sincronization.
//
// @Link          https://aurixino.blogspot.com/
//
//----------------------------------------------------------------------------
// @Date          13/04/2021
//
//****************************************************************************

#ifndef SEMAPHORE_H_
#define SEMAPHORE_H_

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
**                      Include Files                                        **
******************************************************************************/
// #include general HEADER FILES.
#include "Platform_Types.h"

//****************************************************************************
// @Defines
//****************************************************************************

#define semaphore_t boolean // semaphore type
#define RED     TRUE        // RED semaphore color: resource is blocked
#define GREEN   FALSE       // GRREN semaphore color: resource is free


/******************************************************************************
** FUNCTION PROTOTYPES                                                       **
******************************************************************************/

#define semaphore_init(s) \
            s = GREEN;

#define semaphore_take(s) \
            s = RED;

#define semaphore_give(s) \
            s = GREEN;

#define semaphore_wait(s)           \
            while (s == RED) {      \
                __asm__ ("nop");    \
                __asm__ ("nop");    \
                __asm__ ("nop");    \
                __asm__ ("nop");    \
            }


#ifdef __cplusplus
}
#endif

#endif /* SEMAPHORE_H_ */
