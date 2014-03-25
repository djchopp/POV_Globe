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

    //
    // GPIO used for UART and SSI
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);

    // Set alternate function mux to SSI
    GPIOPinConfigure(GPIO_PA2_SSI0CLK);
    GPIOPinConfigure(GPIO_PA3_SSI0FSS);
    GPIOPinConfigure(GPIO_PA4_SSI0RX);
    GPIOPinConfigure(GPIO_PA5_SSI0TX);

    // CLK, MOSI, and MISO pins use alternate function (SSI)
    GPIOPinTypeSSI(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_4 | GPIO_PIN_3 | GPIO_PIN_2);

    // set the SSI clock to the PIOSC clock
    SSIClockSourceSet(SSI0_BASE, SSI_CLOCK_PIOSC);
    SSIConfigSetExpClk(SSI0_BASE, 16000000, SSI_FRF_MOTO_MODE_0, SSI_MODE_MASTER, SPI_CLOCK, 8);
    SSIEnable(SSI0_BASE);
}

void SPI_Send(unsigned char data){
	SSIDataPut(SSI0_BASE, data);
}

void SPI_Wait(){
	while(SSIBusy(SSI0_BASE));
}
