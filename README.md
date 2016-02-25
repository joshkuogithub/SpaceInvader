# SpaceInvader

ARM Cortex M Programming: Arcade Game - Space Invader
-----------------------------

Josh Kuo
Jan 2016

Game Description
-----------------------------
A classic Arcade game. 
You are about to save the galaxy on a Nokia5510 LCD screen. 
Game control is very intuitive. Watch the demo video on Youtube: https://youtu.be/PbEe4651eyA
Good Luck Saving the Galaxy!

Hardware Specs
-----------------------------
Targeting Devices:	LM4F120/TM4C123
 
Pin Connection Requirement:
 
 1. PE2	-	Slide Potentiometer (ANI1)
 2. PE0	-	Button Switch
 3. PA2	-	SSI0Clk (Nokia5110)
 4. PA3	-	SSI0Fss (Nokia5110)
 5. PA5	-	SSI0Tx	(Nokia5110)
 6. PA6	-	Data/Command (Nokia5110)
 7. PA7	-	Reset (Nokia5110)


Known Issues:
-----------------------------
1) PE1 initialized but never used.
2) UFO is not initialized in the game.

Pending Updates:
-----------------------------
1) Solving known issues.
2) Add audio effect in the near future.
3) Create video or picture demo of the functioning system.
