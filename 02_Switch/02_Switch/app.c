/*
 * File:   app.c
 * Author: Armstrong Subero
 * Processor: SAMD21G18A @ 48MHz, 3.3v
 * Program: Source file for application
 * Compiler: ARM-GCC (v6.3.1, Atmel Studio 7.0)
 * Program Version 1.0
 * Program Description: This program flashed an LED at 1 Hz using CPU Cycles
 *
 * Hardware Description: An LED is connected to PIN PA17 and a pushbutton is 
 *                       connected to PIN PA16
 *
 * Modified From: None
 * 
 * Change History:
 *
 * Author             Rev     Date          Description
 * Armstrong Subero   1.0     26/05/2020    Initial Release.
 * 
 * Updated on May 26, 2020, 11:40 AM
 */

//////////////////////////////////////////////////////////////////////////
// Include and defines
//////////////////////////////////////////////////////////////////////////
#include "app.h"
#include "clock.h"

#include "delay.h"

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
 * Note:            This was taken from the _01_LED_Blink provided by
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
	REG_PORT_DIR0 |= LED0_PIN_MASK;
	
	// Set LED0 OFF
	REG_PORT_DIR0 &= LED0_PIN_MASK;
	
	// Assign Switch on PA16 as INPUT
	PORT->Group[0].PINCFG[16].reg = PORT_PINCFG_INEN;

} // AppInit()



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
 * Overview:        This function contains your main application
 *                  
 *
 * Note:
 *
 ******************************************************************************/
void AppRun(void)
{
	// pull up mode normally high
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

} // Apprun()

