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
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"
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
#define delay 50000

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
uint32_t SD_Read_Header();
void SD_Read_Line();


//*****************************************************************************
// Global Variables
//*****************************************************************************
static FATFS g_sFatFs;
static DIR g_sDirObject;
static FILINFO g_sFileInfo;
static FIL g_sFileObject;

FRESULT iFResult;
BYTE buffer[3*4*NUM_MODULES+1];
UINT br;

LED_Array currentLine;
LED_MSG currentMSG;

uint32_t packetCount = 0;
uint32_t numData = 0;
uint32_t displayPeriod = 1;
uint32_t rpmPeriod = 1;

#endif /* MAIN_H_ */
