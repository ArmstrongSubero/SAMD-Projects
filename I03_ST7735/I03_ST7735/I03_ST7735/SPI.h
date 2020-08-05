/*
 * File:   SPI.h
 * Author: Armstrong Subero
 * Processor: SAMD21G18A @ 48MHz, 3.3v
 * Program: Header file for application
 * Compiler: ARM-GCC (v6.3.1, Atmel Studio 7.0)
 * Program Version 1.0
 * Program Description: This header file provides functions for using 
 *                      SPI module
 * Modified From: None
 * 
 * Change History:
 *
 * Author             Rev     Date          Description
 * Armstrong Subero   1.0     26/05/2020    Initial Release.
 * 
 * Updated on August 05, 2020, 06:35 PM
 */

#ifndef INCFILE1_H_
#define INCFILE1_H_

//////////////////////////////////////////////////////////////////////////
// Function Prototypes
//////////////////////////////////////////////////////////////////////////
#include "sam.h"
#include "definitions.h"

// Initialize the SPI module
void spiInit();

// Send data via SPI
void spiSend(unsigned char data);

#endif /* INCFILE1_H_ */