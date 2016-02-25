/********************************************
 * GPIO__Handler.c
 *
 * Edited by: Josh
 * Jan 2016
 *
 *********************************************/

#include "GPIOE_Handler.h"

void GPIOE_Handler(void){
	if(GPIOE_AHB->MIS == PE0){		// If the PE0 button switch is pushed...
		GPIOE_AHB->ICR = PE0;		// Acks the interrupt status.
		ACT = 1U;					// Assigns ACT as 1.
	} else {
		if(GPIOE_AHB->MIS == PE1){	// If the PE1 button switch is pushed...
			GPIOE_AHB->ICR = PE1;	// Acks the interrupt status.
			ACT = 2U;				// Assigns ACT as 2.
		} else {
			GPIOE_AHB->ICR = (PE1 | PE0);
			ACT = 0U;
		}
	}
}
