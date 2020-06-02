/*
 * File:   I2C1.h
 * Author: Armstrong Subero
 * Processor: SAMD21G18A @ 48MHz, 3.3v
 * Program: Header file for application
 * Compiler: ARM-GCC (v6.3.1, Atmel Studio 7.0)
 * Program Version 1.0
 * Program Description: This header file provides functions for I2C
                        communication
 * Modified From: None
 * 
 * Change History:
 *
 * Author             Rev     Date          Description
 * Armstrong Subero   1.0     02/06/2020    Initial Release.
 * 
 * Updated on June 02, 2020, 05:05 PM
 */


#ifndef I2C1_H_
#define I2C1_H_


/**
 * \def UART3_Init
 * \brief Initializes the UART module
 * \param none
 */
void I2C1_init(void);


/**
 * \def UART3_Init
 * \brief Initializes the UART module
 * \param  device_addr (slave device address), memory_addr (memory address of slave), data (data to send)
 */
void I2C1_write_byte(unsigned char device_addr, unsigned char mem_addr, unsigned char data);


/**
 * \def I2C1_read_byte
 * \brief Initializes the I2C module
 * \param device_addr (slave device address), memory_addr (memory address of slave), data (data to read)
 */
void I2C1_read_byte(unsigned char device_addr, unsigned char mem_addr, unsigned char* data);

#endif /* I2C1_H_ */