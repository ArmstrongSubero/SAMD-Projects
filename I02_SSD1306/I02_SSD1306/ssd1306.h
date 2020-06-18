/*
 * File:   I2C1.h
 * Author: Armstrong Subero
 * Processor: SAMD21G18A @ 48MHz, 3.3v
 * Program: Header file for application
 * Compiler: ARM-GCC (v6.3.1, Atmel Studio 7.0)
 * Program Version 1.0
 * Program Description: This header file provides functions for SSD1306
                        communication
 * Modified From: None
 * 
 * Change History:
 *
 * Author             Rev     Date          Description
 * Armstrong Subero   1.0     02/06/2020    Initial Release.
 * 
 * Updated on June 17, 2020, 12:00 MN
 */


#ifndef SSD1306_H_
#define SSD1306_H_

#include "app.h"
#include "I2C1.h"

// Define OLED dimensions
#define OLED_WIDTH 128
#define OLED_HEIGHT 64

// Define command macros
#define OLED_SETCONTRAST 0x81
#define OLED_DISPLAYALLON_RESUME 0xA4
#define OLED_DISPLAYALLON 0xA5
#define OLED_NORMALDISPLAY 0xA6
#define OLED_INVERTDISPLAY 0xA7
#define OLED_DISPLAYOFF 0xAE
#define OLED_DISPLAYON 0xAF
#define OLED_SETDISPLAYOFFSET 0xD3
#define OLED_SETCOMPINS 0xDA
#define OLED_SETVCOMDETECT 0xDB
#define OLED_SETDISPLAYCLOCKDIV 0xD5
#define OLED_SETPRECHARGE 0xD9
#define OLED_SETMULTIPLEX 0xA8
#define OLED_SETLOWCOLUMN 0x00
#define OLED_SETHIGHCOLUMN 0x10
#define OLED_SETSTARTLINE 0x40
#define OLED_MEMORYMODE 0x20
#define OLED_COLUMNADDR 0x21
#define OLED_PAGEADDR   0x22
#define OLED_COMSCANINC 0xC0
#define OLED_COMSCANDEC 0xC8
#define OLED_SEGREMAP 0xA0
#define OLED_CHARGEPUMP 0x8D


// Function declarations
void OLED_Command( uint8_t temp);
void OLED_Data( uint8_t temp);
void OLED_Init();
void OLED_YX(unsigned char Row, unsigned char Column); // *warning!* max 4 rows
void OLED_PutChar( char ch );
void OLED_Clear();
void OLED_Write_String( char *s );
void OLED_Write_Integer(uint16_t i);
void OLED_Write_Float(float f);


#endif /* SSD1306_H_ */