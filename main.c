/********************
 *
 * main.c
 *
 * Space Invaders
 * A classic Arcade game - Space Invaders
 * You are about to save the galaxy on a Nokia5510 LCD screen.
 * Game operation is very intuitive.
 * Good Luck!
 *
 * Author: Josh
 * Date: Jan 2016
 *
 *
 ********************/

/********************
 *
 *  Hardware Specs
 *  -----------------------------
 *  Targeting Devices:	LM4F120/TM4C123
 *
 *  Pin Connuction Requirement:
 *
 * 1. PE2	-	Slide Potentiometer (ANI1)
 * 2. PE0	-	Button Switch
 * 3. PA2	-	SSI0Clk (Nokia5110)
 * 4. PA3	-	SSI0Fss (Nokia5110)
 * 5. PA5	-	SSI0Tx	(Nokia5110)
 * 6. PA6	-	Data/Command (Nokia5110)
 * 7. Pa7	-	Reset (Nokia5110)
 *
 ********************/

#include "TM4C123GH6PM.h"			//CMSIS Cortex-M4 Peripheral Access Layer Header File
#include "random.h"
#define __IS_GLOBAL__
#include "GAMESETTING.h"
#include "PortE_Ctrl_Init.h"
#include "ADC0_Init.h"
#include "ADC0_InSeq3.h"
#include "SysTick_Init.h"
#include "EnableInterrupts.h"
#include "Nokia5110.h"
#include "BufferUpdate.h"

void Delay100ms(uint32_t);
void ScreenTitle(void);
void ScreenNextlvl(void);
void GameOver(void);
void GameWin(void);

void player_hp(uint32_t);
void enemy_hp(uint32_t);
void enemy_pt(uint32_t);
void Para_Set(uint32_t);
void Game_Reset(void);
void Player_Build(void);
void Bunker_Build(void);
void Enemy_Build(void);
void Entity_Clear(void);
void Entity_Build(void);
void Level_Init(void);


int main(void){

	// Seeds randomness.
	__IO uint32_t rand;
	rand = Random();
	Random_Init(rand);

	// Initializes Ports and Peripherals.
	PortE_Ctrl_Init();
	ADC0_init();
	Nokia5110_Init();
	SysTick_Init(1666665U);	// 30Hz = (50MHz)/1666666

	Enable_Control();	// Enables PORTE interrupt triggerd by button switchs
	ScreenTitle();		// Display sGame Title and wait player press to starts
	Entity_Clear();		// Clears game entities like playership, UFO, etc.
	Entity_Build();		// Initializes game entities.
	Game_Reset();		// Initializes game paramenters.
	Enable_SysTick();	// Enables SysTick interrupt.

	while(1){

		spr2buffLock = 1;	// Locks BufferUpdate() and waits for SysTich_Handler() to unlock.
		while(((playerSpr.hp > 0) || (playerSpr.toExplode > 0)) && level <= MAXLVL){

			if(lvlCleared){	// lvlCleared is set 1 in SysTick_Handler() if all enemies are elinimated.
				Disable_SysTick();
				lvlCleared = 0;
				Entity_Clear();
				Entity_Build();
				ScreenNextlvl();	// Displays level info and waits player press to continue.
				level += 1;
				Para_Set(level);	// Resets game paramenters per level
				Enable_SysTick();
			}

			ADCVal = (ADC0_InSeq3()>>5);	// Reads Slide Pot input. Used in SysTick_Handler() for playership position.
			Nokia5110_ClearBuffer();
			BufferUpdate();					// Updates display buffer according to the current entities (sprites) status.
			Nokia5110_DisplayBuffer();

		}

		// Game end condition is reached.

		Disable_SysTick();
		if(playerSpr.hp == 0){	// If player is defeated...
			GameOver();			// Game is over and wait for player press to restart.
		} else{
			GameWin();			// Otherwise, galaxy is saved and wait for player to save again.
			}
		Entity_Clear();
		Entity_Build();
		Game_Reset();
		Enable_SysTick();

	}

}

void Game_Reset(void){

	// Resets global variables.
	score = 0;
	alt_enemov = 0;
	alt_ufomov = 0;
	lvlCleared = 0;
	level = 1;

	Para_Set(level);

}

void Para_Set(uint32_t lvl){

	// Set global variables
	enemov = 11 - lvl;
	enebul = 11 - lvl;
	bulfir = 10;
	bulfly = 3;
	ufomov = 5;

	enemyShoot = 500*lvl; //ENEMYSHOOTDIV 10000U

	// Modifies entities (sprites) attributs
	player_hp(lvl);
	enemy_hp(lvl);
	enemy_pt(lvl);

}

void player_hp(uint32_t lvl){

	playerSpr.hp = (lvl < MAXLVL)? (1+lvl/2):(1+MAXLVL/2);

}
void enemy_hp(uint32_t lvl){
	uint8_t i;
	for (i = 0; i < ENEMYNUM; i++){
		enemySprs[i].hp = (lvl < MAXLVL)? lvl : MAXLVL;
	}
}
void enemy_pt(uint32_t lvl){
	uint8_t i;
	for (i = 0; i < ENEMYNUM; i++){
		enemySprs[i].pt = (lvl < MAXLVL)? lvl : MAXLVL;
	}
}


void Level_Init(void){

	Entity_Clear();
	Entity_Build();

}

void Entity_Build(void){

	Player_Build();
	Bunker_Build();
	Enemy_Build();

}

void Entity_Clear(void){

	uint8_t i;

	// Clears playerBullets & screen
	for(i = 0; i < PLAYBULS; i++){ // for all play bullets
		playerBullets[i].hp = 0;
	}

	// Clears enemyBullets[] & screen
	for(i = 0; i < ENEMYCOLS; i++){ // for all enemies
		enemyBullets[i].hp = 0;
	}

	// Clears Bunkers & screen
	for(i = 0; i < BUNKERNUM; i++){
		bunkerSprs[i].hp = 0;
	}

	// Clears enemySprs[] & screen
	for(i = 0; i < ENEMYNUM; i++){ // for all enemies
		enemySprs[i].hp = 0;
	}

	// Clears playerSpr & screen
	playerSpr.hp = 0;

	// Clears UFOSpr & screen
	UFOSpr.hp = 0;

}

void Player_Build(void){

	sprite tmp;

	// Player initialisation.
	tmp = Player_Init(0,0);		// to get tmp.width
	playerSpr = Player_Init(MINSCREENX + (EFFSCREENW - tmp.width)/2,MAXSCREENY);

}

void Bunker_Build(void){

	uint8_t x_coord, y_coord;	// coordinates
	uint8_t i; 					// used in "for" loops
	uint8_t gap;				// gap b/w bunkers
	sprite tmp; 				// to get .width of any sprite

	// Bunkers initialisation
	tmp = Bunker_Init(0,0);
	y_coord = MAXSCREENY - PLAYERH;
	gap = (EFFSCREENW - BUNKERNUM * tmp.width) / (BUNKERNUM - 1);
	for(i = 0; i < BUNKERNUM; i++){ // For each bunker
		x_coord = MINSCREENX + i * (tmp.width + gap);
		bunkerSprs[i] = Bunker_Init(x_coord, y_coord);
	}

}

void Enemy_Build(void){

// Fills enemySprs[] with enemy horde of ENEMYCOLS & ENEMYROWS.
// Enemy type randomly varies between rows.
// Nokia5110 displays up to 2 rows & 5 columns.
// Indexing increases left to right from front row, then following rows.

	uint8_t y_coord, x_coord; 	// individual enemy coordinates
	uint8_t i, j; 				// used in "for" loops
	uint8_t	var; 				// enemy variant factor
	sprite enemyT;

	enemyT = Enemy_Init(0,0,0); // temperary sprite to get enemy.width
	enemyDir = 0; 				// enemies moves to right at begining

	// Filling enemySprs[] & print
	for(i = 0; i < ENEMYROWS; i++){		// for each row
		y_coord = MINSCREENY + UFOH + (enemyT.height + 1) * (ENEMYROWS - i);
		var = (Random() >> 24) % 4;
		for(j = 0; j < ENEMYCOLS; j++){	// for each colum in a row
			x_coord = MINSCREENX + j * (enemyT.width + ENEMYGAPY);
			enemySprs[i * ENEMYCOLS + j] = Enemy_Init(x_coord, y_coord, var);
		}
	}
}

void ScreenTitle(void){

	// Displays the title of the game.
	// Waits player press to start the game.

	Nokia5110_Clear();
	Nokia5110_SetCursor(3,1);
	Nokia5110_OutString("SPACE");
	Nokia5110_SetCursor(2,2);
	Nokia5110_OutString("INVADERS");
	Nokia5110_SetCursor(1,4);
	Nokia5110_OutString("Press Fire");
	Delay100ms(5);
	ACT = 0U;
	while(ACT != 1U){;}		// ACT is modified in PORTE_Handler() triggered by play pressing button.
	ACT = 0U;
	Delay100ms(5);
}

void ScreenNextlvl(void){

	// Displays level-cleared info.
	// Watis player press to continue to the next level.

	Nokia5110_Clear();
	Nokia5110_SetCursor(0,0);
	Nokia5110_OutString("Level:");
	Nokia5110_OutUDec(level);
	Nokia5110_SetCursor(0,1);
	Nokia5110_OutString("Cleared!");
	Nokia5110_SetCursor(1,3);
	Nokia5110_OutString("Press Fire");
	Nokia5110_SetCursor(0,5);
	Nokia5110_OutString("score:");
	Nokia5110_OutUDec(score);
	Delay100ms(5);
	ACT = 0U;
	while(ACT != 1U){;}		// ACT is modified in PORTE_Handler() triggered by play pressing button.
	ACT = 0U;
	Delay100ms(5);
}

void GameOver(void){

	// Spreads the joy of Galaxy being saved!
	// Waits player to press to restart the game.

	Nokia5110_Clear();
	Nokia5110_SetCursor(1,1);
	Nokia5110_OutString("Nice Try,");
	Nokia5110_SetCursor(1,2);
	Nokia5110_OutString("Earthling");
	Nokia5110_SetCursor(1,3);
	Nokia5110_OutString("Press Fire");
	Nokia5110_SetCursor(0,4);
	Nokia5110_OutString("score:");
	Nokia5110_OutUDec(score);
	Nokia5110_SetCursor(0,5);
	Nokia5110_OutString("level:");
	Nokia5110_OutUDec(level);
	Delay100ms(5);
	ACT = 0U;
	while(ACT != 1U){;}
	ACT = 0U;
	Delay100ms(5);
}

void GameWin(void){

	// Delivers message from invaders...
	// Waits player to press to restart game.

	Nokia5110_Clear();
	Nokia5110_SetCursor(2,1);
	Nokia5110_OutString("Galaxy");
	Nokia5110_SetCursor(2,2);
	Nokia5110_OutString("Saved!");
	Nokia5110_SetCursor(1,3);
	Nokia5110_OutString("Press Fire");
	Nokia5110_SetCursor(0,4);
	Nokia5110_OutString("score:");
	Nokia5110_OutUDec(score);
	Nokia5110_SetCursor(0,5);
	Nokia5110_OutString("level:");
	Nokia5110_OutUDec(level);
	Delay100ms(5);
	ACT = 0U;
	while(ACT != 1U){;}
	ACT = 0U;
	Delay100ms(5);
}

void Delay100ms(uint32_t t){
	// dummy delay loop
	__IO uint32_t counter;
	counter = t * 500000U;
	while(counter){counter--;}
}
