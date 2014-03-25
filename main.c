//*****************************************************************************
//Author: Derek Chopp
//
//Description: Main code for Blue Marble Enterprise POV Globe project
//
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/ssi.h"
#include "POV_Helper.h"
#include "SPI_Helper.h"

//*****************************************************************************
//
// Define Constants
//
//*****************************************************************************

#define delay 5000000

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}
#endif



void Send_MSG(LED_MSG *currentMSG);

//*****************************************************************************
//
// Main 'C' Language entry point.
//
//*****************************************************************************
int
main(void)
{
	//
    // Setup the system clock to run at 50 Mhz from PLL with crystal reference
    //
    SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|
                    SYSCTL_OSC_MAIN);


	SPI_Init();

	LED_Array currentRow;
	LED_MSG currentMSG;

	POV_Init(&currentRow);


	Set_All(&currentRow, 0x00FF, 0x00FF, 0x0000);

	Make_MSG(&currentMSG, &currentRow);

	while(1)Send_MSG(&currentMSG);

/*

    while(1){
    	//Red
    	Update_Leds(&currentMSG, &myLEDS, 255, 0, 0);
    	SysCtlDelay(delay);

    	//Orange
    	Update_Leds(&currentMSG, &myLEDS, 255, 128, 0);
    	SysCtlDelay(delay);

    	//Yellow
    	Update_Leds(&currentMSG, &myLEDS, 255, 255, 0);
    	SysCtlDelay(delay);

    	//Yellow Green
    	Update_Leds(&currentMSG, &myLEDS, 128, 255, 0);
    	SysCtlDelay(delay);

    	//Green
    	Update_Leds(&currentMSG, &myLEDS, 0, 255, 0);
    	SysCtlDelay(delay);

    	//Light Green
    	Update_Leds(&currentMSG, &myLEDS, 0, 255, 128);
    	SysCtlDelay(delay);

    	//Light Blue
    	Update_Leds(&currentMSG, &myLEDS, 0, 255, 255);
    	SysCtlDelay(delay);

    	//Med Blue
    	Update_Leds(&currentMSG, &myLEDS, 0, 128, 255);
    	SysCtlDelay(delay);

    	//Blue
    	Update_Leds(&currentMSG, &myLEDS, 0, 0, 255);
    	SysCtlDelay(delay);

    	//Purple
    	Update_Leds(&currentMSG, &myLEDS, 127, 0, 255);
    	SysCtlDelay(delay);

    	//Violet
    	Update_Leds(&currentMSG, &myLEDS, 255, 0, 255);
    	SysCtlDelay(delay);

    	//Pink
    	Update_Leds(&currentMSG, &myLEDS, 255, 0, 127);
    	SysCtlDelay(delay);
    }
    */

}

void Send_MSG(LED_MSG *currentMSG){
	int i,j;
	for(i=NUM_MODULES;i>=0;i--){
		for(j=0;j<28;j++){
			SSIDataPut(SSI0_BASE, currentMSG->Packets[i].Packet[j]);
		}
		while(SSIBusy(SSI0_BASE));
	}
}

