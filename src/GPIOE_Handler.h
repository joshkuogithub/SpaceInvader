/********************************************
 * GPIO__Handler.h
 *
 * Edited by: Josh
 * Jan 2016
 *
 *********************************************/

#ifndef __GPIOE_HANDLER_H__
#define __GPIOE_HANDLER_H__

#define PE0 (1U<<0)
#define PE1 (1U<<1)

#include "TM4C123GH6PM.h"
#include "GAMESETTING.h"

void GPIOE_Handler(void);

#endif //__GPIOE_HANDLER_H__
