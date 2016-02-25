/********************************************
 * BufferUpdate.c
 *
 * Edited by: Josh
 * Jan 2016
 *
 *********************************************/

#include "BufferUpdate.h"

void BufferUpdate(void){

	uint8_t i;	// used in "for" loops

	while(spr2buffLock == 1){;}

	if(playerSpr.hp > 0){				// If player survives...
		PrintSpr(&playerSpr,0);			// Prints player ship image to disply buffer.
	}else{								// Otherwise...
		if((playerSpr.toExplode > 0)	// If in the middle of explosion...
			&& (playerSpr.explode != 0)){
				ExplodeSpr(&playerSpr);	// Prints the explosion image to disply buffer.
				playerSpr.toExplode -=1;
			}
		}

	for(i = 0; i < PLAYBULS; i++){
		if(playerBullets[i].hp > 0) 		// If player's bullet is in effect...
			PrintSpr(&playerBullets[i],0);	// Prints the bullet image to disply buffer.
	}

	for(i = 0; i < BUNKERNUM; i++){
		PrintBunker(&bunkerSprs[i]);	// Updates bunkers' images.
	}

	for(i = 0; i < ENEMYNUM; i++){
		if(enemySprs[i].hp > 0)							// If enemy survives...
			PrintSpr(&enemySprs[i], alt_enemov % 2);	// Prints enemy ship image to disply buffer.
		else{											// Otherwise...
			if((enemySprs[i].toExplode > 0)				// If in the middle of explosion...
			&& (enemySprs[i].explode != 0)){
				ExplodeSpr(&enemySprs[i]);				// Prints the explosion image to disply buffer.
				enemySprs[i].toExplode -=1;
			}
		}
	}

	for(i = 0; i < ENEMYCOLS; i++){
		if(enemyBullets[i].hp > 0)			// If enemy's bullet is in effect...
			PrintSpr(&enemyBullets[i], 0);	// Prints the bullet image to disply buffer.
	}

	if(UFOSpr.hp > 0)						// If UFO survives...
		PrintSpr(&UFOSpr, alt_ufomov % 3);	// Prints UFO ship image to disply buffer.
	else{									// Otherwise...
		if((UFOSpr.toExplode > 0)			// If in the middle of explosion...
		&& (UFOSpr.explode != 0)){
			ExplodeSpr(&UFOSpr);			// Prints the explosion image to disply buffer.
			UFOSpr.toExplode -=1;
		}
	}
}
