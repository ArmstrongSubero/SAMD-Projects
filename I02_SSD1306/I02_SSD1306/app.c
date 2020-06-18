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

#define F_CPU 48000000UL
#include "delay.h"

#include "I2C1.h"
#include "ssd1306.h"

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
    // Set the drive strength to strong
	PORT->Group[LED0_PORT].PINCFG[LED0_PIN_NUMBER].bit.DRVSTR = 1;
		
	// Turn the LED on PA17 ON
	REG_PORT_OUTSET0 = LED0_PIN_MASK;
	
	I2C1_init();
	
	// Initialize OLED
	OLED_Init();
	
	delay_ms(1000);
	
    // clear OLED
	OLED_Clear();
	
    int count = 0;
	
	while(1)
	{
	    /////////////////////
	    // Strings
	    ///////////////////
	    
	    OLED_YX( 0, 0 );
	    OLED_Write_String( "OLED SSD1306" );
	    
	    OLED_YX(1, 0);
	    OLED_Write_String ("No Buffer");
	    
	    OLED_YX(2, 0);
	    OLED_Write_String("For SAMD21");
	    
	    OLED_YX(3,0);
	    OLED_Write_String("by Armstrong");
	    
	    delay_ms(1000);
	    OLED_Clear();
	    delay_ms(100);
	    
	    /////////////////////
	    // Integer Count
	    ////////////////////
	    
	    for (count = 0; count <= 1024; count++){
		    OLED_YX( 0, 0 );
		    OLED_Write_String( "Integer Count:" );
		    OLED_YX(2, 0);
		    OLED_Write_Integer(count);
		    delay_ms(100);
	    }
	    
	    OLED_Clear();
	    delay_ms(100);
	    
	}

} // Apprun()

