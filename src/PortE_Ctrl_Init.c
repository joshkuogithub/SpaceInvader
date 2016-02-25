/********************************************
 * PortE_Ctrl_Init.c
 *
 * Edited by: Josh
 * Jan 2016
 *
 *********************************************/

#include "PortE_Ctrl_Init.h"

void PortE_Ctrl_Init(void){

	__IO uint32_t dummy;
	SYSCTL->RCGC2 |= (1U<<4);		// Enable clocking on Port E
									// Another optional register is RCGCGPIO.
									// But Nokia5110_Init() writes to RCG2.
									// Writing to RCG2 overwrites RCGCGPIO.
	dummy = SYSCTL->RCGCGPIO; 		// dummy delay for stable clock
	SYSCTL->GPIOHBCTL |= (1U<<4); 	// Enables AHB for Port E

	GPIOE_AHB->DIR &= ~(PE2|PE1|PE0);// Make PE2, PE1, PE0 input

	GPIOE_AHB->DEN &= ~PE2; 		// Disables the digital I/O on PE2.
	GPIOE_AHB->AFSEL |= PE2; 		// Enables Alternative function on PE2.
	GPIOE_AHB->AMSEL |= PE2; 		// Enables Anolog Mode on PE2.

	GPIOE_AHB->AFSEL &= ~(PE1|PE0); // Disables the Alternative Function on PE1,PE0(default).
	GPIOE_AHB->AMSEL &= ~(PE1|PE0); // Disables Anolog Mode on PE1,PE0 (default)s
	GPIOE_AHB->PUR |= (PE1|PE0);	// Enables pull-up resistors
	//GPIOE_AHB->PDR |= (PE1|PE0);	// Enables pull-down resistors
									// i.e. SW on PE1, PE0 grounded, interrupt triggerd by falling edges
	GPIOE_AHB->DEN |= (PE1|PE0);	// Enables the digital I/O on PE1, PE0s

	// Make PE1, PE0 trigger of Interrupt.

	GPIOE_AHB->IS &= ~(PE1|PE0);	// Make sure the PE1,PE0 bit are set 0 as edge sensitive.
	GPIOE_AHB->IBE &= ~(PE1|PE0);	// Make sure the PE1,PE0 bit are set 0 as NOT both edges.
	//GPIOE_AHB->IEV |= (PE1|PE0);	// Make sure the PE1,PE0 bit are set 1 as rising edge.
	GPIOE_AHB->IEV &= ~(PE1|PE0);	// Make sure the PE1,PE0 bit are set 0 as falling edge.
	GPIOE_AHB->ICR |= (PE1|PE0);	// Make sure that flags on PE1,PE0 bit are cleared.
	GPIOE_AHB->IM |= (PE1|PE0);		// Make sure that PE1,PE0 bit are armed

	// Priority of the interrupt is set in a seperate function.
	// The interrupt is enabled in a seperate function.

}
