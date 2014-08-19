#define TESTAPP_GEN

/* $Id: xsysace_selftest_example.c,v 1.1.2.1 2009/12/11 05:51:38 svemula Exp $ */
/******************************************************************************
*
* (c) Copyright 2005-2009 Xilinx, Inc. All rights reserved.
*
* This file contains confidential and proprietary information of Xilinx, Inc.
* and is protected under U.S. and international copyright and other
* intellectual property laws.
*
* DISCLAIMER
* This disclaimer is not a license and does not grant any rights to the
* materials distributed herewith. Except as otherwise provided in a valid
* license issued to you by Xilinx, and to the maximum extent permitted by
* applicable law: (1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND WITH ALL
* FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES AND CONDITIONS, EXPRESS,
* IMPLIED, OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF
* MERCHANTABILITY, NON-INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE;
* and (2) Xilinx shall not be liable (whether in contract or tort, including
* negligence, or under any other theory of liability) for any loss or damage
* of any kind or nature related to, arising under or in connection with these
* materials, including for any direct, or any indirect, special, incidental,
* or consequential loss or damage (including loss of data, profits, goodwill,
* or any type of loss or damage suffered as a result of any action brought by
* a third party) even if such damage or loss was reasonably foreseeable or
* Xilinx had been advised of the possibility of the same.
*
* CRITICAL APPLICATIONS
* Xilinx products are not designed or intended to be fail-safe, or for use in
* any application requiring fail-safe performance, such as life-support or
* safety devices or systems, Class III medical devices, nuclear facilities,
* applications related to the deployment of airbags, or any other applications
* that could lead to death, personal injury, or severe property or
* environmental damage (individually and collectively, "Critical
* Applications"). Customer assumes the sole risk and liability of any use of
* Xilinx products in Critical Applications, subject only to applicable laws
* and regulations governing limitations on product liability.
*
* THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS PART OF THIS FILE
* AT ALL TIMES.
*
******************************************************************************/
/*****************************************************************************/
/**
*
* @file xsysace_selftest_example.c
*
* This file contains a design example using the SystemACE driver.
*
* This example does a simple read/write test of the System Ace Control Register.
*
* @note
*
* None
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date	 Changes
* ----- ---- -------- ---------------------------------------------------------
* 1.00a ecm  01/25/05 First release for TestApp integration
* 1.00a sv   06/06/05 Minor changes to comply to Doxygen and coding guidelines
* 1.11a sv   09/03/07 Simplified the example
* 2.00a ktn  10/22/09 Updated the example to use macros that have been modified
*		      to remove _m from the name and made minor changes to
*		      comply with coding guidelines and updated.
* </pre>
*
******************************************************************************/

/***************************** Include Files *********************************/

#include "xparameters.h"
#include "xstatus.h"
#include "xsysace.h"

/************************** Constant Definitions *****************************/

/*
 * The following constants map to the XPAR parameters created in the
 * xparameters.h file. They are defined here such that a user can easily
 * change all the needed parameters in one place.
 */
#ifndef TESTAPP_GEN
#define SYSACE_DEVICE_ID		XPAR_SYSACE_0_DEVICE_ID
#endif


/**************************** Type Definitions *******************************/


/***************** Macros (Inline Functions) Definitions *********************/


/************************** Function Prototypes ******************************/

int SysAceSelfTestExample(u16 DeviceId);

/************************** Variable Definitions *****************************/

XSysAce SysAce;		/* An instance of the device */

/****************************************************************************/
/**
*
* This function is the main function of this Example.
*
* @param	None
*
* @return	XST_SUCCESS if successful, otherwise XST_FAILURE.
*
* @note		None
*
*****************************************************************************/
#ifndef TESTAPP_GEN
int main(void)
{
	int Status;

	Status = SysAceSelfTestExample(SYSACE_DEVICE_ID);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	return XST_SUCCESS;
}
#endif

/*****************************************************************************/
/**
*
* An example of using the System ACE driver interface to run a simple
* read/write test after the initialization of the driver.
*
* @param	DeviceId is the XPAR_<SYSTEM_ACE_INSTANCE_NUM>_DEVICE_ID value
*		from xparameters.h.
*
* @return	XST_SUCCESS if successful, otherwise XST_FAILURE.
*
* @note		None.
*
******************************************************************************/
int SysAceSelfTestExample(u16 DeviceId)
{
	int Status;
	u32 ControlReg;

	/*
	 * Initialize the instance. The device defaults to polled mode.
	 */
	Status = XSysAce_Initialize(&SysAce, DeviceId);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Read the initial value of the Control Register.
	 */
	ControlReg = XSysAce_GetControlReg(SysAce.BaseAddress);

	/*
	 * Disable all the interrupts in the Control Register.
	 */
	 XSysAce_DisableInterrupt(&SysAce);

	/*
	 * Verify that the interrupts are disabled.
	 */
	if (XSysAce_GetControlReg(SysAce.BaseAddress) &
		(XSA_CR_DATARDYIRQ_MASK | XSA_CR_ERRORIRQ_MASK |
		 XSA_CR_CFGDONEIRQ_MASK)) {

		 Status |= XST_FAILURE;
	}

	/*
	 * Enable the Error interrupt in the Control Register.
	 */
	XSysAce_EnableInterrupt(&SysAce);

	/*
	 * Verify that the Error interrupt is enabled.
	 */
	if (XSysAce_GetControlReg(SysAce.BaseAddress) &
				XSA_CR_ERRORIRQ_MASK){
		Status |= XST_SUCCESS;
	}
	else {
		Status |= XST_FAILURE;
	}

	/*
	 * Restore the initial value of the Control Register.
	 */
	XSysAce_SetControlReg(SysAce.BaseAddress, ControlReg);


	if (Status & XST_FAILURE) {
		return XST_FAILURE;
	} else {
		return XST_SUCCESS;
	}

}


