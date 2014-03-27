//*****************************************************************************
// Filename: SPI_Helper.c
// Author: Derek Chopp
// Last Update: 3/25/14
//
// Description: Helper functions for the SPI.
// All SPI module interaction is handled through this helper
// There should not be any SSI access in any other files
//
// TODO:
// Clean up...
//
//*****************************************************************************

#include "SPI_Helper.h"

void SPI_Init(){

    // set the SSI clock to the PIOSC clock
    SSIClockSourceSet(SSI1_BASE, SSI_CLOCK_PIOSC);
    SSIConfigSetExpClk(SSI1_BASE, 16000000, SSI_FRF_MOTO_MODE_0, SSI_MODE_MASTER, SPI_CLOCK, 8);
    SSIEnable(SSI1_BASE);
}

void SPI_Send(unsigned char data){
	SSIDataPut(SSI1_BASE, data);
}

void SPI_Wait(){
	while(SSIBusy(SSI1_BASE));
}
