/*
 * File:   USART3.h
 * Author: Armstrong Subero
 * Processor: SAMD21G18A @ 48MHz, 3.3v
 * Program: Header file for application
 * Compiler: ARM-GCC (v6.3.1, Atmel Studio 7.0)
 * Program Version 1.0
 * Program Description: This header file provides functions for USART
                        communication
 * Modified From: None
 * 
 * Change History:
 *
 * Author             Rev     Date          Description
 * Armstrong Subero   1.0     01/06/2020    Initial Release.
 * 
 * Updated on June 01, 2020, 05:58 PM
 */


#ifndef USART3_H_
#define USART3_H_


//////////////////////////////////////////////////////////////////////////
// Include and defines
//////////////////////////////////////////////////////////////////////////
#include <stdbool.h>
#define F_CPU 48000000UL
#include "delay.h"


//////////////////////////////////////////////////////////////////////////
// Function Prototypes
//////////////////////////////////////////////////////////////////////////

/**
 * \def UART3_Init
 * \brief Initializes the UART module
 * \param baud (UART baud rate eg.9600)
 */
void UART3_Init(uint32_t baud);


/*
 * \def UART3_Write
 * \brief Writes a character to UART3
 * \param data (character to send)
 */
void UART3_Write(char data);

/*
 * \def UART3_Write_Text
 * \brief Writes a string to UART3
 * \param data (text to send)
 */
void UART3_Write_Text(char *text);


/*
 * \def UART3_Has_Data
 * \brief Return true if we have data
 * \param none
 */
bool UART3_Has_Data();


/*
 * \def UART3_Has_Data
 * \brief Returns data read from UART3
 * \param none
 */
char UART3_Read();


#endif /* USART3_H_ */