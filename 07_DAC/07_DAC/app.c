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
 * Updated on May 26, 2020, 11:40 AM
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
	/* -------------------------------------------------
	* 1) Enable bus clock to APBC mask
	*/
	REG_PM_APBCMASK |=  PM_APBCMASK_DAC;
	
	
    /* -------------------------------------------------
	* 2) select DAC clock
	*/
	GCLK->CLKCTRL.reg = 
	GCLK_CLKCTRL_ID(DAC_GCLK_ID) |  // select DAC clock
	GCLK_CLKCTRL_CLKEN |            // enable the clock
	GCLK_CLKCTRL_GEN(0);            //  select GCLK GEN0
	
	
	/* -------------------------------------------------
	* 3) reset DAC to its initial settings and disable
	*/
	DAC->CTRLA.reg = DAC_CTRLA_SWRST;
	
	
	/* -------------------------------------------------
	* 4) Configure Parameters 
	*/
	// set vref as avcc
	DAC->CTRLB.bit.REFSEL = DAC_CTRLB_REFSEL_AVCC_Val;
	
	// enable external output, will put DAC output to
	// internal ADC positive MUX input and to the
	// Vout PIN PA02
	DAC->CTRLB.bit.EOEN = 1;
	
	/* -------------------------------------------------
	* 5) Enable the DAC
	*/
	DAC->CTRLA.bit.ENABLE = 1;
	
	
	while(1)
	{
		// write values to DAC
		for (int i = 0; i < 1023; i++)
		{
			// convert the 10-bit value into voltage by the DAC
			REG_DAC_DATA = i;
		}
	}

} // Apprun()

