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
#include "I2C1.h"



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

} // AppInit()




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
	// Initialize the UART at 9600 baud
	UART3_Init(9600);
	delay_ms(500);
	
	// Initialize the I2C module
	UART3_Write_Text("Start Init\n");
	I2C1_init();
	UART3_Write_Text("Init Success\n");	
	
	
	// variable to hold our data
	uint8_t data;
	
	while(1)
	{
		UART3_Write_Text("Start Write\n");
		
		// write 10 to address 0x50 to location 0x20
		I2C1_write_byte(0x50, 0x20, 10);
		UART3_Write_Text("Write Stop\n");
		delay_ms(100);
		
		UART3_Write_Text("Start Read\n");
		// read data at address 0x20 and store it
		I2C1_read_byte(0x50, 0x20, &data);
		UART3_Write_Text("Stop Read\n");
		delay_ms(100);
		
		// get the data
		uint8_t my_Read = data;
		
		// see if the data matches
		if(my_Read==10)
		{
			UART3_Write_Text("Read Byte\n");
			UART3_Write_Text("Match\n");
			UART3_Write_Text("Read Byte Done\n");
		}
		
		// else we dont have a match
		else
		{
			UART3_Write_Text("No Match\n");
		}
		
		delay_ms(1000);	
	}
} // Apprun()

