//****************************************************************************
// @Module        Memory emulated serial Consolle (to be read via dedicated server).
// @Filename      DebugConsolle.h
// @Project       Arduino_AURIX
//----------------------------------------------------------------------------
// @Controller    Infineon TC275 Lite Kit
//
// @Compiler      ADS
//
// @Codegenerator
//
// @Description   This file contains low level functions to implement the
//                  Debug Consolle via the DAS server (memory emulation of
//                  serial comunication between AURIX and PC.
//
// @Link          none
//
//----------------------------------------------------------------------------
// @Date          20/04/2021
//
//****************************************************************************

#ifndef DEBUG_CONSOLLE_H_
#define DEBUG_CONSOLLE_H_

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
**                      Include Files                                        **
******************************************************************************/



//****************************************************************************
// @Defines
//****************************************************************************
/* Communication parameters */
#define DEBUG_CONSOLLE_SIZE         32  /* Total Debug Consolle Buffer [byte] size  */

typedef char DC_buffer_t;

typedef enum
{
    DC_Info      = 0,           /**< \brief Info Message (no issue). */
    DC_Warning   = 1,           /**< \brief Warning Message (first level of severity). */
    DC_Error     = 2,           /**< \brief Error Message (second level of severity). */
    DC_Abort     = 3,           /**< \brief ABORT Message (high level of severity). */
    DC_INIT      = 0xADC0,      /**< \brief INIT Message (no level of severity). */
} DC_Severity;

typedef struct
{
    DC_Severity   sev;
    const void    *message;
} DC_message;

/******************************************************************************
** FUNCTION PROTOTYPES                                                       **
******************************************************************************/
extern void DebugConsolle_init(void);                    // Initialization function

/**
 * \brief Writes debug consolle message
 *
 * with TAGs and Strings to the memory modeled serial port (to be read via DAS).
 *
 * \return null
 */
extern void DC_print(DC_message msg);



#ifdef __cplusplus
}
#endif


#endif /* DEBUG_CONSOLLE_H_ */
