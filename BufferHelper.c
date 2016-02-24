/********************************************
 * BufferHelper.c
 *
 * Edited by: Josh
 * Jan 2016
 *
 *********************************************/

#include "BufferHelper.h"

void PrintSpr(sprite* spr, uint8_t var){
// Prints specified image of a sprite to the display buffer.
	Nokia5110_PrintBMP(spr->x, spr->y, spr->image[var], 0);
}

void PrintBunker(sprite* bunker){
// Print appropraite bunker image based on the bunker's hp.
	if(bunker->hp > (20))
		PrintSpr(bunker, 0);
	else if(bunker->hp > (10))
		PrintSpr(bunker, 1);
	else if(bunker->hp > 0)
		PrintSpr(bunker,2 );
}

void ExplodeSpr(sprite* spr){
// Print sprite's explosion image.
	Nokia5110_PrintBMP(spr->x, spr->y, spr->explode,0);
}

