/*
 * File:   main.c
 * Author: Armstrong Subero
 * Processor: SAMD21G18A @ 48MHz, 3.3v
 * Program: Source file for application
 * Compiler: ARM-GCC (v6.3.1, Atmel Studio 7.0)
 * Program Version 1.0
 * Program Description: This program allows us to write data to an 
 *                      SD Card and then read from it.
 * 
 *                      Tested with SD cards from sizes 4 GB, 8 GB and 32 GB
 *                      with speed classes 4, 4 and 6 respectively. Cannot
 *                      guarantee how it will perform with other SD cards 
 * 
 * Hardware Description: A CP2014 USB-UART module is connected through a logic
 *                       level converter to SERCOM3 as follows:
 *                       
 *                       GND -> GND
 *                       TX -> PIN32 (PA23)   
 *                       RX -> PIN31 (PA22)
 *                       
 *                       A SD Card is connected to SERCOM1 as follows:
 *                       SS   -> PA08 (PIN13)
 *                       MISO -> PAD2 (PIN27)
 *                       SCK  -> PAD3 (PIN28)
 *                       MOSI -> PAD0 (PIN25)
 *                       
 *
 * Modified From: Heavy rework of the ChaN's FATfs Library
 * 
 * Change History:
 *
 * Author                Rev     Date          Description
 * Armstrong Subero      1.0     04/06/2020    Initial Release
 *
 * Updated on June 04, 2020, 03:01 PM
 */


//////////////////////////////////////////////////////////////////////////
// Include and defines
//////////////////////////////////////////////////////////////////////////
#include "sam.h"
#include "definitions.h"
#include "app.h"

//////////////////////////////////////////////////////////////////////////
// Function Prototypes
//////////////////////////////////////////////////////////////////////////
void ClocksInit(void);	// Configure Clock, Wait States and synch, bus clocks for 48MHz operation


/*******************************************************************************
 * Function:        void main(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This interrupt handler is called on SysTick timer underflow
 *
 * Note:
 *
 ******************************************************************************/
int main(void)
{
	// CMSIS compliant function not used
	//SystemInit();
	
	// Application hardware and software initialization 
	AppInit();

	// Super loop
	while(1)
	{
		// Run your application
		AppRun();
	}
} // main()




