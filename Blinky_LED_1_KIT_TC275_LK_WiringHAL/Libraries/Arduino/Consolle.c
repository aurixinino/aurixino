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

#include "Ifx_Fifo.h"
#include "IfxAsclin_Asc.h"
#include "IfxCpu_Irq.h"

//****************************************************************************
// @Macros
//****************************************************************************


//****************************************************************************
// @Defines
//****************************************************************************
#define UART_BAUDRATE           115200                                  /* UART baud rate in bit/s                  */

#define UART_PIN_RX             IfxAsclin0_RXA_P14_1_IN                 /* UART receive port pin                    */
#define UART_PIN_TX             IfxAsclin0_TX_P14_0_OUT                 /* UART transmit port pin                   */

/* Definition of the interrupt priorities */
#define INTPRIO_ASCLIN1_RX      18
#define INTPRIO_ASCLIN1_TX      19

#define UART_RX_BUFFER_SIZE     64                                      /* Definition of the receive buffer size    */
#define UART_TX_BUFFER_SIZE     64                                      /* Definition of the transmit buffer size   */                     */
#define SIZE                    13                                      /* Size of the string                       */

//****************************************************************************
// @Typedefs
//****************************************************************************


//****************************************************************************
// @Imported Global Variables
//****************************************************************************


//****************************************************************************
// @Global Variables
//****************************************************************************
/* Declaration of the ASC handle */
static IfxAsclin_Asc g_ascHandle;

/* Declaration of the FIFOs parameters */
#if 0
static uint8 g_ascRxBuffer[UART_RX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];
static uint8 g_ascTxBuffer[UART_TX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];
#else
static uint8 g_ascRxBuffer[100];
static uint8 g_ascTxBuffer[100];
#endif

/* Definition of txData and rxData */
uint8 g_txData[] = "Hello World!";
uint8 g_rxData[SIZE] = {''};

/* Size of the message */
Ifx_SizeT g_count = sizeof(g_txData);


//****************************************************************************
// @External Prototypes
//****************************************************************************


//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************
/*********************************************************************************************************************/
/*---------------------------------------------Function Implementations----------------------------------------------*/
/*********************************************************************************************************************/
/* Adding of the interrupt service routines */
IFX_INTERRUPT(asclin1TxISR, 0, INTPRIO_ASCLIN1_TX);
void asclin1TxISR(void)
{
    IfxAsclin_Asc_isrTransmit(&g_ascHandle);
}

IFX_INTERRUPT(asclin1RxISR, 0, INTPRIO_ASCLIN1_RX);
void asclin1RxISR(void)
{
    IfxAsclin_Asc_isrReceive(&g_ascHandle);
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
    /* Initialize an instance of IfxAsclin_Asc_Config with default values */
    IfxAsclin_Asc_Config ascConfig;
    IfxAsclin_Asc_initModuleConfig(&ascConfig, &MODULE_ASCLIN1);

    /* Set the desired baud rate */
    ascConfig.baudrate.baudrate = UART_BAUDRATE;

    /* ISR priorities and interrupt target */
    ascConfig.interrupt.txPriority = INTPRIO_ASCLIN1_TX;
    ascConfig.interrupt.rxPriority = INTPRIO_ASCLIN1_RX;
    ascConfig.interrupt.typeOfService = IfxCpu_Irq_getTos(IfxCpu_getCoreIndex());

    /* FIFO configuration */
    ascConfig.txBuffer = &g_ascTxBuffer;
    //TODO: ascConfig.txBufferSize = UART_TX_BUFFER_SIZE;
    ascConfig.rxBuffer = &g_ascRxBuffer;
    //TODO: ascConfig.rxBufferSize = UART_RX_BUFFER_SIZE;

    /* Pin configuration */
    const IfxAsclin_Asc_Pins pins =
    {
        NULL_PTR,       IfxPort_InputMode_pullUp,     /* CTS pin not used */
        &UART_PIN_RX,   IfxPort_InputMode_pullUp,     /* RX pin           */
        NULL_PTR,       IfxPort_OutputMode_pushPull,  /* RTS pin not used */
        &UART_PIN_TX,   IfxPort_OutputMode_pushPull,  /* TX pin           */
        IfxPort_PadDriver_cmosAutomotiveSpeed1
    };
    ascConfig.pins = &pins;

    IfxAsclin_Asc_initModule(&g_ascHandle, &ascConfig); /* Initialize module with above parameters */
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
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Link          https://www.infineon.com/dgdl/Infineon-AURIX_ASCLIN_UART_1_KIT_TC297_TFT-Training-v01_01-EN.pdf?fileId=5546d462766cbe8601768b8b1bfa38af
//----------------------------------------------------------------------------
// @Date          15/04/2021
//
//****************************************************************************
void Consolle_print(const void *data)
{
    IfxAsclin_Asc_write(&g_ascHandle, g_txData, &g_count, TIME_INFINITE);
}



/* This function sends and receives the string "Hello World!" */
void send_receive_ASCLIN_UART_message(void)
{
    IfxAsclin_Asc_write(&g_ascHandle, g_txData, &g_count, TIME_INFINITE);   /* Transmit data via TX */
    IfxAsclin_Asc_read(&g_ascHandle, g_rxData, &g_count, TIME_INFINITE);    /* Receive data via RX  */
}






//****************************************************************************
// @Local Functions
//****************************************************************************



//****************************************************************************
//                                 END OF FILE
//****************************************************************************
