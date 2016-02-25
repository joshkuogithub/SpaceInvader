# SpaceInvader

ARM Cortex M Programming: Arcade Game - Space Invader

Josh Kuo
Jan 2016

Space Invaders
A classic Arcade game - Space Invaders
You are about to save the galaxy on a Nokia5510 LCD screen.
Game operation is very intuitive.
Good Luck!

Hardware Specs
-----------------------------
Targeting Devices:	LM4F120/TM4C123
 
Pin Connuction Requirement:
 
 1. PE2	-	Slide Potentiometer (ANI1)
 2. PE0	-	Button Switch
 3. PA2	-	SSI0Clk (Nokia5110)
 4. PA3	-	SSI0Fss (Nokia5110)
 5. PA5	-	SSI0Tx	(Nokia5110)
 6. PA6	-	Data/Command (Nokia5110)
 7. Pa7	-	Reset (Nokia5110)


Some known issues:
1) PE1 initialized but never used.
2) UFO is not initialized in the game.

Peding Updates:
1) Solving known issues.
2) Add sound effect in the near future.
3) Create video or picture demo of the functioning system.
