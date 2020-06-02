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

#include "USART3.h"

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
	REG_PORT_DIR0 = PORT_PA15;
	
	// Set LED0 OFF
	REG_PORT_OUTCLR0 = PORT_PA15;
	

} // AppInit()



// Our SPI Send Function
uint8_t spiSend(uint8_t data)
{
	while(SERCOM1->SPI.INTFLAG.bit.DRE == 0);
	SERCOM1->SPI.DATA.reg = data;
	
	while(SERCOM1->SPI.INTFLAG.bit.RXC == 0);
	return (uint8_t)SERCOM1->SPI.DATA.reg;
}

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
	  PM->APBCMASK.reg |= PM_APBCMASK_SERCOM1;								
	  
	  
	  /* -------------------------------------------------
	  * 2) select SPI clock
	  */
	  GCLK->CLKCTRL.reg = 
	  GCLK_CLKCTRL_ID(SERCOM1_GCLK_ID_CORE) |				
	  GCLK_CLKCTRL_CLKEN | 
	  GCLK_CLKCTRL_GEN(0);
	  
      /* -------------------------------------------------
	  * 3) setup pins
	  */ 
	  //Using the WRCONFIG register to bulk configure PA16 for being configured the SERCOM5 SPI MASTER MISO
	  PORT->Group[0].WRCONFIG.reg =
	       PORT_WRCONFIG_WRPINCFG |		                 //Enables the configuration of PINCFG
	       PORT_WRCONFIG_WRPMUX |						 //Enables the configuration of the PMUX for the selected pins
	       PORT_WRCONFIG_PMUXEN |						 //Enables the PMUX for the pins
	       PORT_WRCONFIG_PMUX(MUX_PA18C_SERCOM1_PAD2) |	 //Bulk configuration for PMUX "C" for SERCOM1
	       PORT_WRCONFIG_HWSEL |						 //Select the correct pin configurations for 16-31
	       PORT_WRCONFIG_INEN |									 //Enable input on this pin MISO
	       PORT_WRCONFIG_PINMASK((uint16_t)((PORT_PA18) >> 16)); //Selecting which pin is configured  PA17 
	       
	       //Using the WRCONFIG register to bulk configure both PB22 and PB23 for being configured the SERCOM5 SPI MASTER MOSI and SCK pins
	       PORT->Group[0].WRCONFIG.reg =
	       PORT_WRCONFIG_WRPINCFG |							 //Enables the configuration of PINCFG
	       PORT_WRCONFIG_WRPMUX |							 //Enables the configuration of the PMUX for the selected pins
	       PORT_WRCONFIG_PMUX(MUX_PA16C_SERCOM1_PAD0) |		 //Bulk configuration for PMUX
	       PORT_WRCONFIG_PMUXEN |							 //Enables the PMUX for the pins
	       PORT_WRCONFIG_HWSEL |												//Select the correct pin configurations for 16-31
	       PORT_WRCONFIG_PINMASK ((uint16_t)((PORT_PA16 | PORT_PA19) >> 16));	//Selecting which pin is configured
	         
	       // Set the drive strength to strong
	       PORT->Group[0].PINCFG[19].bit.DRVSTR = 1;

       /* -------------------------------------------------
	   * 4) Configure SPI Module
	   */ 
	   // Disable the SERCOM SPI module 
	   SERCOM5->SPI.CTRLA.bit.ENABLE = 0;

       // Wait for synchronization 
       while(SERCOM5->SPI.SYNCBUSY.bit.SWRST);

       // Perform a software reset 
       SERCOM5->SPI.CTRLA.bit.SWRST = 1;
		   
       // Wait for synchronization 
       while(SERCOM5->SPI.CTRLA.bit.SWRST);

	   SERCOM1->SPI.CTRLA.reg = 
	   SERCOM_SPI_CTRLA_MODE_SPI_MASTER |   // set SPI Master Mode
	   SERCOM_SPI_CTRLA_DIPO(2) |           // PAD2 is used as data input
	   SERCOM_SPI_CTRLA_DOPO(3);            // PAD0 is used as data output, PAD3 is SCK, PAD1 is SS
		  
	   /* -------------------------------------------------
	   * 5) Set the baud rate
	   */ 
	   uint32_t BAUD_REG =  ((float)48000000 / (float)(2 * 1000000)) - 1;	//Calculate BAUD value
	   SERCOM1->SPI.BAUD.reg =	SERCOM_SPI_BAUD_BAUD(BAUD_REG);
		
		
	   /* -------------------------------------------------
	   * 6) Enable SPI Module
	   */ 
	    // enable SPI receive
	    SERCOM1->SPI.CTRLB.reg = SERCOM_SPI_CTRLB_RXEN;      // Enable SPI Recieve enable
	    SERCOM1->SPI.CTRLA.reg |= SERCOM_SPI_CTRLA_ENABLE;	//Enable the SPI
	    while(SERCOM1->SPI.SYNCBUSY.bit.ENABLE);
		   
	    // variable to hold our read data   
	    uint8_t Read_Data;
	   
	    // Initialize the UART at 9600 baud
	    UART3_Init(9600);
	    delay_ms(500);
	   
	   while(1) 
	   {
		 for (char c = '0'; c <= '8'; c++) 
		 { 	
			// Send character via SPI Bus
			UART3_Write_Text("Sen: ");
			UART3_Write(c);
			UART3_Write_Text("\n");
			Read_Data = spiSend(c);
			
			// Receive character via SPI Bus
			// and increment it
			UART3_Write_Text("Rec: ");
			UART3_Write(Read_Data + 1);
			UART3_Write_Text("\n");
			
			// Every Second
			delay_ms(1000);
		 }
	  }

} // Apprun()

