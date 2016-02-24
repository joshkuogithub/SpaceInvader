/********************************************
 * GAMESETTING.h
 *
 * Edited by: Josh
 * Jan 2016
 *
 *********************************************/

/*** INCLUDES ***/

#include "TM4C123GH6PM.h"
#include "Sprites.h"

/*** DEFINITIONS ***/
#define UFOH 7          // height of UFO's row (will be at top)
#define PLAYERH 8       // height of player ship's row (will be at bottom)
#define BUNKERH 5       // height of bunker's row (will be right above player's ship row)

#define SCREENW     84
#define SCREENH     48

#define MINSCREENY 2    // Minimum screen y-coord (top)
#define MAXSCREENY 47   // Maximum screen y-coord (bottom)
#define EFFSCREENH (MAXSCREENY - MINSCREENY)    // effective screen height
#define MINSCREENX 0    // Minimum screen x-coord (left)
#define MAXSCREENX 82   // Maximum screen x-coord (right)
#define EFFSCREENW (MAXSCREENX - MINSCREENX)    // effective screen width

#define ENEMYGAPX 0     // horizontal gap (in px) between adjacent enemy sprites
#define ENEMYGAPY 1     // vertical gap (in px) between adjacent enemy sprites
#define ENEMYROWS 2     // number of rows in enemy horde
#define ENEMYCOLS 4     // number of columns in enemy horde
#define ENEMYNUM (ENEMYROWS * ENEMYCOLS)    // number of enemies in horde

#define PLAYBULS 25     // number of player bullets can exist on the screen

#define BUNKERNUM 3     // max number of bunkers

#define ALTMAX 12       // max value of alt (will be lowest common multipler of images and sound options)

#define ENEMYSHOOTDIV 10000U    // Each enemy's chance of shotting = enemyShoot/ENEMYSHOOTDIV

#define EXPDELAY 60     // A value used in SprCrash() to assign to sprite->toExplode,
                        // that indicates how many frames that explosion lasts.

#define MAXLVL 5	    // Max number of level.

/*** Global variables ***/

#ifdef __IS_GLOBAL__

sprite playerSpr, UFOSpr, bunkerSprs[BUNKERNUM], enemySprs[ENEMYNUM];   // ship sprites
sprite playerBullets[PLAYBULS], enemyBullets[ENEMYCOLS];                // bullet sprites

uint32_t ACT;			// A variable used to hold the read from button switch.
uint32_t ADCVal;        // A variable used to hold te value read from the Slide Pot.

uint32_t score;			// A variable used to hold score gained.
uint8_t spr2buffLock;	// A variable used by BufferUpdate() and SysTick_Handler() (Game Update)
						// If 0: Unlocked the operation of Reading of all sprites and writing to buffer
						// If 1: Lock the operation of ...

uint8_t enemov;
uint8_t enebul;

uint8_t bulfir;
uint8_t bulfly;

uint8_t ufomov;

uint8_t alt_enemov;     // A variable used in SysTick_Handler() to alter the enemy sprites' image.
uint8_t alt_ufomov;     // A variable used in SysTick_Handler() to alter the UFO sprite's image.

uint8_t enemyDir;
uint32_t enemyShoot;    // Each enemy's chance of shotting = enemyShoot/ENEMYSHOOTDIV

uint8_t level;          // A variable used to indicate the game difficulty level.
uint8_t lvlCleared;     // A variable used to check if the level is cleared.
                        // Checked at the end of each SysTick_Handler call.

#endif
#ifndef __IS_GLOBAL__

extern sprite playerSpr, UFOSpr, bunkerSprs[BUNKERNUM], enemySprs[ENEMYNUM]; // sprites
extern sprite playerBullets[PLAYBULS], enemyBullets[ENEMYCOLS]; // bullet sprites

extern uint32_t ACT;			// A variable used to hold the read from buttons
extern uint32_t ADCVal;         // A variable used to hold the value read from the Slide Pot

extern uint32_t score;		    // Score gained.
extern uint8_t spr2buffLock;	// A variable used by BufferUpdate() and SysTick_Handler (Game Update)
								// If 0: Unlocked the operation of Reading sprites and writing to buffer
								// If 1: Lock the operation of ...


extern uint8_t enemov;
extern uint8_t enebul;

extern uint8_t bulfir;
extern uint8_t bulfly;

extern uint8_t ufomov;

extern uint8_t alt_enemov;      // A variable used in SysTick_Handler() to alter the enemy sprites' image.
extern uint8_t alt_ufomov;	    // A variable used in SysTick_Handler() to alter the UFO sprite's image.

extern uint8_t enemyDir;
extern uint32_t enemyShoot;     // Each enemy's chance of shotting = enemyShoot/ENEMYSHOOTDIV
extern uint8_t level;           // A variable used to indicate the game difficulty level.
extern uint8_t lvlCleared;      // A variable used to check if the level is cleared.
                                // Checked at the end of each SysTick_Handler call.

#endif //__IS_GLOBAL__

