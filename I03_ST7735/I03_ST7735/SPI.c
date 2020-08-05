/*
 * File:   SPI.c
 * Author: Armstrong Subero
 * Processor: SAMD21G18A @ 48MHz, 3.3v
 * Program: Source file for application
 * Compiler: ARM-GCC (v6.3.1, Atmel Studio 7.0)
 * Program Version 1.0
 * Program Description: This file contains source code for 
 *                      using the SPI module
 *
 * Modified From: None
 * 
 * Change History:
 *
 * Author                Rev     Date          Description
 * Armstrong Subero      1.0     25/05/2020    Initial Release
 *
 * Updated on August 05, 2020, 06:39 PM
 */


//////////////////////////////////////////////////////////////////////////
// Include and defines
//////////////////////////////////////////////////////////////////////////
#include "SPI.h"
#include "ST7735.h"

unsigned char* ARRAY_PORT_PINCFG0 = (unsigned char*)&REG_PORT_PINCFG0;
unsigned char* ARRAY_PORT_PMUX0 = (unsigned char*)&REG_PORT_PMUX0;


/*******************************************************************************
 * Function:        void spiInit(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This functions initializes the SPI module
 *
 * Note:
 *
 ******************************************************************************/
void spiInit(void)
{
	REG_PM_APBCMASK |= 0x00000008;          /* SERCOM1 bus clock */
	REG_GCLK_CLKCTRL = 0x4015;              /* SERCOM1 core clock */

	ARRAY_PORT_PINCFG0[16] |= 1;    /* allow pmux to set PA16 pin configuration */
	ARRAY_PORT_PINCFG0[17] |= 1;    /* allow pmux to set PA17 pin configuration */
	ARRAY_PORT_PINCFG0[18] |= 1;    /* allow pmux to set PA18 pin configuration */
	ARRAY_PORT_PINCFG0[19] |= 1;    /* allow pmux to set PA19 pin configuration */
	ARRAY_PORT_PMUX0[8] = 0x22;     /* PA16 = MOSI, PA17 = SCK */
	ARRAY_PORT_PMUX0[9] = 0x22;     /* PA18 = SS,   PA19 = MISO */

	REG_SERCOM1_SPI_CTRLA = 1;              /* reset SERCOM1 */
	while (REG_SERCOM1_SPI_CTRLA & 1) {}    /* wait for reset to complete */
	REG_SERCOM1_SPI_CTRLA = 0x0030000C;     /* MISO-3, MOSI-0, SCK-1, SS-2, SPI master */
	REG_SERCOM1_SPI_CTRLB = 0x00002000;     /* Master SS, 8-bit */
	REG_SERCOM1_SPI_BAUD = 0;               /* SPI clock is 1MHz/2 = 500kHz */
	REG_SERCOM1_SPI_CTRLA |= 2;             /* enable SERCOM1 */

	REG_PORT_DIRSET0 = RESET | DC;  /* PA08, PA09 set as output */
	REG_PORT_OUTCLR0 = RESET;       /* assert reset */
}


/*******************************************************************************
 * Function:        void spiSend(unsigned char data)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This functions sends data via the SPI module
 *
 * Note:
 *
 ******************************************************************************/
void spiSend(unsigned char data)
{
	while(!(REG_SERCOM1_SPI_INTFLAG & 1)) {}    /* wait until Tx ready */
	REG_SERCOM1_SPI_DATA = data;                /* send data byte */
}