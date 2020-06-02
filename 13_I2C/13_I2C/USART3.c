/*
 * File:   USART3.c
 * Author: Armstrong Subero
 * Processor: SAMD21G18A @ 48MHz, 3.3v
 * Program: Source file for application
 * Compiler: ARM-GCC (v6.3.1, Atmel Studio 7.0)
 * Program Version 1.0
 * Program Description: This file contains source code for 
 *                      using the UART3 module
 *
 * Modified From: None
 * 
 * Change History:
 *
 * Author                Rev     Date          Description
 * Armstrong Subero      1.0     01/05/2020    Initial Release
 *
 * Updated on June 01st, 2020, 06:09 PM
 */ 


//////////////////////////////////////////////////////////////////////////
// Include and defines
//////////////////////////////////////////////////////////////////////////
#include "app.h"
#include "USART3.h"


/*******************************************************************************
 * Function:        void UART3_Init(uint32_t baud)
 *
 * PreCondition:    None
 *
 * Input:           The baud rate we desire
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function initializes the UART3 Module
 *                  
 *
 * Note:            
 *
 ******************************************************************************/
void UART3_Init(uint32_t baud)
{
	
	/* -------------------------------------------------
	* 1) Enable bus clock to APBC mask
	*/
	REG_PM_APBCMASK |=  PM_APBCMASK_SERCOM3;
	
    /* -------------------------------------------------
	* 2) select UART clock
	*/
	GCLK->CLKCTRL.reg =  
	GCLK_CLKCTRL_ID(SERCOM3_GCLK_ID_CORE) |  // select the UART clock
	GCLK_CLKCTRL_CLKEN |                     // enable the clock
    GCLK_CLKCTRL_GEN(0);                     // set GCLK GEN(0)
	
	/* --------------------------------------------------
	* 3) Configure PA22 as TX Pin
	*/
	// Set pin direction to output
	PORT->Group[0].DIRSET.reg = (1 << 22);     
	
    // Enable PMUX
	PORT->Group[0].PINCFG[22].reg |= PORT_PINCFG_PMUXEN;   
	
	// Enable PMUX and set the PMUX bit, since pin is even we use PMUXE
	PORT->Group[0].PMUX[22>>1].bit.PMUXE = PORT_PMUX_PMUXE_C_Val;
	
	
	/* ---------------------------------------------------
	* 4) Configure PA23 as RX Pin
	*/
	// Set pin direction to input
	PORT->Group[0].DIRCLR.reg = (1 << 23);       

	// Enable pull down resistor
	PORT->Group[0].PINCFG[23].reg &= ~PORT_PINCFG_PULLEN;   
	
	// Enable PMUX and set the PMUX bit, since pin is odd we use PMUX0
	PORT->Group[0].PINCFG[23].reg |= PORT_PINCFG_PMUXEN; 
	PORT->Group[0].PMUX[23>>1].bit.PMUXO = PORT_PMUX_PMUXO_C_Val; 
	
	
	/* ----------------------------------------------------
	* 5) Configure USART via Control A and Control B 
	*/
	SERCOM3->USART.CTRLA.reg =                  // USART is ASYNCHRONOUS
	   SERCOM_USART_CTRLA_DORD |                // Transmit LSB First
	   SERCOM_USART_CTRLA_MODE_USART_INT_CLK |  // Set Internal Clock 
	   SERCOM_USART_CTRLA_RXPO(1) |             // Use SERCOM pad 1 for data reception
	   SERCOM_USART_CTRLA_TXPO(0/*PAD0*/);      // Set SERCOM pad 0 for data transmission
	
	
	SERCOM3->USART.CTRLB.reg =        // We don't use PARITY
	    SERCOM_USART_CTRLB_RXEN |     // Enable receive when USART in enabled
		SERCOM_USART_CTRLB_TXEN |     // Enable transmit when USART is enabled
		SERCOM_USART_CTRLB_CHSIZE(0); // Set character size to 8 bits
	
	/* -----------------------------------------------------
	* 6) Set USART Baud Rate
	*/
	// Baud rate is (65536) * (CPU_CLock - 16 * wanted baud) / CPU_Clock
	uint64_t baudRate = (uint64_t)65536 * (F_CPU - 16 * baud) / F_CPU;
	
	// Set Baud Rate
	SERCOM3->USART.BAUD.reg = (uint32_t)baudRate;
	

    /* ------------------------------------------------------
	* 7) Enable the USART
	*/
	// SERCOM3 peripheral enabled
	SERCOM3->USART.CTRLA.reg |= SERCOM_USART_CTRLA_ENABLE;
}  // UART3_Init()


/*******************************************************************************
 * Function:        void UART3_Write(char data)
 *
 * PreCondition:    The UART must be initialized
 *
 * Input:           The character we want to send
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function writes a character to the UART module
 *                  
 *
 * Note:            
 *
 ******************************************************************************/
void UART3_Write(char data)
{
	// Wait on interrupt flag and Write some data
	while(!(REG_SERCOM3_USART_INTFLAG) & 1)
	{
		
	}
	
	REG_SERCOM3_USART_DATA = data;
} //UART3_Write()


/*******************************************************************************
 * Function:        void UART3_Write_Text(char *text)
 *
 * PreCondition:    The UART must be initialized
 *
 * Input:           This text we want to send
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function writes a string to the UART module
 *                  
 *
 * Note:            
 *
 ******************************************************************************/
void UART3_Write_Text(char *text)
{
	// we write text until we reach EOL
	for(int i=0;text[i]!='\0';i++)
	{
		UART3_Write(text[i]);
	}
	
} // UART3_Write_Text()


/*******************************************************************************
 * Function:        void UART3_Write_Text(char *text)
 *
 * PreCondition:    The UART must be initialized
 *
 * Input:           None
 *
 * Output:          Bool stating if we have data or not
 *
 * Side Effects:    None
 *
 * Overview:        This function writes a string to the UART module
 *                  
 *
 * Note:            
 *
 ******************************************************************************/
bool UART3_Has_Data()
{
	// if we have data
	if ((SERCOM3->USART.INTFLAG.reg & SERCOM_USART_INTFLAG_RXC) >> SERCOM_USART_INTFLAG_RXC_Pos)
    {
		// return true
		return true;
	}
	
	// else return false
	return false;
}  // UART3_Has_Data()


/*******************************************************************************
 * Function:        char UART3_Read()
 *
 * PreCondition:    The UART must be initialized
 *
 * Input:           None
 *
 * Output:          Reads Data from the UART Module
 *
 * Side Effects:    None
 *
 * Overview:        This function writes a string to the UART module
 *                  
 *
 * Note:            
 *
 ******************************************************************************/
char UART3_Read()
{
	// return data in the USART data register
	return SERCOM3->USART.DATA.reg;
}  // UART3_Read()