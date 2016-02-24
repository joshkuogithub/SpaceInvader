/*****************************************
 * Sprites.h
 *
 * Functions to create & manage sprites
 * Acknowledgement: Billy.Ljm
 * Edited by: Josh
 * Jan 2016
 *
 ****************************************/

#ifndef __SPRITES_H__
#define __SPRITES_H__

typedef struct sprite{
	unsigned char x; 				// x-cooridnate
	unsigned char y; 				// y-coordinate
	unsigned char hp; 				// hit points
	unsigned char pt; 				// score points for killing sprite
	unsigned char width;			// sprite's width in px
	unsigned char height;			// sprite's height in px
	unsigned char toExplode;		// a flag indicates to explode in the next (few) frame(s)
	const unsigned char* explode; 	// sprite exploding image
	const unsigned char* block; 	// image to cover & erase sprite
	const unsigned char* image[5]; 	// sprite's image(s)
} sprite;

// Intialise player's ship sprite at (x,y)
// Returns: sprite of player's ship
sprite Player_Init(unsigned char x, unsigned char y);


// Initialise bunker at (x,y) with specified hp
// Returns: sprite of bunker
sprite Bunker_Init(unsigned char x, unsigned char y);


// Intialise 1 enemy sprite of specified variant at (x,y)
// Returns: sprite of enemy
sprite Enemy_Init(unsigned char x, unsigned char y, unsigned char variant);


// Intialise a UFO at (x,y)
// Returns: sprite of UFO
sprite UFO_Init(unsigned char x, unsigned char y);


// Initialise laser sprite at center of sprite
// direction = 0 -> downward laser, direction = 1 -> upwards laser
// Returns: sprite of laser
void ShootLaser(sprite* spr, sprite* laser, unsigned char updir);


// Display title screen
void TitleScreen(void);


// Display game over screen
void GameOverScreen(void);


// Checks if 2 sprites have collided
// returns: 1 if sprites crash, 0 otherwise
unsigned char CrashCheck(sprite* spr1, sprite* spr2);

#endif //__SPRITES_H__

