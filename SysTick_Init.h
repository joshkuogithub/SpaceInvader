/********************************************
 * SysTick_Init.h
 *
 * Edited by: Josh
 * Jan 2016
 *
 *********************************************/

#ifndef __SYSTICK_INIT_H__
#define __SYSTICK_INIT_H__

#include "TM4C123GH6PM.h"

// System Timer Clock Source (datasheet page 138)
#define SYS_CLK (1U<<2)
#define PIOSC	(0U<<2)

// System Timer Interrupt Generation Enable
#define INTEN	(1U<<1)

// System Timer Enable
#define EN		(1U<<0)

void SysTick_Init(uint32_t);

#endif //__SYSTICK_INIT_H__

