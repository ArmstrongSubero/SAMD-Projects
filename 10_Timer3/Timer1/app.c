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
 * Updated on May 31, 2020, 02:12 AM
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
	
    // Set the LED drive strength to strong
    PORT->Group[LED0_PORT].PINCFG[LED0_PIN_NUMBER].bit.DRVSTR = 1;
		
	/* -------------------------------------------------
	* 1) Enable bus clock to APBC mask
	*/
	REG_PM_APBCMASK |=  PM_APBCMASK_TC3;
	
	
    /* -------------------------------------------------
	* 2) select TC3 clock
	*/
	GCLK->CLKCTRL.reg = 
	GCLK_CLKCTRL_ID(GCLK_CLKCTRL_ID_TCC2_TC3) |  // select TC3 clock
	GCLK_CLKCTRL_CLKEN |                         // enable the clock
	GCLK_CLKCTRL_GEN(0);                         //  select GCLK GEN0
	    	
	 /* -------------------------------------------------
	 * 3) Configure Timer3 Operation
	 */	
	 // disable TC3
	 TC3->COUNT16.CTRLA.bit.ENABLE = 0;

     // Configure Count Mode (16-bit)
     TC3->COUNT16.CTRLA.bit.MODE = 0x0;
	  
	 // set TC3 to normal frequency
	 TC3->COUNT16.CTRLA.reg |= TC_CTRLA_WAVEGEN_NFRQ; 
	 
	 
	 /* -------------------------------------------------
	 * 4) Set Prescaler
	 */
     // Set PRescaler
	 // 6 Hz
	 // 48 000 000 / 64 / 65535 / 2
     TC3->COUNT16.CTRLA.reg |= TC_CTRLA_PRESCALER_DIV64;   
	  
	  
	 /* -------------------------------------------------
	 * 5) Set Interrupts and enable timer
	 */ 
	 // Interrupts
	 TC3->COUNT16.INTENSET.reg = 0;              // disable interrupts
	 TC3->COUNT16.INTENSET.bit.MC0 = 1;          // enable compare match interrupt

	 // Enable TC
	 TC3->COUNT16.CTRLA.reg |= TC_CTRLA_ENABLE;
	 
	 // Wait for Sync	
	 while (TC3->COUNT16.STATUS.bit.SYNCBUSY == 1); 
	  
	 // Set interrupt priority
	 NVIC_SetPriority(TC3_IRQn, 3);	
	 
	 // Enable Interrupt Vector
	 NVIC_EnableIRQ(TC3_IRQn);
	  
	 
	 while(1)
	 {
		 
	 }

} // Apprun()


/*******************************************************************************
 * Function:        void TC3_Handler(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This is our Timer3 Interrupt handler
 *
 * Note:
 *
 ******************************************************************************/

void TC3_Handler(void)
{
	// interrupt occurred on timer overflow
	if (TC3->COUNT16.INTFLAG.bit.OVF == 1)
	{  
		// toggle the LED
		REG_PORT_OUTTGL0 = LED0_PIN_MASK;

		// write a 1 to clear the OVF flag
		REG_TC3_INTFLAG = 1;
	}
	
}