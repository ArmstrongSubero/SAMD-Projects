/*
 * File:   sleep.c
 * Author: Armstrong Subero
 * Processor: SAMD21G18A @ 48MHz, 3.3v
 * Program: Source file for application
 * Compiler: ARM-GCC (v6.3.1, Atmel Studio 7.0)
 * Program Version 1.0
 * Program Description: This file contains source code for 
 *                      putting the MCU in sleep mode
 *
 * Modified From: None
 * 
 * Change History:
 *
 * Author                Rev     Date          Description
 * Armstrong Subero      1.0     25/05/2020    Initial Release
 *
 * Updated on June 17, 2020, 08:35 PM
 */

//////////////////////////////////////////////////////////////////////////
// Include and defines
//////////////////////////////////////////////////////////////////////////
#include "sleep.h"


/*******************************************************************************
 * Function:        void StandbySleep(void)
 *
 * PreCondition:    None
 *
 * Input:           Delay in clock cycles
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function puts the MCU in sleep mode
 *
 * Note:
 *
 ******************************************************************************/
void StandbySleep(void)
{
	// Disable interrupts
	__disable_irq();
	__DMB();
	
	// Select STANDBY sleep mode
	SCB->SCR |=  SCB_SCR_SLEEPDEEP_Msk;
	
	// Wait for Interrupt
	__DSB();
	__WFI();
	
	// Enable interrupts
	__DMB();
	__enable_irq();
}
