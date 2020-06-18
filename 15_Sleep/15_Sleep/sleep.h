/*
 * File:   sleep.h
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
 * Updated on June 17, 2020, 08:32 PM
 */


#ifndef SLEEP_H_
#define SLEEP_H_

//////////////////////////////////////////////////////////////////////////
// Include and defines
//////////////////////////////////////////////////////////////////////////
#include "app.h"


//////////////////////////////////////////////////////////////////////////
// Function Prototypes
//////////////////////////////////////////////////////////////////////////

/**
 * \def StandbySleep
 * \brief Puts the microcontroller in standby sleep mode
 * \param None
 */
void StandbySleep(void);


#endif /* SLEEP_H_ */