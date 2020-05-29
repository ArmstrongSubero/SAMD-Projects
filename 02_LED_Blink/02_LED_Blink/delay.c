/*
 * File:   delay.c
 * Author: Armstrong Subero
 * Processor: SAMD21G18A @ 48MHz, 3.3v
 * Program: Source file for application
 * Compiler: ARM-GCC (v6.3.1, Atmel Studio 7.0)
 * Program Version 1.0
 * Program Description: This file contains source code for 
 *                      delaying a number of CPU cycles
 *
 * Modified From: None
 * 
 * Change History:
 *
 * Author                Rev     Date          Description
 * Armstrong Subero      1.0     25/05/2020    Initial Release
 *
 * Updated on May 26, 2020, 11:47 AM
 */


//////////////////////////////////////////////////////////////////////////
// Include and defines
//////////////////////////////////////////////////////////////////////////
#include "delay.h"


/*******************************************************************************
 * Function:        void delay_n_cycles(unsigned long n)
 *
 * PreCondition:    None
 *
 * Input:           Delay in clock cycles
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This functions allows for delay in CPU cycles
 *
 * Note:
 *
 ******************************************************************************/

void delay_n_cycles(unsigned long n)
{
	__asm (
	"loop: DMB	\n"
	"SUB r0, r0, #1 \n"
	"CMP r0, #0  \n"
	"BNE loop         "
	);
} // delay_n_cycles()



