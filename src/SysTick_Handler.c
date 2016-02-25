/********************************************
 * SysTick_Handler.c
 *
 * Edited by: Josh
 * Jan 2016
 *
 *********************************************/

#include "SysTick_Handler.h"

void SysTick_Handler(void){

	uint8_t i;
	uint8_t j;

	static uint8_t cnt_enemov = 0;
	static uint8_t cnt_enebul = 0;
	static uint8_t cnt_bulfir = 0;
	static uint8_t cnt_bulfly = 0;
	static uint8_t cnt_bulidx = 0;
	static uint8_t cnt_ufomov = 0;

	cnt_enemov = (cnt_enemov + 1)%enemov;	// indicates how fast enemy can move
	cnt_enebul = (cnt_enebul + 1)%enebul;	// indicates how fast the enemy bullet can fly
	cnt_bulfir = (cnt_bulfir + 1)%bulfir;	// indicates how frequent player can fire a bullet
	cnt_bulfly = (cnt_bulfly + 1)%bulfly;	// indicates how fast the player bullet can fly

	cnt_ufomov = (cnt_ufomov + 1)%ufomov;
	spr2buffLock = 1;						// Lock
	if(cnt_enemov == (enemov-1)){

		// Enemy Sprites Direction
		for(i = 0; i < ENEMYNUM; i++){
			if(enemySprs[i].hp > 0){
				if(enemySprs[i].x >= SCREENW - enemySprs[i].width)	// Enemy collides on right
					enemyDir = 1;
				else if(enemySprs[i].x <= 0)						// Enemy colldies on left
					enemyDir = 0;
			}
		}

		// Enemy Sprites Position Update
		for(i = 0; i < ENEMYNUM; i++){
			if(enemySprs[i].hp > 0){
				enemySprs[i].x += enemyDir == 0 ? 1 : -1;
			}
		}

		alt_enemov = (alt_enemov+1)%ALTMAX;

		// End of Enemy Ship Position Update.

	}

	if(cnt_ufomov == (ufomov-1)){

		// UFO Sprite Position Update

		if(UFOSpr.x > SCREENW - UFOSpr.width){ // If out of screen...
			UFOSpr.hp = 0;
		}

		if(UFOSpr.hp > 0){
			UFOSpr.x += 2;
		}

		alt_ufomov = (alt_ufomov+1)%ALTMAX;

		// End of UFO Ship Position Update

	}

	if(playerSpr.hp > 0){

		// Player Sprite Position Update

		/*
		 * ADCVal = 0x7F -> x = 0
		 *
		 * ADCVal = 0x00 -> x = (82 - (12-1))
		 */

		playerSpr.x = (uint8_t)(((0x7FU - ADCVal)*(0x54U - 0x12U))/0x7FU);
	}


	if(cnt_enebul == (enebul-1)){

		// Enemy Bullet Gneration (Shooting)
		for(i = 0; i < ENEMYCOLS; i++){	// 1 bullet per coloum
			if((enemyBullets[i].hp == 0) && (((Random()) % ENEMYSHOOTDIV) < enemyShoot)){	// random probability
				for(j = 0; j < ENEMYROWS; j++){
					if(enemySprs[j * ENEMYROWS + i].hp != 0){
						ShootLaser(&enemySprs[j * ENEMYROWS + i], &enemyBullets[i], 0);
						break;
					}
				}
			}
		}

		// Enemy Bullet Position Update
		for(i = 0; i < ENEMYCOLS; i++){
			if(enemyBullets[i].hp > 0){
				if(enemyBullets[i].y >= MAXSCREENY)
					enemyBullets[i].hp = 0;
				else
					enemyBullets[i].y += 1;
			}
		}

		// End of Enemy Bullet Position Update

	}


	// Player Bullet Generation

	if(cnt_bulfir == (bulfir-1)){

		if((playerSpr.hp > 0) && (ACT == 1U)){

			ACT = 0U;
			ShootLaser(&playerSpr, &playerBullets[cnt_bulidx], 1);
			cnt_bulidx = (cnt_bulidx + 1)%25;	// index of the firing bullet instance

		}
	}

	// Player Bullet Position Update

	if(cnt_bulfly == (bulfly-1)){

		for(i = 0; i < PLAYBULS; i++){
			if(playerBullets[i].hp > 0){
				if(playerBullets[i].y <= MINSCREENY)
					playerBullets[i].hp = 0;
				else
					playerBullets[i].y -= 1;
			}
		}

		// End of Player Bullet Position Update
	}



	//Collision Check
	for(i = 0; i < ENEMYCOLS; i++){
		for(j = 0; j < BUNKERNUM; j++){
			SprCrash(&enemyBullets[i], &bunkerSprs[j]);
		}
	}

	for(i = 0; i < PLAYBULS; i++){
		for(j = 0; j < BUNKERNUM; j++){
			SprCrash(&playerBullets[i], &bunkerSprs[j]);
		}
	}

	for(i = 0; i < PLAYBULS; i++){
		for(j = 0; j < ENEMYNUM; j++){
			SprCrash(&playerBullets[i], &enemySprs[j]);
		}
	}

	for(i = 0; i < ENEMYCOLS; i++){
			SprCrash(&enemyBullets[i], &playerSpr);
	}

	for(i = 0; i < PLAYBULS; i++){

		SprCrash(&playerBullets[i], &UFOSpr);
	}


	// If level cleared?
	lvlCleared = 1;
	for(i = 0; i < ENEMYNUM; i++){
		if(enemySprs[i].hp > 0)
			lvlCleared = 0;
	}

	spr2buffLock = 0;	// Unlock the sprite instances so it can be read (to update the LCD buffer).

}
