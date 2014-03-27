/*
 * main.h
 *
 *  Created on: Mar 26, 2014
 *      Author: DC
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/ssi.h"
#include "PinSetup.h"
#include "POV_Helper.h"
#include "SPI_Helper.h"
#include "fatfs/src/ff.h"
#include "fatfs/src/diskio.h"

//*****************************************************************************
// Define Constants
//*****************************************************************************
#define delay 500000

//*****************************************************************************
// The error routine that is called if the driver library encounters an error.
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}
#endif


//*****************************************************************************
// Function Prototypes
//*****************************************************************************
void Send_MSG(LED_MSG *currentMSG);
void Read_Send();


//*****************************************************************************
// Global Variables
//*****************************************************************************
static FATFS g_sFatFs;
static DIR g_sDirObject;
static FILINFO g_sFileInfo;
static FIL g_sFileObject;

FRESULT iFResult;
BYTE buffer[3];
UINT br;

LED_Array currentRow;
LED_MSG currentMSG;

#endif /* MAIN_H_ */
