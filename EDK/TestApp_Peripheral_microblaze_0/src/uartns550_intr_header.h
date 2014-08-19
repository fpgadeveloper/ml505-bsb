#define TESTAPP_GEN

/* $Id: uartns550_intr_header.h,v 1.1 2008/08/27 12:17:47 sadanan Exp $ */

#include "xbasic_types.h"
#include "xstatus.h"

XStatus UartNs550IntrExample(XIntc* IntcInstancePtr, \
                             XUartNs550* UartLiteInstancePtr, \
                             Xuint16 UartNs550DeviceId, \
                             Xuint16 UartNs550IntrId);


