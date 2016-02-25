/********************************************
 * SpritesHelper.c
 *
 * Edited by: Josh
 * Jan 2016
 *
 *********************************************/

#include "SpritesHelper.h"

void SprCrash(sprite* bullet, sprite* spr){

	// Checks of bullet hits player/enemy sprites & update

	if((bullet->hp > 0 && spr->hp > 0) && CrashCheck(bullet, spr)){
		bullet->hp--;
		spr->hp--;
		score += spr->pt * level;
		if(spr->hp == 0 && (spr->explode != 0)){	// if the sprite just killed and it was initiated with a explode image
			spr->toExplode = EXPDELAY;				// a pre-defined number assigned to toExplode and is used as explosion delay
		} else{
			spr->toExplode = 0;
		}
	}
}
