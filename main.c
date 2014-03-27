//*****************************************************************************
// Filename: main.c
// Author: Derek Chopp
// Last Update: 3/25/14
//
// Description: Main code for POV Globe. Basic operation is:
// 1. Initialize everything
// 2. Update rpm (TODO)
// 3. Update timer for new RPM (TODO)
// 4. Display current data at interrupt (TODO)
// 5. Repeat step 4 forever. (TODO)
//
// TODO:
// Add Hall Effect sensor support and the interrupts for it
// Add Timer to sync update pattern
//
//*****************************************************************************

#include "main.h"

//*****************************************************************************
// Main 'C' Language entry point.
//*****************************************************************************
int main(void)
{
	//
    // Setup the system clock to run at 50 Mhz from PLL with crystal reference
    //
    SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|
                    SYSCTL_OSC_MAIN);

    PortFunctionInit();

    FRESULT iFResult;
    BYTE buffer[3];
    UINT br;
    iFResult = f_mount(0, &g_sFatFs);

    if(iFResult != FR_OK) while(1);

    iFResult = f_open(&g_sFileObject,"data.txt", FA_READ);
    if(iFResult != FR_OK) while(1);

    f_read(&g_sFileObject, buffer, 3, &br);

    f_close(&g_sFileObject);


    // Unregister a work area before discard it
    f_mount(0, 0);



    //Placeholders for LED data
	LED_Array currentRow;
	LED_MSG currentMSG;

    //Initialize
	SPI_Init();
	POV_Init(&currentRow);


	Set_All(&currentRow, buffer[0], buffer[1], buffer[2]);
	Make_MSG(&currentMSG, &currentRow);
	Send_MSG(&currentMSG);


	/*
	//Test Loop
    while(1){
    	//Red
		Set_All(&currentRow, 255, 0, 0);
		Make_MSG(&currentMSG, &currentRow);
		Send_MSG(&currentMSG);
    	SysCtlDelay(delay);

    	//Orange
		Set_All(&currentRow, 255, 128, 0);
		Make_MSG(&currentMSG, &currentRow);
		Send_MSG(&currentMSG);
    	SysCtlDelay(delay);

    	//Yellow
		Set_All(&currentRow, 255, 255, 0);
		Make_MSG(&currentMSG, &currentRow);
		Send_MSG(&currentMSG);
		SysCtlDelay(delay);

    	//Yellow Green
		Set_All(&currentRow, 128, 255, 0);
		Make_MSG(&currentMSG, &currentRow);
		Send_MSG(&currentMSG);
		SysCtlDelay(delay);

    	//Green
		Set_All(&currentRow, 0, 255, 0);
		Make_MSG(&currentMSG, &currentRow);
		Send_MSG(&currentMSG);
		SysCtlDelay(delay);

    	//Light Green
		Set_All(&currentRow, 0, 255, 128);
		Make_MSG(&currentMSG, &currentRow);
		Send_MSG(&currentMSG);
		SysCtlDelay(delay);

    	//Light Blue
		Set_All(&currentRow, 0, 255, 255);
		Make_MSG(&currentMSG, &currentRow);
		Send_MSG(&currentMSG);
		SysCtlDelay(delay);

    	//Med Blue
		Set_All(&currentRow, 0, 128, 255);
		Make_MSG(&currentMSG, &currentRow);
		Send_MSG(&currentMSG);
		SysCtlDelay(delay);

    	//Blue
		Set_All(&currentRow, 0, 0, 255);
		Make_MSG(&currentMSG, &currentRow);
		Send_MSG(&currentMSG);
    	SysCtlDelay(delay);

    	//Purple
		Set_All(&currentRow, 127, 0, 255);
		Make_MSG(&currentMSG, &currentRow);
		Send_MSG(&currentMSG);
    	SysCtlDelay(delay);

    	//Violet
		Set_All(&currentRow, 255, 0, 255);
		Make_MSG(&currentMSG, &currentRow);
		Send_MSG(&currentMSG);
    	SysCtlDelay(delay);

    	//Pink
		Set_All(&currentRow, 255, 0, 127);
		Make_MSG(&currentMSG, &currentRow);
		Send_MSG(&currentMSG);
    	SysCtlDelay(delay);
    }
	*/
}

//*****************************************************************************
// Send the current message over SPI
//*****************************************************************************
void Send_MSG(LED_MSG *currentMSG){
	int i,j;
	for(i=NUM_MODULES;i>=0;i--){
		for(j=0;j<28;j++){
			SPI_Send(currentMSG->Packets[i].Packet[j]);
		}
		SPI_Wait();
	}
}

