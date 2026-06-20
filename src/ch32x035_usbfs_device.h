/********************************** (C) COPYRIGHT *******************************
 * File Name          : ch32v20x_usbfs_device.h
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2022/08/20
 * Description        : This file contains all the functions prototypes for the
 *                      USBFS firmware library.
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

#ifndef __CH32V035_USBFS_DEVICE_H_
#define __CH32V035_USBFS_DEVICE_H_

// #include "debug.h"
#include "string.h"

#include "usb_desc.h"

#include <ch32x035.h>
#include <ch32x035_usb.h>
#include <ch32x035_pwr.h>
// #include "UART.h"

/******************************************************************************/
/* Global Define */
#ifndef __PACKED
#define __PACKED __attribute__((packed))
#endif

/* end-point number */
#define DEF_UEP_IN 0x80
#define DEF_UEP_OUT 0x00
#define DEF_UEP0 0x00
#define DEF_UEP1 0x01
#define DEF_UEP2 0x02
#define DEF_UEP3 0x03
#define DEF_UEP4 0x04
#define DEF_UEP5 0x05
#define DEF_UEP6 0x06
#define DEF_UEP7 0x07
#define DEF_UEP_NUM 8

#define USBFSD_UEP_MOD_BASE 0x5000000C
#define USBFSD_UEP_DMA_BASE 0x50000010
#define USBFSD_UEP_LEN_BASE 0x50000030
#define USBFSD_UEP_CTL_BASE 0x50000032
#define USBFSD_UEP_RX_EN 0x08
#define USBFSD_UEP_TX_EN 0x04
#define USBFSD_UEP_BUF_MOD 0x01
#define DEF_UEP_DMA_LOAD 0 /* Direct the DMA address to the data to be processed */
#define DEF_UEP_CPY_LOAD 1 /* Use memcpy to move data to a buffer */
#define USBFSD_UEP_MOD(n) (*((volatile uint8_t *)(USBFSD_UEP_MOD_BASE + n)))
#define USBFSD_UEP_TX_CTRL(n) (*((volatile uint8_t *)(USBFSD_UEP_CTL_BASE + n * 0x04)))
#define USBFSD_UEP_RX_CTRL(n) (*((volatile uint8_t *)(USBFSD_UEP_CTL_BASE + n * 0x04 + 1)))
#define USBFSD_UEP_DMA(n) (*((volatile uint32_t *)(USBFSD_UEP_DMA_BASE + n * 0x04)))
#define USBFSD_UEP_BUF(n) ((uint8_t *)(*((volatile uint32_t *)(USBFSD_UEP_DMA_BASE + n * 0x04))) + 0x20000000)
#define USBFSD_UEP_TLEN(n) (*((volatile uint16_t *)(USBFSD_UEP_LEN_BASE + n * 0x04)))

/* Setup Request Packets */
#define pUSBFS_SetupReqPak ((PUSB_SETUP_REQ)USBFS_EP0_Buf)

/*******************************************************************************/
/* Variable Definition */

/******************************************************************************/
/* Related macro definitions */
/* Serial buffer related definitions */
#define DEF_UARTx_RX_BUF_LEN (4 * 512)                                        /* Serial x receive buffer size */
#define DEF_UARTx_TX_BUF_LEN (2 * 512)                                        /* Serial x transmit buffer size */
#define DEF_USB_FS_PACK_LEN DEF_USBD_FS_PACK_SIZE                             /* USB full speed mode packet size for serial x data */
#define DEF_UARTx_TX_BUF_NUM_MAX (DEF_UARTx_TX_BUF_LEN / DEF_USB_FS_PACK_LEN) /* Serial x transmit buffer size */

/* Serial port receive timeout related macro definition */
#define DEF_UARTx_BAUDRATE 115200      /* Default baud rate for serial port */
#define DEF_UARTx_STOPBIT 0            /* Default stop bit for serial port */
#define DEF_UARTx_PARITY 0             /* Default parity bit for serial port */
#define DEF_UARTx_DATABIT 8            /* Default data bit for serial port */
#define DEF_UARTx_RX_TIMEOUT 30        /* Serial port receive timeout, in 100uS */
#define DEF_UARTx_USB_UP_TIMEOUT 60000 /* Serial port receive upload timeout, in 100uS */

/* Serial port transceiver DMA channel related macro definition */
// #define DEF_UART2_TX_DMA_CH DMA1_Channel7 /* Serial 2 transmit channel DMA channel */
// #define DEF_UART2_RX_DMA_CH DMA1_Channel6 /* Serial 1 transmit channel DMA channel */


#define USB_IOEN                    0x00000080
#define USB_PHY_V33                 0x00000040
#define UDP_PUE_MASK                0x0000000C
#define UDP_PUE_DISABLE             0x00000000
#define UDP_PUE_35UA                0x00000004
#define UDP_PUE_10K                 0x00000008
#define UDP_PUE_1K5                 0x0000000C

#define UDM_PUE_MASK                0x00000003
#define UDM_PUE_DISABLE             0x00000000
#define UDM_PUE_35UA                0x00000001
#define UDM_PUE_10K                 0x00000002
#define UDM_PUE_1K5                 0x00000003


/************************************************************/
/* Serial port X related structure definition */
typedef struct __attribute__((packed)) _UART_CTL
{
  // uint16_t Rx_LoadPtr;            /* Serial x data receive buffer load pointer */
  // uint16_t Rx_DealPtr;            /* Pointer to serial x data receive buffer processing */
  // volatile uint16_t Rx_RemainLen; /* Remaining unprocessed length of the serial x data receive buffer */
  // uint8_t Rx_TimeOut;             /* Serial x data receive timeout */
  uint8_t Rx_TimeOutMax; /* Serial x data receive timeout maximum */

  // volatile uint16_t Tx_LoadNum;                           /* Serial x data send buffer load number */
  // volatile uint16_t Tx_DealNum;                           /* Serial x data send buffer processing number */
  // volatile uint16_t Tx_RemainNum;                         /* Serial x data send buffer remaining unprocessed number */
  // volatile uint16_t Tx_PackLen[DEF_UARTx_TX_BUF_NUM_MAX]; /* The current packet length of the serial x data send buffer */
  // uint8_t Tx_Flag;                                        /* Serial x data send status */
  // uint8_t Recv1;
  // uint16_t Tx_CurPackLen; /* The current packet length sent by serial port x */
  // uint16_t Tx_CurPackPtr; /* Pointer to the packet currently being sent by serial port x */

  // uint8_t USB_Up_IngFlag; /* Serial xUSB packet being uploaded flag */
  // uint8_t Recv2;
  // uint16_t USB_Up_TimeOut;   /* Serial xUSB packet upload timeout timer */
  // uint8_t USB_Up_Pack0_Flag; /* Serial xUSB data needs to upload 0-length packet flag */
  // uint8_t USB_Down_StopFlag; /* Serial xUSB packet stop down flag */

  uint8_t Com_Cfg[8]; /* Serial x parameter configuration (default baud rate is 115200, 1 stop bit, no parity, 8 data bits) */
  // uint8_t Recv3;
  // uint8_t USB_Int_UpFlag;       /* Serial x interrupt upload status */
  // uint16_t USB_Int_UpTimeCount; /* Serial x interrupt upload timing */
} UART_CTL;//, *PUART_CTL;

/***********************************************************************************************************************/
/* Constant, variable extents */
/* The following are serial port transmit and receive related variables and buffers */
// extern volatile UART_CTL Uart;                  /* Serial x control related structure */
// extern volatile uint32_t UARTx_Rx_DMACurCount;  /* Serial x receive DMA current count */
// extern volatile uint32_t UARTx_Rx_DMALastCount; /* last count of DMA received by serial x */
// extern __attribute__((aligned(4))) uint8_t UART2_Tx_Buf[DEF_UARTx_TX_BUF_LEN]; /* Serial x transmit buffer */
// extern __attribute__((aligned(4))) uint8_t UART2_Rx_Buf[DEF_UARTx_RX_BUF_LEN]; /* Serial x transmit buffer */

/* Global */
// extern const uint8_t *pUSBFS_Descr;

/* Setup Request */
// extern volatile uint8_t USBFS_SetupReqCode;
// extern volatile uint8_t USBFS_SetupReqType;
// extern volatile uint16_t USBFS_SetupReqValue;
// extern volatile uint16_t USBFS_SetupReqIndex;
// extern volatile uint16_t USBFS_SetupReqLen;

/* USB Device Status */
// extern volatile uint8_t USBFS_DevConfig;
// extern volatile uint8_t USBFS_DevAddr;
// extern volatile uint8_t USBFS_DevSleepStatus;
// extern volatile uint8_t USBFS_DevEnumStatus;

/* Endpoint Buffer */
// extern __attribute__((aligned(4))) uint8_t USBFS_EP0_Buf[];
// extern __attribute__((aligned(4))) uint8_t USBFS_EP1_Buf[];
// extern __attribute__((aligned(4))) uint8_t USBFS_EP2_Buf[];
// extern __attribute__((aligned(4))) uint8_t USBFS_EP3_Buf[];
/* USB IN Endpoint Busy Flag */
// extern volatile uint8_t USBFS_Endp_Busy[];

/******************************************************************************/
/* external functions */


extern void USBFS_Device_Init(FunctionalState sta);
extern void USBFS_Device_Endp_Init(void);
extern void USBFS_RCC_Init(void);
extern void USBFS_Send_Resume(void);
// extern void USBFS_Sleep_Wakeup_Operate(void);
extern uint8_t USBFS_Endp_DataUp(uint8_t endp, uint8_t *pbuf, uint16_t len, uint8_t mod);

#endif /* USER_CH32V20X_USB_DEVICE_H_ */
