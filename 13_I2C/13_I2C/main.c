/*
 * File:   main.c
 * Author: Armstrong Subero
 * Processor: SAMD21G18A @ 48MHz, 3.3v
 * Program: Source file for application
 * Compiler: ARM-GCC (v6.3.1, Atmel Studio 7.0)
 * Program Version 1.0
 * Program Description: This is the main file
 * Hardware Description: A CP2014 USB-UART module is connected through a logic
 *                       level converter as follows:
 *
 *                       GND -> GND
 *                       TX -> PIN32 (PA23)   
 *                       RX -> PIN31 (PA22)
 *       
 *                       Also a 24LC16B EEPROM is connected to MCU in I2C mode,
 *                       all pins grounded, default address 0x50 
 *                       PA16 is SDA 
 *                       PA17 is SCL
 *
 * Modified From: None
 * 
 * Change History:
 *
 * Author                Rev     Date          Description
 * Armstrong Subero      1.1     26/05/2020    Initial Release
 *
 * Updated on June 02, 2020, 05:16 PM
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




