/*
 * File:   main.c
 * Author: Armstrong Subero
 * Processor: SAMD21G18A @ 48MHz, 3.3v
 * Program: Source file for application
 * Compiler: ARM-GCC (v6.3.1, Atmel Studio 7.0)
 * Program Version 1.0
 * Program Description: This is the main file
 * Hardware Description: An LED is connected to pin PA17 via a 1k resistor
 *                       The internal clock frequency can be viewed on PIN PA28
 *                       We also have a potentiometer connected to PIN PA11
 *
 * Modified From: None
 * 
 * Change History:
 *
 * Author                Rev     Date          Description
 * Armstrong Subero      1.2     29/05/2020    Updated Hardare Description for ADC
 * Armstrong Subero      1.1     26/05/2020    Initial Release
 *
 * Updated on May 29, 2020, 02:14 PM
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




