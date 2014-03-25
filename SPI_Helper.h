//*****************************************************************************
// Filename: SPI_Helper.h
// Author: Derek Chopp
// Last Update: 3/25/14
//
// Description: Header file for SPI helper code
//
// TODO:
// same as SPI_Helper.c
//
//*****************************************************************************

#ifndef SPI_HELPER_H_
#define SPI_HELPER_H_

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/ssi.h"

//*****************************************************************************
// Define Constants
//*****************************************************************************
#define SPI_CLOCK 8000000


//*****************************************************************************
// Function Prototypes
//*****************************************************************************
void SPI_Init();
void SPI_Send(unsigned char data);
void SPI_Wait();

#endif /* SPI_HELPER_H_ */
