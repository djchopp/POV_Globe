//*****************************************************************************
// Filename: POV_Helper.h
// Author: Derek Chopp
// Last Update: 3/25/14
//
// Description: Header file for POV helper code
//
// TODO:
// same as POV_Helper.c
//
//*****************************************************************************

#ifndef POV_HELPER_H_
#define POV_HELPER_H_

#include <stdint.h>


//*****************************************************************************
// Define Constants
//*****************************************************************************
#define NUM_MODULES 2
#define NUM_ROWS 360

#define multiplier 2

#define CTRL0 0x96
#define CTRL1 0xC8
#define CTRL2 0xFF
#define CTRL3 0xFF


//*****************************************************************************
// Structures
//*****************************************************************************
//LED holds RGB data for individual LED's
typedef struct
{
	uint16_t R;
	uint16_t G;
	uint16_t B;
} LED;

//LED_Module holds 4 LED Structs to represent 1 LED board (Module)
typedef struct
{
	LED D[4];
} LED_Module;

//LED_Array holds a columns worth of LED_Module's
typedef struct
{
	LED_Module M[NUM_MODULES];
} LED_Array;

//LED Packet
typedef struct
{
	unsigned char Packet[28];
} LED_PACKET;

//LED Message
typedef struct
{
	LED_PACKET Packets[NUM_MODULES];
} LED_MSG;


//*****************************************************************************
// Function Prototypes
//*****************************************************************************
void POV_Init(LED_Array *LEDS);
void Make_MSG(LED_MSG *msg, LED_Array *LEDS);
void Set_All(LED_Array *LEDS, uint16_t newRed, uint16_t newBlue, uint16_t newGreen);
void Shift_Up(LED_Array *LEDS, uint16_t newRed, uint16_t newBlue, uint16_t newGreen);

#endif /* POV_HELPER_H_ */
