/********************************************
 * ADC0_init.c
 *
 * Edited by: Josh
 * Jan 2016
 *
 *********************************************/

#include "ADC0_init.h"

void ADC0_init(void){

	// Initializes ADC0 for player ship movement control.

	__IO uint32_t dummy;

	SYSCTL->RCGC0 |= (1U<<16);	// Active ADC0;
	dummy = SYSCTL->RCGC0;		// dummy delay for stable clock
	SYSCTL->RCGC0 |= ((1U<<9)|(1U<<8));		// Sampling rate 1M
	ADC0->SAC = 0x2U;			// Set hardware average oversampling rate as 4 (2^2)
	ADC0->SSPRI = 0x0123U; 		// Sequencer 3 is the highest priority
	ADC0->ACTSS &= ~(1U<<3);	// Disable Sequencer 3
	ADC0->EMUX &= ~0xF000U;		// Sequencer 3 reading is set as software triggered
	ADC0->SSMUX3 &= ~(0xEU); ADC0->SSMUX3 |= 1U;	// Sequencer 3 uses AIN1 (PE2)
	ADC0->SSCTL3 = ((1U<<2)|(1U<<1));	// Deassert TS0, D0; Assert IE0, END0 (page 876)
	ADC0->ACTSS |= (1U<<3);				// Enable Sequencer 3

	}
