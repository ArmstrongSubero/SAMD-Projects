/*
 * File:   SD.c
 * Author: Armstrong Subero
 * Processor: SAMD21G18A @ 48MHz, 3.3v
 * Program: Source file for application
 * Compiler: ARM-GCC (v6.3.1, Atmel Studio 7.0)
 * Program Version 1.0
 * Program Description: This file contains source code for 
 *                      using the SD card File Functions
 *
 * Modified From: None
 * 
 * Change History:
 *
 * Author                Rev     Date          Description
 * Armstrong Subero      1.0     04/06/2020    Initial Release
 *
 * Updated on June 04th, 2020, 11:30 AM
 */ 

//////////////////////////////////////////////////////////////////////////
// Include and defines
//////////////////////////////////////////////////////////////////////////
#include "SD.h"
#include "SPI.h"
#include "app.h"
#include "delay.h"
#include "USART3.h"
#include "integer.h"

// setup for slave select
#define GPIO_MAP_SS						PORT_PA08
#define GPIO_GROUP_SS					0

#define SPI_CS_LOW()					PORT->Group[GPIO_GROUP_SS].OUTCLR.reg = GPIO_MAP_SS;
#define SPI_CS_HIGH()					PORT->Group[GPIO_GROUP_SS].OUTSET.reg = GPIO_MAP_SS;

// Global Variables
uint8_t tmp_0 = 0;
uint8_t tmp_1 = 0;
uint8_t tmp_8 = 0;
uint8_t tmp_9 = 0;
uint8_t tmp_16 = 0;
uint8_t tmp_55 = 0;
uint8_t tmp_41 = 0;
uint8_t tmp_58 = 0;
uint8_t tmpAMD = 0;
uint8_t tmp17 = 0;
uint8_t tmp17_2 = 0;
uint8_t tmp_24 = 0;

// custom loop variable
uint8_t lvar = 0;

// data buffer
uint8_t  dataBuff[512];

// variable for SD Card Type
uint8_t SD_Type=0; 


/*-----------------------------------------------------------------------*/
/* Set Slow SPI Speed                                                    */
/*-----------------------------------------------------------------------*/
void SDCard_InitSpeed(void)
{
	SPI_Initialize_Slow();
}

/*-----------------------------------------------------------------------*/
/* Set Fast SPI Speed                                                    */
/*-----------------------------------------------------------------------*/
void SDCard_RunSpeed(void)
{
	SPI_Initialize_Fast();
} // SDCard_RunSpeed()


/*-----------------------------------------------------------------------*/
/* Slave Select Function                                                 */
/*-----------------------------------------------------------------------*/
void SDCard_SS(uint8_t cs)
{
	
	if (cs == 1)
	{
		SPI_CS_HIGH();
	}
	
	else
	{
		SPI_CS_LOW();
	}
} // SDCard_SS()



/*-----------------------------------------------------------------------*/
/* Wait for SD Card to Read                                              */
/*-----------------------------------------------------------------------*/
uint8_t SDCard_WaitRead( void )
{
	uint32_t cnt = 0x00FFFFF;
	uint8_t  res;
	
	do
	{
		res = SPI_SD_Send_Byte( 0xFF );
		
		if ( res == 0xff ) //
		{
			return 0;
		}
		cnt--;

	} while ( cnt );

	return 1;
} // SDCard_WaitRead()


/*-----------------------------------------------------------------------*/
/* Wait for SD Card to Be Ready                                          */
/*-----------------------------------------------------------------------*/
uint8_t SD_WaitReady(void)
{
	uint8_t data;	
    uint16_t attempt = 0;
	
    do
    {
		data = SPI_SD_Send_Byte(0xFF);
		
        if(attempt==0xFFFE)
		{
			return 1;
		}
    }while(data!=0xFF);
	
    return 0;
} //SDCard_WaitReady()


/*-----------------------------------------------------------------------*/
/* Initialize the SD Card                                                */
/*-----------------------------------------------------------------------*/
uint8_t SDCard_Init(void){

    // local variables
	uint8_t tvar = 0;
	uint16_t cnt=0;

    // Initialize the SD Card with a low speed
	SDCard_InitSpeed();
	delay_ms(100);
	
	// send dummy clocks
	for (tvar=0; tvar<0x0F; tvar++)
	{
		SPI_SD_Send_Byte(0xFF);  // send dummy clocks
	} 
	
	// try to reset the SD card
	do
	{
		// try reset
		tmp_0 = SDCard_WriteCmd(CMD0,0x00,0x95);
		lvar++;
    }   while ((tmp_0 != 1) && (lvar < 200)); 
	
	// the card reset failed
	if(lvar == 0)
	{
		SDCard_SS(1);          
		SPI_SD_Send_Byte(0xFF);
		UART3_Write_Text("Faile to reset card");
		return 1;
	}
		
    // make sure we can operate in the voltage range
    tmp_8 = SDCard_WriteCmd(CMD8,0x1AA,0x87);
		 
    // all good
    if(tmp_8 == 1)
		 	{
			   cnt=0xFFFF;
		 	   do
		 	   {
			      // our next command will be application specific
		 		  tmp_55 = SDCard_WriteCmd( CMD55, 0, 0xff );
				   
				  // wake up the card
		 		  tmp_41 = SDCard_WriteCmd( CMD41,0x40000000, 0xff);//CMD41
				   
		 		 cnt--;
		 	   } while ((tmp_41) && (cnt));

		 	        // activates Card's initialization process
		 	        tmp_1 = SDCard_WriteCmd(CMD1,0, 0xff);
		
				   // tell card we are taking OCR data
				   tmp_58 = SDCard_WriteCmd(CMD58, 0, 0);
				   
				   // somethings up
				   if ( tmp_58 != 0x00 )
				   {
					   SDCard_SS(1);           
					   UART3_Write_Text( "Problem taking OCR data\n");
					   return 1;
				   }

                   // get data from operations conditions (OCR) register 
				   for ( tvar = 0; tvar < 4; tvar++ )
				   {
					 dataBuff[tvar] = SPI_SD_Read_Byte();
				   }
				   
				   /// select card
				   SDCard_SS(1);
				   
                   // read card type
		 	       if ( dataBuff[0] & 0x40 )
		 	       {
		 		      SD_Type = SD_TYPE_V2HC;
		 		      UART3_Write_Text( "Card: V2.0 SDHC\n");
		 	       }
					
		 	       else 
			       {
		 		      SD_Type = SD_TYPE_V2;
		 		      UART3_Write_Text( "Card Type: V2.0\n");
		 	       }

                   // set the block length to 512 bytes (standard for SDHC and SDXC)
		 	       while(SDCard_WriteCmd(CMD16,512,0xff) != 0)
			       {
			       }
		 	  
			      // ask card for card specific data
			      tmp_9 = SDCard_WriteCmd(CMD9,0,0xff);
		 	}

            // We have finished our initialization
			UART3_Write_Text("Initialization Complete \n");

            // set our card to run speed now
			SDCard_RunSpeed();
			
			// slave select high
			SDCard_SS(1);
			
			return 0;
}// SDCard_Init()


// Disable select with inline expansion
__inline static void SDCard_DisableSelect( void )
{
	SDCard_SS(1);
	SPI_SD_Send_Byte(0xFF); 
}

// Enable select with inline expansion
__inline static uint8_t SDCard_EnableSelect( void )
{
	
	SDCard_SS(0);
	if ( SDCard_WaitRead() == 0 ) // ??SD/MMC??
	{
		return 0;
	}
	SDCard_DisableSelect();

	return 1;
}


/*-----------------------------------------------------------------------*/
/* Write a command to the card                                           */
/*-----------------------------------------------------------------------*/
uint8_t SDCard_WriteCmd(uint8_t cmd, uint32_t arg, uint8_t crc )
{
	uint16_t cnt = 512;
	uint8_t  res;

    // toggle line and transmit data
	SDCard_SS(1); 
    SPI_SD_Send_Byte( 0xFF); 
    SDCard_SS(0); 

     if (SDCard_EnableSelect())              // Select the card and wait for ready except to stop multiple block read
     {
	  return 0xFF;
     } 
	
     SPI_SD_Send_Byte( cmd | 0x40 );          // start command and index
     SPI_SD_Send_Byte( (uint8_t)(arg>>24) );  // argument [31..24]
     SPI_SD_Send_Byte( (uint8_t)(arg>>16) );  // argument [23..16]
     SPI_SD_Send_Byte( (uint8_t)(arg>>8) );   // argument [15..8]
     SPI_SD_Send_Byte( (uint8_t)(arg) );      // argument [7..0]
     SPI_SD_Send_Byte( crc );                 // Send valid CRC and stop
	 
	 do                                       // Wait for a valid response
	 {
		 res = SPI_SD_Send_Byte(0xFF);
		 cnt--;
	 } while ((cnt)&&(res==0xFF));

 	 return res;                              // Return with a response value
} // SDCard_WriteCmd()


/*-----------------------------------------------------------------------*/
/* Get the SD Card ID                                                    */
/*-----------------------------------------------------------------------*/
uint8_t SDCard_CardID(uint8_t cmd, uint8_t *buf)
{
	uint8_t i;

	if (SDCard_WriteCmd(cmd,0x00,0xFF) != 0x00)
	{
	    return 1;                                    
	}

	for (i=0; i<16; i++)
	{
	    *buf++ = SPI_SD_Send_Byte(0xFF);
	}

	return 0;                                        
}

/*-----------------------------------------------------------------------*/
/* Read a single block of Data                                           */
/*-----------------------------------------------------------------------*/
uint8_t SDCard_ReadSingleBlock(uint32_t addr, uint8_t *buf)
{
		uint16_t i;
	   
		if(SD_Type!=SD_TYPE_V2HC)
		{
			UART3_Write_Text("Not SD_TYPE_V2HC\n");
			  addr= addr<<9;
		}
		
		//////////////////////////
		// read a block address
		//////////////////////////
		tmp17 = SDCard_WriteCmd(CMD17,addr,0x01);
		
		while(tmp17 !=0)
		{
			UART3_Write_Text("Read block address\n");
			
			tmp17 = SDCard_WriteCmd(CMD17,addr,0x01);
		}
		delay_ms(1);

    
		while (SPI_SD_Read_Byte() != 0xFE)
		{
			
		}

		if(tmp17 == 0)
		{
	       UART3_Write_Text("Reading\n");
		   for (i=0; i<512; i++)
		   {
			  buf[i] = SPI_SD_Send_Byte(0xFF); 
		   }
		}
		
		// Done reading
		UART3_Write_Text("Read complete\n");
		SPI_SD_Send_Byte(0xFF);
		SPI_SD_Send_Byte(0xFF);
		SDCard_SS(1);
		return 0;
}


/*-----------------------------------------------------------------------*/
/* Read multiple blocks of Data                                          */
/*-----------------------------------------------------------------------*/
uint8_t SDCard_ReadMultipleBlock(uint32_t addr,uint8_t *buf,uint8_t count)
{
	uint16_t i;
	
	//////////////////////////////////
	// Read Multiple Block Addresses
	/////////////////////////////////
	if(SD_Type!=SD_TYPE_V2HC)
	{
		addr = addr<<9;
	}
 
    // keep transferring data until interrupted
	// by stop transmission command
	if (SDCard_WriteCmd(CMD18,addr,0xFF) != 0x00)
	{
		return 1;
	}

	SDCard_SS(0);
	do
	{
		while(SPI_SD_Send_Byte(0xFF) != 0xFE){;}
		for (i=0; i<512; i++)
		{
			*buf++ = SPI_SD_Send_Byte(0xFF);
		}
		SPI_SD_Send_Byte(0xFF);
		SPI_SD_Send_Byte(0xFF);

	}while (--count);
	SDCard_SS(1);
	
	// Force stop transmission after multiple block read 
	SDCard_WriteCmd(CMD12,0x00,0xFF);
	SPI_SD_Send_Byte(0xFF);
	return 0;
}


/*-----------------------------------------------------------------------*/
/* Write Single Block of Data                                            */
/*-----------------------------------------------------------------------*/
uint8_t SDCard_WriteSingleBlock(uint32_t addr,const uint8_t *buf)
{
	    uint8_t  temp;
	    uint16_t retry = 0;
		uint16_t i;

        //////////////////////////////////
        // Write Single Block Address
        /////////////////////////////////
        if(SD_Type!=SD_TYPE_V2HC)
        {
             addr=addr<<9 ;
        }

        tmp_24 = SDCard_WriteCmd(CMD24,addr,0x01);
		
		
        while(tmp_24 != 0)
		{
        	tmp_24 = SDCard_WriteCmd(CMD24,addr,0x01);
        }
		
        if (tmp_24 != 0x00)
        {
        	UART3_Write_Text("Reading\n");
            return 1;
        }

        SDCard_SS(0);
		
		//Wait until SD Card is ready
		SPI_SD_Send_Byte(0xFF);
		SPI_SD_Send_Byte(0xFF);
		SPI_SD_Send_Byte(0xFF);
		SPI_SD_Send_Byte(0xFE);

		for (i=0; i<512; i++)
		{
			SPI_SD_Send_Byte(buf[i]);
		}
		
	    // Send CRC Info (dummy)
		SPI_SD_Send_Byte(0xFF);
		SPI_SD_Send_Byte(0xFF);
		temp = SPI_SD_Send_Byte(0xFF);
		temp &= 0x1F;
		
		if (temp != 0x05)
		{
			UART3_Write_Text("CRC Write Fail");
			SDCard_SS(1);
			return 1;
		}

		while (SPI_SD_Send_Byte(0xFF) == 0x00)
		{
			 retry++;
			 if(retry>0xfffe)
			{

			  SDCard_SS(1);
			   return 1 ;
			 }
		}
		
		SDCard_SS(1);
		SPI_SD_Send_Byte(0xFF);
		UART3_Write_Text("Write Complete\n");
		return 0;
}

/*-----------------------------------------------------------------------*/
/* Write Multiple Blocks of Data                                         */
/*-----------------------------------------------------------------------*/
uint8_t SDCard_WriteMultipleBlock(uint32_t addr, uint8_t *buf, uint8_t count)
{
     uint16_t i;
	 uint8_t tmp;
	 
     if(SD_Type!=SD_TYPE_V2HC) 
     {
          addr=addr<<9;
     }
	 
	 if(SD_Type!=SD_TYPE_MMC)
     {
		// pre-erase write sector
        tmp=SDCard_WriteCmd(CMD23,count,0x00);
     }
	 
     ////////////////////////////////////
     // Write Multiple Block Addresses
     ///////////////////////////////////
	 
	 // try to write blocks of data until stop transmission received
	 if (SDCard_WriteCmd(CMD25,addr,0xFF) != 0x00) 
	 {
		 UART3_Write_Text("Write Multiple Block Address Failed\n");
		 return 1;
	 }
	 
	 SDCard_SS(0); 

	 // Wait until SD Card is ready
	 SPI_SD_Send_Byte(0xFF);
	 SPI_SD_Send_Byte(0xFF);
	 
	 // Write Data
	 do
	 {
		 // Start block
		 SPI_SD_Send_Byte (0xFC); 
		 
		 // Write Data
		 for (i=0; i<512; i++) 
		 {
				 SPI_SD_Send_Byte(*buf++);
		 }
		 
		 // Send CRC info (dummy)
		 SPI_SD_Send_Byte(0xFF); 
		 SPI_SD_Send_Byte(0xFF);
		 
		 tmp = SPI_SD_Send_Byte(0xFF); 
		 tmp &= 0x1F;
		 
		 if(tmp != 0x05)
		 {   
			UART3_Write_Text("CRC Multiple Write Failed\n");
			SDCard_SS(1);
			return 1;
		 }
		 while(SPI_SD_Send_Byte (0xFF) == 0x00){;} // BUSY wait
	 }while (--count);
	 
	 // Send 'Stop Tran' Token
	 SPI_SD_Send_Byte (0xFD);
	 while (SPI_SD_Send_Byte (0xFF) == 0x00)
	 {
		 
	 }
	 
	 // done writing
	 SDCard_SS(1);
	 SPI_SD_Send_Byte(0xFF);
	 UART3_Write_Text("Write Multiple Complete\n");
	 return 0;
}


