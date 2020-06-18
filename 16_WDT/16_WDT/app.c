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
 * Updated on June 17, 2020, 10:16 PM
 */

//////////////////////////////////////////////////////////////////////////
// Include and defines
//////////////////////////////////////////////////////////////////////////
#include "app.h"
#include "clock.h"

#define F_CPU 48000000UL
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



////////////////////////
// Setup the WDT Timer
////////////////////////

void wdt_init(void)
{
	// Set up the generic clock (GCLK2) used to clock the watchdog timer at 1.024kHz
	REG_GCLK_GENDIV = GCLK_GENDIV_DIV(4) |            // Divide the 32.768kHz clock source by divisor 32, where 2^(4 + 1): 32.768kHz/32=1.024kHz
	GCLK_GENDIV_ID(2);                                // Select Generic Clock (GCLK) 2
	while (GCLK->STATUS.bit.SYNCBUSY);                // Wait for synchronization

	REG_GCLK_GENCTRL = GCLK_GENCTRL_DIVSEL |          // Set to divide by 2^(GCLK_GENDIV_DIV(4) + 1)
	GCLK_GENCTRL_IDC |             // Set the duty cycle to 50/50 HIGH/LOW
	GCLK_GENCTRL_GENEN |           // Enable GCLK2
	GCLK_GENCTRL_SRC_OSCULP32K |   // Set the clock source to the ultra low power oscillator (OSCULP32K)
	GCLK_GENCTRL_ID(2);            // Select GCLK2
	while (GCLK->STATUS.bit.SYNCBUSY);                // Wait for synchronization

	// Feed GCLK2 to WDT (Watchdog Timer)
	REG_GCLK_CLKCTRL = GCLK_CLKCTRL_CLKEN |           // Enable GCLK2 to the WDT
	GCLK_CLKCTRL_GEN_GCLK2 |       // Select GCLK2
	GCLK_CLKCTRL_ID_WDT;           // Feed the GCLK2 to the WDT
	while (GCLK->STATUS.bit.SYNCBUSY);                // Wait for synchronization

	REG_WDT_CONFIG = WDT_CONFIG_PER_4K;               // Set the WDT reset timeout to 4 seconds
	while(WDT->STATUS.bit.SYNCBUSY);                  // Wait for synchronization
	REG_WDT_CTRL = WDT_CTRL_ENABLE;                   // Enable the WDT in normal mode
	while(WDT->STATUS.bit.SYNCBUSY);                  // Wait for synchronization
}

void wdt_clear(void)
{
	if (!WDT->STATUS.bit.SYNCBUSY)                  // Check if the WDT registers are synchronized
	{
		REG_WDT_CLEAR = WDT_CLEAR_CLEAR_KEY;        // Clear the watchdog timer
	}
}



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
	
	// Turn the LED on PA17 ON
	REG_PORT_OUTSET0 = LED0_PIN_MASK;
	delay_ms(1000);
	REG_PORT_OUTCLR0 = LED0_PIN_MASK;
	delay_ms(1000);

	// setup the WDT for 1 second timeout
	wdt_init();
	
	while(1)
	{
		// clear the watchdog timer
		//wdt_clear();
	}

} // Apprun()

