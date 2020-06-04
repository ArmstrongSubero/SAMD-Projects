/*
 * File:   app.h
 * Author: Armstrong Subero
 * Processor: SAMD21G18A @ 48MHz, 3.3v
 * Program: Header file for application
 * Compiler: ARM-GCC (v6.3.1, Atmel Studio 7.0)
 * Program Version 1.0
 * Program Description: This header file contains your application includes
 * Modified From: None
 * 
 * Change History:
 *
 * Author             Rev     Date          Description
 * Armstrong Subero   1.0     26/05/2020    Initial Release.
 * 
 * Updated on May 26, 2020, 11:09 AM
 */


#ifndef APP_H_
#define APP_H_


//////////////////////////////////////////////////////////////////////////
// Include and defines
//////////////////////////////////////////////////////////////////////////
#include "sam.h"
#include "definitions.h"

#define F_CPU 48000000UL
//////////////////////////////////////////////////////////////////////////
// Function Prototypes
//////////////////////////////////////////////////////////////////////////

// initialize your application
void AppInit(void);

// run the main program		
void AppRun(void);

#endif /* APP_H_ */