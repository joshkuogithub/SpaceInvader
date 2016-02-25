/********************************************
 * EnableInterrupts.c
 *
 * Edited by: Josh
 * Jan 2016
 *
 *********************************************/

#include "EnableInterrupts.h"

void Enable_Control(void){

	NVIC->IP[4] = (2U << 5);		// Sets GPIOE_Handler() Priority as 2 (0 ~ 7)
	NVIC->ISER[0] |= (1U << 4);		// Enables the interrupt number 4, i.e., PE interrupt
}

void Enable_SysTick(void){

	SCB->SHP[8] = (2U << 5);		// Sets SysTick_Handler() Priority as 2 (0 ~ 7)
	SysTick->CTRL |= (INTEN|EN);	//Enables System Timer interrupt generation and timer.

}

void Disable_SysTick(void){

	SysTick->CTRL &= ~(INTEN|EN);	//Disables System Timer interrupt generation and timer.

}

