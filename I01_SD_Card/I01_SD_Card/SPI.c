/*
 * File:   SPI.c
 * Author: Armstrong Subero
 * Processor: SAMD21G18A @ 48MHz, 3.3v
 * Program: Source file for application
 * Compiler: ARM-GCC (v6.3.1, Atmel Studio 7.0)
 * Program Version 1.0
 * Program Description: This file contains source code for 
 *                      using the SPI module and SD card 
 *                      communication routines
 *
 * Modified From: None
 * 
 * Change History:
 *
 * Author                Rev     Date          Description
 * Armstrong Subero      1.1     04/06/2020    Added SD Card Support
 * Armstrong Subero      1.0     01/05/2020    Initial Release
 *
 * Updated on June 04th, 2020, 11:30 AM
 */ 


//////////////////////////////////////////////////////////////////////////
// Include and defines
//////////////////////////////////////////////////////////////////////////
#include "app.h"
#include "SPI.h"


/*******************************************************************************
 * Function:        void SPI_Initialize_Fast(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function initializes the SPI bus at 12 MHz baud
 *                  
 *
 * Note:            Needed for SPI initial slow function
 *
 ******************************************************************************/
void SPI_Initialize_Fast(void)
{
	  // Wait Sync
	  while(SERCOM1->SPI.SYNCBUSY.bit.ENABLE);
	
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
	  
	  while(GCLK->STATUS.bit.SYNCBUSY);
	  
      /* -------------------------------------------------
	  * 3) setup pins
	  */ 
	  //Using the WRCONFIG register to bulk configure PA16 for being configured the SERCOM1 SPI MASTER MISO
	  PORT->Group[0].WRCONFIG.reg =
	       PORT_WRCONFIG_WRPINCFG |		                 //Enables the configuration of PINCFG
	       PORT_WRCONFIG_WRPMUX |						 //Enables the configuration of the PMUX for the selected pins
	       PORT_WRCONFIG_PMUXEN |						 //Enables the PMUX for the pins
	       PORT_WRCONFIG_PMUX(MUX_PA18C_SERCOM1_PAD2) |	 //Bulk configuration for PMUX "C" for SERCOM1
	       PORT_WRCONFIG_HWSEL |						 //Select the correct pin configurations for 16-31
	       PORT_WRCONFIG_INEN |									 //Enable input on this pin MISO
	       PORT_WRCONFIG_PINMASK((uint16_t)((PORT_PA18) >> 16)); //Selecting which pin is configured  PA17 
	       
	       //Using the WRCONFIG register to bulk configure both PB22 and PB23 for being configured the SERCOM1 SPI MASTER MOSI and SCK pins
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
	   SERCOM1->SPI.CTRLA.bit.ENABLE = 0;

       // Wait for synchronization 
       while(SERCOM1->SPI.SYNCBUSY.bit.SWRST)
	   {
		   
	   }

       // Perform a software reset 
       SERCOM1->SPI.CTRLA.bit.SWRST = 1;
		   
       // Wait for synchronization 
       while(SERCOM1->SPI.CTRLA.bit.SWRST)
	   {
		   
	   }
	   
	   /* Wait for synchronization */
	   while(SERCOM1->SPI.SYNCBUSY.bit.SWRST || SERCOM1->SPI.SYNCBUSY.bit.ENABLE);

	   SERCOM1->SPI.CTRLA.reg = 
	   SERCOM_SPI_CTRLA_MODE_SPI_MASTER |   // set SPI Master Mode
	   SERCOM_SPI_CTRLA_DIPO(2) |           // PAD2 is used as data input
	   SERCOM_SPI_CTRLA_DOPO(3);            // PAD0 is used as data output, PAD3 is SCK, PAD1 is SS
		 
	   SERCOM1->SPI.CTRLB.reg = SERCOM_SPI_CTRLB_RXEN;      // Enable SPI Receive enable
	
	   /* -------------------------------------------------
	   * 5) Set the baud rate
	   */ 
	   uint32_t BAUD_REG =  ((float)48000000 / (float)(2 * 12000000)) - 1;	//Calculate BAUD value
	   SERCOM1->SPI.BAUD.reg =	SERCOM_SPI_BAUD_BAUD(BAUD_REG);
		
		
	   /* -------------------------------------------------
	   * 6) Enable SPI Module
	   */ 
	    // enable SPI receive
	    
	    SERCOM1->SPI.CTRLA.reg |= SERCOM_SPI_CTRLA_ENABLE;	//Enable the SPI
	    while(SERCOM1->SPI.SYNCBUSY.bit.ENABLE);
}

/*******************************************************************************
 * Function:        void SPI_Initialize_Slow(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function initializes the SPI bus at 400 kHz baud
 *                  
 *
 * Note:            Needed for SPI initial slow function
 *
 ******************************************************************************/
void SPI_Initialize_Slow(void)
{
	  // Wait Sync
	  while(SERCOM1->SPI.SYNCBUSY.bit.ENABLE);
	
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
	  
	  while(GCLK->STATUS.bit.SYNCBUSY);
	  
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
	   SERCOM1->SPI.CTRLA.bit.ENABLE = 0;

       // Wait for synchronization 
       while(SERCOM1->SPI.SYNCBUSY.bit.SWRST)
	   {
		   
	   }

       // Perform a software reset 
       SERCOM1->SPI.CTRLA.bit.SWRST = 1;
		   
       // Wait for synchronization 
       while(SERCOM1->SPI.CTRLA.bit.SWRST)
	   {
		   
	   }
	   
	   /* Wait for synchronization */
	   while(SERCOM1->SPI.SYNCBUSY.bit.SWRST || SERCOM1->SPI.SYNCBUSY.bit.ENABLE);

	   SERCOM1->SPI.CTRLA.reg = 
	   SERCOM_SPI_CTRLA_MODE_SPI_MASTER |   // set SPI Master Mode
	   SERCOM_SPI_CTRLA_DIPO(2) |           // PAD2 is used as data input
	   SERCOM_SPI_CTRLA_DOPO(3);            // PAD0 is used as data output, PAD3 is SCK, PAD1 is SS
		 
	   SERCOM1->SPI.CTRLB.reg = SERCOM_SPI_CTRLB_RXEN;      // Enable SPI Receive enable
	
	   /* -------------------------------------------------
	   * 5) Set the baud rate
	   */ 
	   uint32_t BAUD_REG =  ((float)48000000 / (float)(2 * 400000)) - 1;	//Calculate BAUD value
	   SERCOM1->SPI.BAUD.reg =	SERCOM_SPI_BAUD_BAUD(BAUD_REG);
		
		
	   /* -------------------------------------------------
	   * 6) Enable SPI Module
	   */ 
	    // enable SPI receive
	    
	    SERCOM1->SPI.CTRLA.reg |= SERCOM_SPI_CTRLA_ENABLE;	//Enable the SPI
	    while(SERCOM1->SPI.SYNCBUSY.bit.ENABLE);
}


/*******************************************************************************
 * Function:        uint8_t SPI_Exchange8bit(uint8_t data)
 *
 * PreCondition:    The SPI Bus Must be Initialized
 *
 * Input:           The data we want to send
 *
 * Output:          The data Exchanged via SPI
 *
 * Side Effects:    None
 *
 * Overview:        This function exchanges a byte of data on the SPI Bus
 *                  
 *
 * Note:            
 *
 ******************************************************************************/
uint8_t SPI_Exchange8bit(uint8_t data)
{
	while(SERCOM1->SPI.INTFLAG.bit.DRE == 0);
	SERCOM1->SPI.DATA.reg = data;
	
	while(SERCOM1->SPI.INTFLAG.bit.RXC == 0);
	return (uint8_t)SERCOM1->SPI.DATA.reg;
}


/*******************************************************************************
 * Function:        uint8_t SPI_SD_Send_Byte(uint8_t byte_val)
 *
 * PreCondition:    The SPI Bus Must be Initialized
 *
 * Input:           The data we want to send
 *
 * Output:          Data Exchanged on SPI Transfer
 *
 * Side Effects:    None
 *
 * Overview:        This function sends a byte of data to the SD Card
 *                  
 *
 * Note:            
 *
 ******************************************************************************/
uint8_t SPI_SD_Send_Byte(uint8_t byte_val)
{
	uint8_t data;
	
	data = SPI_Exchange8bit(byte_val);
	return data;
}



/*******************************************************************************
 * Function:        uint8_t SPI_SD_Read_Byte(void)
 *
 * PreCondition:    SPI Bus Must Be Initialized
 *
 * Input:           None
 *
 * Output:          Data Read from SPI Bus
 *
 * Side Effects:    None
 *
 * Overview:        This function reads a byte of data from the SPI Module
 *                  
 *
 * Note:            
 *
 ******************************************************************************/
uint8_t SPI_SD_Read_Byte(void)
{
	uint8_t data;

	data = SPI_Exchange8bit(0xff);
	return data;
}