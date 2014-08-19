#define TESTAPP_GEN

/**************************************************************
 * (c) Copyright 2005 - 2009 Xilinx, Inc. All rights reserved.
 *
 * This file contains confidential and proprietary information
 * of Xilinx, Inc. and is protected under U.S. and
 * international copyright and other intellectual property
 * laws.
 *
 * DISCLAIMER
 * This disclaimer is not a license and does not grant any
 * rights to the materials distributed herewith. Except as
 * otherwise provided in a valid license issued to you by
 * Xilinx, and to the maximum extent permitted by applicable
 * law: (1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND
 * WITH ALL FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES
 * AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
 * BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-
 * INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE; and
 * (2) Xilinx shall not be liable (whether in contract or tort,
 * including negligence, or under any other theory of
 * liability) for any loss or damage of any kind or nature
 * related to, arising under or in connection with these
 * materials, including for any direct, or any indirect,
 * special, incidental, or consequential loss or damage
 * (including loss of data, profits, goodwill, or any type of
 * loss or damage suffered as a result of any action brought
 * by a third party) even if such damage or loss was
 * reasonably foreseeable or Xilinx had been advised of the
 * possibility of the same.
 *
 * CRITICAL APPLICATIONS
 * Xilinx products are not designed or intended to be fail-
 * safe, or for use in any application requiring fail-safe
 * performance, such as life-support or safety devices or
 * systems, Class III medical devices, nuclear facilities,
 * applications related to the deployment of airbags, or any
 * other applications that could lead to death, personal
 * injury, or severe property or environmental damage
 * (individually and collectively, "Critical
 * Applications"). Customer assumes the sole risk and
 * liability of any use of Xilinx products in Critical
 * Applications, subject only to applicable laws and
 * regulations governing limitations on product liability.
 *
 * THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS
 * PART OF THIS FILE AT ALL TIMES. 
 *************************************************************/
/**
*
* @file xlltemac_example.h
*
* Defines common data types, prototypes, and includes the proper headers
* for use with the TEMAC example code residing in this directory.
*
* This file along with xlltemac_example_util.c are utilized with the specific
* example code in the other source code files provided.
*
* These examples are designed to be compiled and utilized within the EDK
* standalone BSP development environment. The readme file contains more
* information on build requirements needed by these examples.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date     Changes
* ----- ---- -------- -------------------------------------------------------
* 1.00a jvb  04/05/07 First release
* 3.00a hbm  01/20/10 Hal phase 1 support, bump up major release
* </pre>
*
******************************************************************************/
#ifndef XTEMAC_EXAMPLE_H
#define XTEMAC_EXAMPLE_H


/***************************** Include Files *********************************/

#include "xparameters.h"	/* defines XPAR values */
#include "xlltemac.h"		/* defines XLlTemac API */
#include "xllfifo.h"
#include "xlldma.h"
#include "stdio.h"		/* stdio */
#include "xil_cache.h"

/************************** Constant Definitions ****************************/
#define TEMAC_LOOPBACK_SPEED	100	/* 100Mb/s for Mii */
#define TEMAC_LOOPBACK_SPEED_1G 1000	/* 1000Mb/s for GMii */
#define TEMAC_PHY_DELAY_SEC	4	/* Amount of time to delay waiting on
					 * PHY to reset.
					 */

#define MAX_MULTICAST_ADDR   (1<<23)	/* Maximum number of multicast ethernet
					 * mac addresses.
					 */

/***************** Macros (Inline Functions) Definitions *********************/


/**************************** Type Definitions ******************************/

/*
 * Define an aligned data type for an ethernet frame. This declaration is
 * specific to the GNU compiler
 */
typedef char EthernetFrame[XTE_MAX_FRAME_SIZE] __attribute__ ((aligned(8)));


/************************** Function Prototypes *****************************/



/*
 * Utility functions implemented in xlltemac_example_util.c
 */
void TemacUtilSetupUart(void);
void TemacUtilFrameHdrFormatMAC(EthernetFrame * FramePtr, char *DestAddr);
void TemacUtilFrameHdrFormatType(EthernetFrame * FramePtr, u16 FrameType);
void TemacUtilFrameSetPayloadData(EthernetFrame * FramePtr, int PayloadSize);
void TemacUtilFrameHdrVlanFormatVid(EthernetFrame * FramePtr, u32 VlanNumber, u32 Vid);
void TemacUtilFrameHdrVlanFormatType(EthernetFrame * FramePtr, u16 FrameType, u32 VlanNumber);
void TemacUtilFrameSetVlanPayloadData(EthernetFrame * FramePtr, int PayloadSize, u32 VlanNumber);
int TemacUtilFrameVerify(EthernetFrame * CheckFrame,
			 EthernetFrame * ActualFrame);
void TemacUtilFrameMemClear(EthernetFrame * FramePtr);
int TemacUtilEnterLoopback(XLlTemac * TemacInstancePtr, int Speed);
void TemacUtilErrorTrap(char *Message);
void TemacUtilPhyDelay(unsigned int Seconds);

/************************** Variable Definitions ****************************/

extern XLlTemac TemacInstance;	/* Temac device instance used throughout examples */
extern XLlFifo FifoInstance;	/* Fifo device instance used throughout examples */
extern XLlDma DmaInstance;	/* Dma device instance used throughout example */
extern char TemacMAC[];		/* Local MAC address */

#endif /* XTEMAC_EXAMPLE_H */


