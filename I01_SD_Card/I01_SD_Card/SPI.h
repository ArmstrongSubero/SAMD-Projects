/*
 * File:   SPI.h
 * Author: Armstrong Subero
 * Processor: SAMD21G18A @ 48MHz, 3.3v
 * Program: Header file for application
 * Compiler: ARM-GCC (v6.3.1, Atmel Studio 7.0)
 * Program Version 1.0
 * Program Description: This header file provides functions for SPI
                        communication specifically related to SD Cards
 * Modified From: None
 * 
 * Change History:
 *
 * Author             Rev     Date          Description
 * Armstrong Subero   1.1     06/04/2020    Added SD Card Support
 * Armstrong Subero   1.0     02/06/2020    Initial Release.
 * 
 * Updated on June 04, 2020, 11:13 AM
 */


#ifndef SPI_H_
#define SPI_H_

//////////////////////////////////////////////////////////////////////////
// Include and defines
//////////////////////////////////////////////////////////////////////////
#include "app.h"


/**
 * \def SPI_Initialize_Slow
 * \brief Initializes the SPI module in Slow Mode 400 kHz Baud
 * \param none 
 */
void SPI_Initialize_Slow(void);


/**
 * \def SPI_Initialize_Fast
 * \brief Initializes the SPI module in Fast Mode 12 MHz Baud (Att.)
 * \param none 
 */
void SPI_Initialize_Fast(void);


/**
 * \def SPI_Exchange8bit
 * \brief Exchanges 8 bits of data on SPI bus
 * \param none 
 */
uint8_t SPI_Exchange8bit(uint8_t data);


/**
 * \def SPI_SD_Send_Byte
 * \brief Exchanges 8 bits of data on SPI bus
 * \param none 
 */
uint8_t SPI_SD_Send_Byte(uint8_t byte_val);



/**
 * \def SPI_SD_Read_Byte
 * \brief Exchanges 8 bits of data on SPI bus
 * \param none 
 */
uint8_t SPI_SD_Read_Byte(void);


#endif /* SPI_H_ */