/*
 * File:   SD.h
 * Author: Armstrong Subero
 * Processor: SAMD21G18A @ 48MHz, 3.3v
 * Program: Header file for application
 * Compiler: ARM-GCC (v6.3.1, Atmel Studio 7.0)
 * Program Version 1.0
 * Program Description: This header file provides functions for SD
                        card file handling functions
 * Modified From: None
 * 
 * Change History:
 *
 * Author             Rev     Date          Description
 * Armstrong Subero   1.0     06/04/2020    Added SD Card Support
 * 
 * Updated on June 04, 2020, 1:13 AM
 */


#ifndef SD_H_
#define SD_H_


//////////////////////////////////////////////////////////////////////////
// Include and defines
//////////////////////////////////////////////////////////////////////////
#include <stdint.h>

// SD Card Type Definition
#define SD_TYPE_MMC     0
#define SD_TYPE_V1      1
#define SD_TYPE_V2      2
#define SD_TYPE_V2HC    4

// SD Card instruction commands
#define CMD0  0x40 // Use SPI interface
#define CMD1  0x41 // Use SPI interface
#define CMD8  0x48 // Get SD card version
#define CMD9  0x49 // Get Card Specific Data
#define CMD12 0x4C // Stop data transmission in Multiple Read Operation
#define CMD13 0x4D // Send status register
#define CMD16 0x50 // Set SD card block size to 512Byte.
#define CMD17 0x51 // For reading the SD card send to this
#define CMD18 0x52 // Transfer data blocks from Card to HOST
#define CMD23 0x57 // Write Sector
#define CMD24 0x58 // For writing to the SD card send to this
#define CMD25 0x59 // For writing to the SD card send to this
#define CMD41 0x69 // Activate SD card
#define CMD55 0x77 // Define next command in specific command
#define CMD58 0x7A // Reads OCR data
#define CMD59 0x7B // Turn CRC ON or OFF

/**
 * \def SDCard_Init
 * \brief Initializes the SD Card
 * \param none 
 */
uint8_t SDCard_Init(void);


/**
 * \def SDCard_WriteCmd
 * \brief writes a command to the SD Card
 * \param  uint8_t cmd, uint32_t arg, uint8_t crc
 */
uint8_t SDCard_WriteCmd( uint8_t cmd, uint32_t arg, uint8_t crc );

/**
 * \def SDCard_SS
 * \brief  slave select SD card
 * \param  uint8_t cs
 */
void    SDCard_SS(uint8_t cs);


/**
 * \def SDCard_WriteSingleBlock
 * \brief  Writes a single block of data to the SD Card
 * \param  uint32_t addr,const uint8_t *buf
 */
uint8_t SDCard_WriteSingleBlock(uint32_t addr,const uint8_t *buf);

/**
 * \def SDCard_WriteSingleBlock
 * \brief  Reads a single block of data from the SD Card
 * \param  uint32_t addr, uint8_t *buf
 */
uint8_t SDCard_ReadSingleBlock(uint32_t addr,uint8_t *buf);

/**
 * \def  SDCard_WriteMultipleBlock
 * \brief  Writes multiple blocks of data to the SD Card
 * \param  uint32_t addr,uint8_t *buf,uint8_t count
 */
uint8_t SDCard_WriteMultipleBlock(uint32_t addr,uint8_t *buf,uint8_t count);


/**
 * \def  SDCard_WriteMultipleBlock
 * \brief  Reads multiple blocks of data from the SD Card
 * \param  uint32_t addr,uint8_t *buf,uint8_t count
 */
uint8_t SDCard_ReadMultipleBlock(uint32_t addr,uint8_t *buf,uint8_t count);

/**
 * \def  SDCard_CardID
 * \brief  SD Card Card Identification routines
 * \param  uint8_t cmd, uint8_t *buf
 */
uint8_t SDCard_CardID(uint8_t cmd, uint8_t *buf);

#endif /* SD_H_ */
