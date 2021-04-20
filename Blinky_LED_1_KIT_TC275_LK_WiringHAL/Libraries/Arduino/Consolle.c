//****************************************************************************
// @Module        Arduino-compatible Consolle (Serial port communication).
// @Filename      Consolle.h
// @Project       Arduino_AURIX
//----------------------------------------------------------------------------
// @Controller    Infineon TC275 Lite Kit
//
// @Compiler
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
// @Date          15/04/2021
//
//****************************************************************************


//****************************************************************************
// @Project Includes
//****************************************************************************

#include "Arduino.h"

#include "string.h"
#include "Ifx_Fifo.h"
#include "IfxAsclin_Asc.h"
#include "IfxCpu_Irq.h"


//****************************************************************************
// @Macros
//****************************************************************************


//****************************************************************************
// @Defines
//****************************************************************************
/* Communication parameters */
#define ISR_PRIORITY_ASCLIN_TX      8                                       /* Priority for interrupt ISR Transmit  */
#define ISR_PRIORITY_ASCLIN_RX      4                                       /* Priority for interrupt ISR Receive   */
#define ISR_PRIORITY_ASCLIN_ER      12                                      /* Priority for interrupt ISR Errors    */
#define ASC_TX_BUFFER_SIZE          256                                     /* Define the TX buffer size in byte    */
#define ASC_RX_BUFFER_SIZE          256                                     /* Define the RX buffer size in byte    */
#define ASC_BAUDRATE                115200                                  /* Define the UART baud rate            */


//****************************************************************************
// @Typedefs
//****************************************************************************


//****************************************************************************
// @Imported Global Variables
//****************************************************************************


//****************************************************************************
// @Global Variables
//****************************************************************************
IfxStdIf_DPipe  g_ascStandardInterface;                                     /* Standard interface object            */
IfxAsclin_Asc   g_asclin;                                                   /* ASCLIN module object                 */

/* The transfer buffers allocate memory for the data itself and for FIFO runtime variables.
 * 8 more bytes have to be added to ensure a proper circular buffer handling independent from
 * the address to which the buffers have been located.
 */
uint8 g_uartTxBuffer[ASC_TX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];
uint8 g_uartRxBuffer[ASC_RX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];


//****************************************************************************
// @External Prototypes
//****************************************************************************


//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************
/*********************************************************************************************************************/
/*---------------------------------------------Function Implementations----------------------------------------------*/
/*********************************************************************************************************************/
/* Macro to define Interrupt Service Routine.
 * This macro makes following definitions:
 * 1) Define linker section as .intvec_tc<vector number>_<interrupt priority>.
 * 2) define compiler specific attribute for the interrupt functions.
 * 3) define the Interrupt service routine as ISR function.
 *
 * IFX_INTERRUPT(isr, vectabNum, priority)
 *  - isr: Name of the ISR function.
 *  - vectabNum: Vector table number.
 *  - priority: Interrupt priority. Refer Usage of Interrupt Macro for more details.
 */
IFX_INTERRUPT(asc0TxISR, 0, ISR_PRIORITY_ASCLIN_TX);

void asc0TxISR(void)
{
    IfxStdIf_DPipe_onTransmit(&g_ascStandardInterface);
}

IFX_INTERRUPT(asc0RxISR, 0, ISR_PRIORITY_ASCLIN_RX);

void asc0RxISR(void)
{
    IfxStdIf_DPipe_onReceive(&g_ascStandardInterface);
}

IFX_INTERRUPT(asc0ErrISR, 0, ISR_PRIORITY_ASCLIN_ER);

void asc0ErrISR(void)
{
    IfxStdIf_DPipe_onError(&g_ascStandardInterface);
}

//****************************************************************************
// @Function     consolle_init
//
//----------------------------------------------------------------------------
// @Description   This function initializes the ASCLIN UART module
//
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Link          https://www.infineon.com/dgdl/Infineon-AURIX_ASCLIN_UART_1_KIT_TC297_TFT-Training-v01_01-EN.pdf?fileId=5546d462766cbe8601768b8b1bfa38af
//----------------------------------------------------------------------------
// @Date          15/04/2021
//
//****************************************************************************
void Consolle_init(void)
{
    IfxAsclin_Asc_Config ascConf;

    /* Set default configurations */
    IfxAsclin_Asc_initModuleConfig(&ascConf, &MODULE_ASCLIN0); /* Initialize the structure with default values      */

    /* Set the desired baud rate */
    ascConf.baudrate.baudrate = ASC_BAUDRATE;                                   /* Set the baud rate in bit/s       */
    ascConf.baudrate.oversampling = IfxAsclin_OversamplingFactor_16;            /* Set the oversampling factor      */

    /* Configure the sampling mode */
    ascConf.bitTiming.medianFilter = IfxAsclin_SamplesPerBit_three;             /* Set the number of samples per bit*/
    ascConf.bitTiming.samplePointPosition = IfxAsclin_SamplePointPosition_8;    /* Set the first sample position    */

    /* ISR priorities and interrupt target */
    ascConf.interrupt.txPriority = ISR_PRIORITY_ASCLIN_TX;  /* Set the interrupt priority for TX events             */
    ascConf.interrupt.rxPriority = ISR_PRIORITY_ASCLIN_RX;  /* Set the interrupt priority for RX events             */
    ascConf.interrupt.erPriority = ISR_PRIORITY_ASCLIN_ER;  /* Set the interrupt priority for Error events          */
    ascConf.interrupt.typeOfService = IfxSrc_Tos_cpu0;

    /* Pin configuration */
    const IfxAsclin_Asc_Pins pins = {
            .cts        = NULL_PTR,                         /* CTS pin not used                                     */
            .ctsMode    = IfxPort_InputMode_pullUp,
            .rx         = &IfxAsclin0_RXA_P14_1_IN,         /* Select the pin for RX connected to the USB port      */
            .rxMode     = IfxPort_InputMode_pullUp,         /* RX pin                                               */
            .rts        = NULL_PTR,                         /* RTS pin not used                                     */
            .rtsMode    = IfxPort_OutputMode_pushPull,
            .tx         = &IfxAsclin0_TX_P14_0_OUT,         /* Select the pin for TX connected to the USB port      */
            .txMode     = IfxPort_OutputMode_pushPull,      /* TX pin                                               */
            .pinDriver  = IfxPort_PadDriver_cmosAutomotiveSpeed1
    };
    ascConf.pins = &pins;

    /* FIFO buffers configuration */
    ascConf.txBuffer = g_uartTxBuffer;                      /* Set the transmission buffer                          */
    ascConf.txBufferSize = ASC_TX_BUFFER_SIZE;              /* Set the transmission buffer size                     */
    ascConf.rxBuffer = g_uartRxBuffer;                      /* Set the receiving buffer                             */
    ascConf.rxBufferSize = ASC_RX_BUFFER_SIZE;              /* Set the receiving buffer size                        */

    /* Init ASCLIN module */
    IfxAsclin_Asc_initModule(&g_asclin, &ascConf);          /* Initialize the module with the given configuration   */

    /* Initialize the Standard Interface */
    IfxAsclin_Asc_stdIfDPipeInit(&g_ascStandardInterface, &g_asclin);
}


//****************************************************************************
// @Function     Consolle_print
//
//----------------------------------------------------------------------------
// @Description   The print() method writes data to the serial port. This is
//                  often helpful for looking at the data a program is
//                  producing or to write data to other devices connected to
//                  the serial port.
//
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    char      message[STDIF_DPIPE_MAX_PRINT_SIZE + 1];
//
//----------------------------------------------------------------------------
// @Link          https://www.infineon.com/dgdl/Infineon-AURIX_ASCLIN_UART_1_KIT_TC297_TFT-Training-v01_01-EN.pdf?fileId=5546d462766cbe8601768b8b1bfa38af
//----------------------------------------------------------------------------
// @Date          15/04/2021
//
//****************************************************************************
void Consolle_print(const void *message)
{
    Ifx_SizeT count = (Ifx_SizeT)strlen(message);
    IfxStdIf_DPipe_write(&g_ascStandardInterface, (void *)message, &count, TIME_INFINITE);
}


//****************************************************************************
// @Function     Consolle_println
//
//----------------------------------------------------------------------------
// @Description   The print() method writes data to the serial port. This is
//                  often helpful for looking at the data a program is
//                  producing or to write data to other devices connected to
//                  the serial port. The println method works like print, but
//                  sends a new line character for each call to the function.
//
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    char      message[STDIF_DPIPE_MAX_PRINT_SIZE + 1];
//
//----------------------------------------------------------------------------
// @Link          https://www.infineon.com/dgdl/Infineon-AURIX_ASCLIN_UART_1_KIT_TC297_TFT-Training-v01_01-EN.pdf?fileId=5546d462766cbe8601768b8b1bfa38af
//----------------------------------------------------------------------------
// @Date          15/04/2021
//
//****************************************************************************
void Consolle_println(const void *message)
{
    // Conactenate given string with CR-NL and print
    char      msg[STDIF_DPIPE_MAX_PRINT_SIZE + 1];
    strcat ( (char * ) message, ENDLINE);
    Consolle_print(msg);
}





//****************************************************************************
// @Local Functions
//****************************************************************************



//****************************************************************************
//                                 END OF FILE
//****************************************************************************
