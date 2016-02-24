/********************************************
 * BufferHelper.h
 *
 * Edited by: Josh
 * Jan 2016
 *
 *********************************************/

#ifndef __BUFFERHELPER_H__
#define __BUFFERHELPER_H__

#include "TM4C123GH6PM.h"
#include "Sprites.h"
#include "Nokia5110.h"

void PrintSpr(sprite*, uint8_t);    // Prints specified image of a sprite to the display buffer.
void PrintBunker(sprite*);          // Print appropraite bunker image based on the bunker's hp.
void ExplodeSpr(sprite*);           // Print sprite's explosion image.

#endif //__BUFFERHELPER_H__

