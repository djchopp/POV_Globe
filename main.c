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

    //Initialize
    PortFunctionInit();
	SPI_Init();
	POV_Init(&currentLine);

	//SD card startup
    iFResult = f_mount(0, &g_sFatFs);
    if(iFResult != FR_OK) while(1);

    iFResult = f_open(&g_sFileObject,"LED.dat", FA_READ);
    if(iFResult != FR_OK) while(1);

    numData = SD_Read_Header();



	/*RPM Timer*/
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_ONE_SHOT_UP );

    rpmPeriod = SysCtlClockGet();
    TimerLoadSet(TIMER0_BASE, TIMER_A, rpmPeriod -1);

    IntEnable(INT_TIMER0A);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);


	/*Display timer*/
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
    TimerConfigure(TIMER1_BASE, TIMER_CFG_PERIODIC);

    displayPeriod = (SysCtlClockGet()/2);
    TimerLoadSet(TIMER1_BASE, TIMER_A, displayPeriod -1);

    IntEnable(INT_TIMER1A);
    TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);


    IntMasterEnable();

    //TimerEnable(TIMER0_BASE, TIMER_A);
    TimerEnable(TIMER1_BASE, TIMER_A);

    //Do nothing, timers handle all interaction from here on
	while(1){

	}
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


/*Reads in the number of data points. located at first 32 bits of data file*/
uint32_t SD_Read_Header(){
	uint32_t tempNum = 0;
	f_read(&g_sFileObject, buffer, 4, &br);
	tempNum = buffer[3];
	tempNum = tempNum | ((buffer[2]<<8) & 0xFF00);
	tempNum = tempNum | ((buffer[1]<<16) & 0xFF0000);
	tempNum = tempNum | ((buffer[0]<<24) & 0xFF000000);
	return tempNum;
}


void SD_Read_Line(){
	f_read(&g_sFileObject, buffer, 3*4*NUM_MODULES, &br);
	POV_Prepare_Data(&currentLine, buffer);
}

void Timer0IntHandler(void)
{

	// Clear the timer interrupt
	TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
}

void Timer1IntHandler(void)
{
	SD_Read_Line();//read data from sd card into currentLine

	POV_Make_MSG(&currentMSG, &currentLine);//construct message
	Send_MSG(&currentMSG);//send message

	packetCount+=4*NUM_MODULES;//update number of packets sent

	//if at end of file, go back to beginning
	if(packetCount>(numData-1)){
		packetCount = 0;
		f_lseek(&g_sFileObject, 4);
	}

	// Clear the timer interrupt
	TimerIntClear(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
}
