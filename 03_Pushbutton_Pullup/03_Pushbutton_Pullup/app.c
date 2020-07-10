/*
 * File:   app.c
 * Author: Armstrong Subero
 * Processor: SAMD21G18A @ 48MHz, 3.3v
 * Program: Source file for application
 * Compiler: ARM-GCC (v6.3.1, Atmel Studio 7.0)
 * Program Version 1.0
 * Program Description: This file contains your application source
 *
 * Modified From: None
 * 
 * Change History:
 *
 * Author             Rev     Date          Description
 * Armstrong Subero   1.0     26/05/2020    Initial Release.
 * 
 * Updated on May 27, 2020, 01:50 PM
 */

//////////////////////////////////////////////////////////////////////////
// Include and defines
//////////////////////////////////////////////////////////////////////////
#include "app.h"
#include "clock.h"

/*******************************************************************************
 * Function:        void AppInit(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This routine takes care of all of the 1-time hardware/software
 *                  initialization that is required.
 *
 * Note:            This was taken from the _00_LED_ON provided by
 *                  Microchip Technology Inc. 
 *
 ******************************************************************************/
void AppInit(void)
{
	/*	Clock initialization (CPU, AHB, APBx, Asynchronous Peripheral Clocks)
		The System RC Oscillator (RCSYS) provides the source for the main clock
		at chip startup. It is set to 1MHz.
	*/
	ClocksInit();
	
	// Assign LED0 as OUTPUT
	REG_PORT_DIR0 = LED0_PIN_MASK;
	
	// Set LED0 OFF
	REG_PORT_OUTCLR0 = LED0_PIN_MASK;
	
	// Assign Switch on PA16 as INPUT
	PORT->Group[0].PINCFG[16].reg = PORT_PINCFG_INEN;

} // AppInit()


/*******************************************************************************
 * Function:        void AppRun(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function contains your main application
 *                  
 *
 * Note:
 *
 ******************************************************************************/
void AppRun(void)
{
	// Set the drive strength to strong
	PORT->Group[LED0_PORT].PINCFG[LED0_PIN_NUMBER].bit.DRVSTR = 1;
	
	while(1)
	{
		
		// pull down mode 
		// so we keep LED off
		if((PORT->Group[0].IN.reg & PORT_PA16) != 0)
		{
			// keep LED off
			REG_PORT_OUTCLR0 = LED0_PIN_MASK;
		}
		
		else
		{
			// turn LED on
			REG_PORT_OUTSET0 = LED0_PIN_MASK;
		}
	}

} // Apprun()

