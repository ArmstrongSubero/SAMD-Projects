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
 * Armstrong Subero   1.1     06/04/2020    Updated for SD Card Specific Functions
 * Armstrong Subero   1.0     26/05/2020    Initial Release.
 * 
 * Updated on June 04, 2020, 02:47 PM
 */

//////////////////////////////////////////////////////////////////////////
// Include and defines
//////////////////////////////////////////////////////////////////////////

// Standard includes
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Primitives
#include "app.h"
#include "clock.h"
#include "USART3.h"
#include "SPI.h"

// FatFS Includes
#include "SD.h"
#include "diskio.h"
#include "ff.h"
#include "integer.h"
#include "ffconf.h"

// file handlers
FATFS fs;     // our work area
FRESULT FR;   // error results
FIL fil;      // file object
UINT bw;      // variable for pointer to number of bytes

// our data file
char data_file[12]="Data.csv";


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
	
	// Assign SS as OUTPUT
	REG_PORT_DIR0 = PORT_PA08;
	
	// Set SS OFF
	REG_PORT_OUTCLR0 = PORT_PA08;
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
	// Initialize the UART at 9600 baud
	UART3_Init(9600);
	delay_ms(500);
	
	// Initialize SPI
	SPI_Initialize_Slow();
	delay_ms(500);
	
	
	//////////////////////////////////////////////////////////////////////////
	// Writing to File
	//////////////////////////////////////////////////////////////////////////
	
	// Start to Init the SD Card
	UART3_Write_Text("start init\n");
	
	// Initialize the SD Card
    SDCard_Init();
	 
	// Initialize Done
	UART3_Write_Text("init done\n");
	
	// Start to mount the SD card
	UART3_Write_Text("start mount\n");
	
	// Mount the file
	FR= f_mount(&fs,data_file,0);
	
	// Finish Mounting
	UART3_Write_Text("end mount\n");
	
	// Error with mount
	if(FR)
	{
		UART3_Write_Text("\nError mounting file system\r\n");
		while(1);
	}
	
	// Start Open
	UART3_Write_Text("start open\n");
	
	// Open the SD Card for Writing
	FR = f_open(&fil, data_file, FA_WRITE | FA_OPEN_ALWAYS);
	
	// Open Successful
	UART3_Write_Text("end open\n");
	
	
	// Error Opening File
	if(FR)
	{
		UART3_Write_Text("Error opening file\r\n");
		while(1);
	}
	
	// Open File to write some CSV Data
	FR = f_write(&fil, "Data1 ,Data2 ,Data3 ,Data4 \r\n", 29, &bw); 
	
	
	// There is an Error
	if(FR)
	{
		UART3_Write_Text("\nError writing to file\r\n");
		while(1);
	}
	
	// Close the file
	FR = f_close(&fil);
	
	// There is an error
	if(FR)
	{
		UART3_Write_Text("\nError closing file\r\n");
		while(1);
	}
		
    UART3_Write_Text("Successful Write File Done!\n");


    //////////////////////////////////////////////////////////////////////////
	// Reading Files
	//////////////////////////////////////////////////////////////////////////
	
     UART3_Write_Text("Start Read\n");
   
     // Open the SD Card for Writing
     FR = f_open(&fil, data_file, FA_READ );
   
     UART3_Write_Text("Reading Good\n");
	 
	 // Reading Error
	 if (FR)
	 {
		 UART3_Write_Text("Read Error\n");
	 }
	 
	 
	 // Print Read Contents
	 UART3_Write_Text("The file contains: \n");
	  
	 char line[100]; /* Line buffer */
	 
	 /* Read every line and display it */
	 while (f_gets(line, sizeof line, &fil)) {
		 UART3_Write_Text(line);
	 }
	 
	 
	 // Reading Good
	 UART3_Write_Text("Reading Done\n");
	 
	 // Close the file
	 UART3_Write_Text("Closing File\n");
	 
	 // Close the file
	 FR = f_close(&fil);
	 
	 // Close read Error
	 if(FR)
	 {
		 UART3_Write_Text("Close Read Error\n");
	 }
	 
	 // All good on the close
	 UART3_Write_Text("Closing Success\n");
	 
	 
	 while(1)
	 {
		 
	 }

} // Apprun()

