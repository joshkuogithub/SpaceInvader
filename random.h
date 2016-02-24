/*Random number generator;
  Linear congruential generator
  from Numerical Recipes by Press et al.
  Jonathan Valvano

  How to use:
  Call Random_Init once with a seed. For example
      Random_Init(1);
      Random_Init(NVIC_CURRENT_R);
  Call Random over and over to get a new random number. For example
      n = Random();    // returns a random 32-bit number
      m = Random()%60; // returns a random number from 0 to 59
*/

#include "TM4C123GH6PM.h"

void Random_Init(uint32_t);

uint32_t Random(void);
