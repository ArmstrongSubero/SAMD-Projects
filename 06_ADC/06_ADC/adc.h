/*
 * File:   adc.h
 * Author: Armstrong Subero
 * Processor: SAMD21G18A @ 48MHz, 3.3v
 * Program: Header file for application
 * Compiler: ARM-GCC (v6.3.1, Atmel Studio 7.0)
 * Program Version 1.0
 * Program Description: This header file provides functions for ADC
                        conversion
 * Modified From: None
 * 
 * Change History:
 *
 * Author             Rev     Date          Description
 * Armstrong Subero   1.0     29/05/2020    Initial Release.
 * 
 * Updated on May 29, 2020, 12:37 PM
 */

#ifndef ADC_H_
#define ADC_H_



//////////////////////////////////////////////////////////////////////////
// Include and defines
//////////////////////////////////////////////////////////////////////////
#include "app.h"


//////////////////////////////////////////////////////////////////////////
// Function Prototypes
//////////////////////////////////////////////////////////////////////////


/**
 * \def adc_init
 * \brief Initializes the ADC module
 * \param none
 */
void adc_init(void);


/**
 * \def adc_readchannel
 * \brief Read the specified ADC channel
 * \param channel (ADC channel number)
 */
int32_t adc_readchannel(uint8_t channel);


#endif /* ADC_H_ */