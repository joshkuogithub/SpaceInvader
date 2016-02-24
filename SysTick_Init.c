/********************************************
 * SysTick_Init.c
 *
 * Edited by: Josh
 * Jan 2016
 *
 *********************************************/

#include "SysTick_Init.h"

void SysTick_Init(uint32_t period){		// period = (Clock Source / Desired Frequency - 1)
										// e.g., period = (50MHz / 30Hz - 1)
	SysTick->CTRL &= ~(INTEN|EN);		// Disable interrupt and timer for configuration
	SysTick->LOAD = period-1;			// This is the value reload to VAL
	SysTick->VAL = 0;					// Initialize VAL as 0
	//SysTick->CTRL = (PIOSC|INTEN|EN);	// Use PIOSC/4
	SysTick->CTRL |= SYS_CLK;			// Use System Clock as clock source
										// If default SystemInit is used, 50MHz.

	// Priority of the interrupt is set in a seperate function.
	// The interrupt is enabled in a seperate function.

}
