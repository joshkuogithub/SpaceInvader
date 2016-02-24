/********************************************
 * EnableInterrupts.h
 *
 * Edited by: Josh
 * Jan 2016
 *
 *********************************************/

#ifndef __ENABLEINTERRUPTS_H__
#define __ENABLEINTERRUPTS_H__

#include "TM4C123GH6PM.h"
#include "SysTick_Init.h"

void Enable_Control(void);

void Enable_SysTick(void);

void Disable_SysTick(void);

#endif //__ENABLEINTERRUPTS_H__
