/********************************************
 * ADC0_InSeq3.c
 *
 * Edited by: Josh
 * Jan 2016
 *
 *********************************************/

#include "ADC0_InSeq3.h"

uint32_t ADC0_InSeq3(void){

	uint32_t result;
	ADC0->PSSI = (1U<<3);
	while((ADC0->RIS&(1U<<3))==0){;}	// Waits for Sequencer 3 is ready.
	result = ADC0->SSFIFO3&0xFFF;		// Stores 12 bits digital reading in result.
	ADC0->ISC = (1U<<3);				// Ack the interrupt status on seq 3.
	return result;
}
