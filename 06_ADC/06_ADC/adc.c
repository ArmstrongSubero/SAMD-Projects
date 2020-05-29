/*
 * File:   adc.c
 * Author: Armstrong Subero
 * Processor: SAMD21G18A @ 48MHz, 3.3v
 * Program: Source file for application
 * Compiler: ARM-GCC (v6.3.1, Atmel Studio 7.0)
 * Program Version 1.0
 * Program Description: This file contains source code for 
 *                      using the ADC module
 *
 * Modified From: None
 * 
 * Change History:
 *
 * Author                Rev     Date          Description
 * Armstrong Subero      1.0     29/05/2020    Initial Release
 *
 * Updated on May 29, 2020, 12:39 PM
 */


//////////////////////////////////////////////////////////////////////////
// Include and defines
//////////////////////////////////////////////////////////////////////////
#include "adc.h"



/*******************************************************************************
 * Function:        void adc_init(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function initializes the ADC module
 *                  
 *
 * Note:            The default initialization is 10-bits resolution
 *
 ******************************************************************************/
void adc_init(void)
{
	/* -------------------------------------------------
	* 1) Enable bus clock to APBC mask
	*/
	REG_PM_APBCMASK |=  PM_APBCMASK_ADC;
	
	/* -------------------------------------------------
	* 2) select Analog clock
	*/
	GCLK->CLKCTRL.reg = 
	GCLK_CLKCTRL_ID(ADC_GCLK_ID) |  // select ADC clock
	GCLK_CLKCTRL_CLKEN |            // enable the clock
	GCLK_CLKCTRL_GEN(0);            //  select GCLK GEN0
	
	/* -------------------------------------------------
	* 3) reset ADC to its initial settings and disable
	*/
	ADC->CTRLA.reg = ADC_CTRLA_SWRST;
	
	/* -------------------------------------------------
	* 4) Load in the fixed device ADC calibration constants 
	*/
	ADC->CALIB.reg =
	ADC_CALIB_BIAS_CAL((*(uint32_t *) ADC_FUSES_BIASCAL_ADDR >> ADC_FUSES_BIASCAL_Pos)) |
	ADC_CALIB_LINEARITY_CAL((*(uint64_t *) ADC_FUSES_LINEARITY_0_ADDR >> ADC_FUSES_LINEARITY_0_Pos));
	
	/* -------------------------------------------------
	* 5) Setup voltage reference 
	*/
	ADC->INPUTCTRL.bit.GAIN = ADC_INPUTCTRL_GAIN_1X_Val;    // Gain Factor Selection
	ADC->REFCTRL.bit.REFSEL = ADC_REFCTRL_REFSEL_INTVCC1; // Vcc voltage reference
	ADC->REFCTRL.bit.REFCOMP = 1;                           //  enable reference compensation
	
	/* -------------------------------------------------
	* 6) Setup average and samples
	*/
	ADC->AVGCTRL.reg = ADC_AVGCTRL_SAMPLENUM_1 |   // 1 sample
	ADC_AVGCTRL_ADJRES(0x00ul); // Adjusting result by 0
	
	/* -------------------------------------------------
	* 7) Setup sample length
	*/
	ADC->SAMPCTRL.reg = ADC_SAMPCTRL_SAMPLEN(5);
	
	/* -------------------------------------------------
	* 8) Configure Parameters 
	*/
	// prescaler div32
	ADC->CTRLB.bit.PRESCALER = ADC_CTRLB_PRESCALER_DIV32_Val;
	
	// 10-bit resolution
	ADC->CTRLB.bit.RESSEL = ADC_CTRLB_RESSEL_10BIT_Val;
	
	// no correction enable
	ADC->CTRLB.bit.CORREN = 0;     
	
	// set free running 
	ADC->CTRLB.bit.FREERUN = 1;
	
	// set right Adjustment
	ADC->CTRLB.bit.LEFTADJ = 0;
	
	// turn off differential mode
	ADC->CTRLB.bit.DIFFMODE = 0;
	
    /* -------------------------------------------------
	* 9) Configure delay gain, scan at 5 and ground
	*/
	ADC->INPUTCTRL.reg = ADC_INPUTCTRL_MUXPOS_PIN0 | 
	                     ADC_INPUTCTRL_MUXNEG_GND | 
	                     ADC_INPUTCTRL_GAIN_DIV2;    
	
    /* -------------------------------------------------
	* 10) enable the ADC
	*/
	ADC->CTRLA.reg = ADC_CTRLA_ENABLE;
}


/*******************************************************************************
 * Function:        int32_t adc_readchannel(uint8_t channel)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function reads a channel number for ADC conversion
 *                  
 *
 * Note:            
 *
 ******************************************************************************/
int32_t adc_readchannel(uint8_t channel)
{
	// set positive MUX input selection
	ADC->INPUTCTRL.bit.MUXPOS = channel;

	// start conversion then flush
	// ADC will pick up where it left off
	ADC->SWTRIG.reg = ADC_SWTRIG_START | ADC_SWTRIG_FLUSH;

	// wait for analog conversion to complete
	while (ADC->INTFLAG.bit.RESRDY == 0)
	{

	}

	// return the result of the ADC
	return ADC->RESULT.reg;
}