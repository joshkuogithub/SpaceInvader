/********************************************
 * PortE_Ctrl_Init.h
 *
 * Edited by: Josh
 * Jan 2016
 *
 *********************************************/

#ifndef __PORTE_CTRL_INIT_H__
#define __PORTE_CTRL_INIT_H__

#include "TM4C123GH6PM.h"

#define PE0 (1U<<0)
#define PE1 (1U<<1)
#define PE2 (1U<<2)

void PortE_Ctrl_Init(void);

#endif // __PORTE_CTRL INIT_H__
