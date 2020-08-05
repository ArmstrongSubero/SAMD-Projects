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
 * Updated on August 05, 2020, 06:21 PM
 */

//////////////////////////////////////////////////////////////////////////
// Include and defines
//////////////////////////////////////////////////////////////////////////
#include "app.h"
#include "clock.h"
#include "SPI.h"
#include "delay.h"
#include <string.h>
#include <stdlib.h>

#include "ST7735.h"


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
	
	// Assign GLCD output pins
	REG_PORT_DIR0 = DC_PIN_MASK;
	REG_PORT_DIR0 = CS_PIN_MASK;
	REG_PORT_DIR0 = RST_PIN_MASK;
	
	// Set GLCD pins low
	REG_PORT_OUTCLR0 = DC_PIN_MASK;
	REG_PORT_OUTCLR0 = CS_PIN_MASK;
	REG_PORT_OUTCLR0 = RST_PIN_MASK;
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
	///////////////////////
	// Setup Display 
	//////////////////////
	spiInit();
	delay_ms(100);
	ST7735_Init();
	delay_ms(100);
	
	///////////////////////
	// Main Loop
	//////////////////////
	while(1)
	{
	   ST7735_test();
	}

} // Apprun()

