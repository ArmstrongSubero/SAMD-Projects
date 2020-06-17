/*
 * File:   app.c
 * Author: Armstrong Subero
 * Processor: SAMD21G18A @ 48MHz, 3.3v
 * Program: Source file for application
 * Compiler: ARM-GCC (v6.3.1, Atmel Studio 7.0)
 * Program Version 1.0
 * Program Description: This file contains your application source
 *
 * Modified From: None
 * 
 * Change History:
 *
 * Author             Rev     Date          Description
 * Armstrong Subero   1.0     26/05/2020    Initial Release.
 * 
 * Updated on June 17, 2020, 06:44 PM
 */

//////////////////////////////////////////////////////////////////////////
// Include and defines
//////////////////////////////////////////////////////////////////////////
#include "app.h"
#include "clock.h"

#define F_CPU 48000000UL
#include "delay.h"

/*******************************************************************************
 * Function:        void AppInit(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This routine takes care of all of the 1-time hardware/software
 *                  initialization that is required.
 *
 * Note:            This was taken from the _00_LED_ON provided by
 *                  Microchip Technology Inc. 
 *
 ******************************************************************************/
void AppInit(void)
{
	/*	Clock initialization (CPU, AHB, APBx, Asynchronous Peripheral Clocks)
		The System RC Oscillator (RCSYS) provides the source for the main clock
		at chip startup. It is set to 1MHz.
	*/
	ClocksInit();
	
	// Assign LED0 as OUTPUT
	REG_PORT_DIR0 = LED0_PIN_MASK;
	
	// Set LED0 OFF
	REG_PORT_OUTCLR0 = LED0_PIN_MASK;
	

} // AppInit()


////////////////////////
// Initialize the PWM 
////////////////////////
void PWM_Init()
{
   /* -------------------------------------------------
	* 1) Enable bus clock to APBC mask
	*/
	REG_PM_APBCMASK |=  PM_APBCMASK_TCC0;
	
    /* -------------------------------------------------
	* 2) select TCC0 clock
	*/
	GCLK->CLKCTRL.reg = 
	GCLK_CLKCTRL_ID(GCLK_CLKCTRL_ID_TCC0_TCC1) |  // select TCC0 clock
	GCLK_CLKCTRL_CLKEN |                         // enable the clock
	GCLK_CLKCTRL_GEN(0);                         //  select GCLK GEN0
	
	while (GCLK->STATUS.bit.SYNCBUSY) {}
	
	/* -------------------------------------------------
	* 3) select PA05 as output
	*/
    PORT->Group[0].DIRSET.reg = PORT_PA05;
    PORT->Group[0].OUTCLR.reg = PORT_PA05;
	PORT->Group[0].PINCFG[5].reg |= PORT_PINCFG_PMUXEN;
	PORT->Group[0].PMUX[4 >> 1].reg =  PORT_PMUX_PMUXO_E;
	
	/* -------------------------------------------------
	* 4) Reset the PWM Module
	*/
	TCC0->CTRLA.reg = TCC_CTRLA_SWRST;
	while (TCC0->SYNCBUSY.reg & TCC_SYNCBUSY_SWRST) {}
	 
	/* -------------------------------------------------
	* 5) Configure the prescaler
	*/
	TCC0->CTRLA.reg = (TCC_CTRLA_PRESCSYNC_GCLK_Val | TCC_CTRLA_PRESCALER(TCC_CTRLA_PRESCALER_DIV8_Val));
	 
	/* -------------------------------------------------
	* 6) Set the waveform to normal PWM
	*/
	TCC0->WAVE.reg = (TCC_WAVE_WAVEGEN_NPWM);
	while (TCC0->SYNCBUSY.reg & TCC_SYNCBUSY_WAVE) {}
	 
	/* -------------------------------------------------
	* 7) Set the period
	*/
	TCC0->PER.reg = (255 - 1);
	while (TCC0->SYNCBUSY.reg & TCC_SYNCBUSY_PER) {}
	 
	/* -------------------------------------------------
	* 8) Initial duty cycle is zero
	*/
	TCC0->CC[1].reg = 0;
	 
	/* -------------------------------------------------
	* 9) Enable the TCC module
	*/ 
	TCC0->CTRLA.reg |= (TCC_CTRLA_ENABLE);
}


////////////////////////
// Set the Duty Cycle
////////////////////////
void PWM_SetDuty(uint8_t duty)
{
	 // Set the duty cycle for TCC0
	 TCC0->CC[1].reg = duty;
}



/*******************************************************************************
 * Function:        void AppInit(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function contains your main application
 *                  
 *
 * Note:
 *
 ******************************************************************************/
void AppRun(void)
{
	// Initialize the PWM module
	PWM_Init();
	
	while(1)
	{
		for (int i = 0; i <= 255; i++)
		{
			// set the duty cycle
			PWM_SetDuty(i);
			delay_ms(10);
		}
	}

} // Apprun()

