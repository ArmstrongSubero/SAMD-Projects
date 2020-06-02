/*
 * File:   app.c
 * Author: Armstrong Subero
 * Processor: SAMD21G18A @ 48MHz, 3.3v
 * Program: Source file for application
 * Compiler: ARM-GCC (v6.3.1, Atmel Studio 7.0)
 * Program Version 1.0
 * Program Description: This file contains your application source
 *
 * Modified From: Microchip Technology Inc. Example
 * Copyright: Copyright (C) 2017 Microchip Technology Inc. and its subsidiaries
 * 
 * Change History:
 *
 * Author                 Rev     Date          Description
 * Armstrong Subero       1.0     31/05/2020    Modified for SAMD21G18A
 * Microchip Technology   1.0     30/11/2017    Initial Release.
 * 
 * Updated on May 31, 2020, 11:47 AM
 */

//////////////////////////////////////////////////////////////////////////
// Include and defines
//////////////////////////////////////////////////////////////////////////
#include "app.h"
#include "clock.h"


//////////////////////////////////////////////////////////////////////////
// Global Variables
//////////////////////////////////////////////////////////////////////////

// Global state variable for tick count
static uint32_t ul_tickcount=0 ;	


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
	
	// Configure SysTick to trigger every millisecond using the CPU Clock
	SysTick->CTRL = 0;					 // Disable SysTick
	SysTick->LOAD = 47999UL;		     // Set reload register for 1mS interrupts (48 MHz clk)
	NVIC_SetPriority(SysTick_IRQn, 3);	 // Set interrupt priority to least urgency
	SysTick->VAL = 0;					 // Reset the SysTick counter value
	
	 // Enable SysTick, Enable SysTick Exceptions, Use CPU Clock
	 SysTick->CTRL  = 
	    SysTick_CTRL_CLKSOURCE_Msk |
	    SysTick_CTRL_TICKINT_Msk   |
	    SysTick_CTRL_ENABLE_Msk;
	
	// Enable SysTick Interrupt     			
	NVIC_EnableIRQ(SysTick_IRQn);		
	
	while(1)
	{
		
	}

} // Apprun()


/*******************************************************************************
 * Function:        void SysTick_Handler(void)
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
void SysTick_Handler(void){
	// increment tickcount
	ul_tickcount++ ;
	
	// Toggle LEDs 500 ms
	if(ul_tickcount % 500 == 0)
	{
	   // Toggle LED pin output level.
	   PORT->Group[LED0_PORT].OUTTGL.reg = LED0_PIN_MASK;
	}
}
