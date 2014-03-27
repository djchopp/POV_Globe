//*****************************************************************************
// Filename: POV_Helper.c
// Author: Derek Chopp
// Last Update: 3/25/14
//
// Description: Helper functions for the POV Globe.
// Use this section to manipulate the LED data.
//
// TODO:
// Cleanup...
// Add functions as needed
//
//*****************************************************************************

#include "POV_Helper.h"

void POV_Init(LED_Array *LEDS){
	int i,j;

	for(i=0;i<NUM_MODULES;i++){
		for(j=0;j<4;j++){
			LEDS->M[i].D[j].R = 0;
			LEDS->M[i].D[j].G = 0;
			LEDS->M[i].D[j].B = 0;
		}
	}
}

void POV_Make_MSG(LED_MSG *msg, LED_Array *LEDS){
	int i;


	for(i=0;i<NUM_MODULES;i++){
		msg->Packets[i].Packet[0] = CTRL0;
		msg->Packets[i].Packet[1] = CTRL1;
		msg->Packets[i].Packet[2] = CTRL2;
		msg->Packets[i].Packet[3] = CTRL3;
		msg->Packets[i].Packet[4] = ((LEDS->M[i].D[3].B)>>8)&0xFF;
		msg->Packets[i].Packet[5] = ((LEDS->M[i].D[3].B))&0xFF;
		msg->Packets[i].Packet[6] = ((LEDS->M[i].D[3].G)>>8)&0xFF;
		msg->Packets[i].Packet[7] = ((LEDS->M[i].D[3].G))&0xFF;
		msg->Packets[i].Packet[8] = ((LEDS->M[i].D[3].R)>>8)&0xFF;
		msg->Packets[i].Packet[9] = ((LEDS->M[i].D[3].R))&0xFF;

		msg->Packets[i].Packet[10] = ((LEDS->M[i].D[2].B)>>8)&0xFF;
		msg->Packets[i].Packet[11] = ((LEDS->M[i].D[2].B))&0xFF;
		msg->Packets[i].Packet[12] = ((LEDS->M[i].D[2].G)>>8)&0xFF;
		msg->Packets[i].Packet[13] = ((LEDS->M[i].D[2].G))&0xFF;
		msg->Packets[i].Packet[14] = ((LEDS->M[i].D[2].R)>>8)&0xFF;
		msg->Packets[i].Packet[15] = ((LEDS->M[i].D[2].R))&0xFF;

		msg->Packets[i].Packet[16] = ((LEDS->M[i].D[1].B)>>8)&0xFF;
		msg->Packets[i].Packet[17] = ((LEDS->M[i].D[1].B))&0xFF;
		msg->Packets[i].Packet[18] = ((LEDS->M[i].D[1].G)>>8)&0xFF;
		msg->Packets[i].Packet[19] = ((LEDS->M[i].D[1].G))&0xFF;
		msg->Packets[i].Packet[20] = ((LEDS->M[i].D[1].R)>>8)&0xFF;
		msg->Packets[i].Packet[21] = ((LEDS->M[i].D[1].R))&0xFF;

		msg->Packets[i].Packet[22] = ((LEDS->M[i].D[0].B)>>8)&0xFF;
		msg->Packets[i].Packet[23] = ((LEDS->M[i].D[0].B))&0xFF;
		msg->Packets[i].Packet[24] = ((LEDS->M[i].D[0].G)>>8)&0xFF;
		msg->Packets[i].Packet[25] = ((LEDS->M[i].D[0].G))&0xFF;
		msg->Packets[i].Packet[26] = ((LEDS->M[i].D[0].R)>>8)&0xFF;
		msg->Packets[i].Packet[27] = ((LEDS->M[i].D[0].R))&0xFF;
	}
}

void POV_Prepare_Data(LED_Array *LEDS, unsigned char *newData){
	int i, j;
	for(i=0;i<NUM_MODULES;i++){
		for(j=0;j<4;j++){
			LEDS->M[i].D[j].R = newData[0+3*j+12*i] * multiplier;
			LEDS->M[i].D[j].G = newData[1+3*j+12*i] * multiplier;
			LEDS->M[i].D[j].B = newData[2+3*j+12*i] * multiplier;
		}
	}
}

void POV_Shift_Up(LED_Array *LEDS, uint16_t newRed, uint16_t newBlue, uint16_t newGreen){
	int i,j;


	for(i=(NUM_MODULES-1);i>=0;i--){
		for(j=3;j>0;j--){
			LEDS->M[i].D[j].R = LEDS->M[i].D[j-1].R;
			LEDS->M[i].D[j].G = LEDS->M[i].D[j-1].G;
			LEDS->M[i].D[j].B = LEDS->M[i].D[j-1].B;
		}
		if(i>0){
			LEDS->M[i].D[j].R = LEDS->M[i-1].D[3].R;
			LEDS->M[i].D[j].G = LEDS->M[i-1].D[3].G;
			LEDS->M[i].D[j].B = LEDS->M[i-1].D[3].B;
		}
	}

	LEDS->M[0].D[0].R = newRed;
	LEDS->M[0].D[0].G = newGreen;
	LEDS->M[0].D[0].B = newBlue;

}

void POV_Set_All(LED_Array *LEDS, uint16_t newRed, uint16_t newBlue, uint16_t newGreen){
	int i,j;

	for(i=0;i<NUM_MODULES;i++){
		for(j=0;j<4;j++){
			LEDS->M[i].D[j].R = newRed * multiplier;
			LEDS->M[i].D[j].G = newBlue * multiplier;
			LEDS->M[i].D[j].B = newGreen * multiplier;
		}
	}
}


