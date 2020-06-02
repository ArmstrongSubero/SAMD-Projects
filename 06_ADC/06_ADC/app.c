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
 * Updated on May 29, 2020, 12:30 PM
 */

//////////////////////////////////////////////////////////////////////////
// Include and defines
//////////////////////////////////////////////////////////////////////////
#include "app.h"
#include "clock.h"

#define F_CPU 48000000UL
#include "delay.h"

#include "adc.h"

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
	// variable to store result of ADC conversion
	int result;
	
	// initialize the ADC
	adc_init();
	
	while(1)
	{
		// read the ADC channel 19 (PA11)
		result =  adc_readchannel(19);
		
		// if result under threshold keep LED off
		if (result < 512)
		{
			
	      // Set LED0 OFF
	      REG_PORT_OUTCLR0 = LED0_PIN_MASK;
		}
		
		// if result is over threshold turn LED on
		else if (result > 512)
		{
			// Set LED0 ON
			REG_PORT_OUTSET0 = LED0_PIN_MASK;
		}
		
        // small delay
		delay_ms(100);
	}

} // Apprun()

