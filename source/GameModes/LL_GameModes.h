/*
 * LL_GameModes.h
 *
 *  Created on: 01.08.2014
 *      Author: B�ro Debernitz
 */

#ifndef LL_GAMEMODES_H_
#define LL_GAMEMODES_H_

#include <stdint.h>

typedef enum
{
   /*
    * Stop, waiting for commands
    */
	GameMode_0,

	/*
    * Standard GameMode
    */
	GameMode_1,

	/*
	 * Movement: fixed forwards
	 * Speed: adjustable
	 */
	GameMode_2,

   /*
    * Movement: fixed backwards
    * Speed: adjustable
    */
	GameMode_3,

   /*
    * Movement: random
    * Speed: adjustable
    */
	GameMode_4,

   /*
    * Movement: random
    * Speed: random
    */
	GameMode_5,

   /*
    * Movement: fixed forwards
    * Speed: random
    */
	GameMode_6,

   /*
    * Movement: fixed backwards
    * Speed: random
    */
	GameMode_7
} GameModes;

typedef enum
{
   Difficulty_0,
   Difficulty_1,
   Difficulty_2,
   Difficulty_3,
   Difficulty_4,
   Difficulty_5,
   Difficulty_6,
   Difficulty_7,
   Difficulty_8,
   Difficulty_9,
   Difficulty_10,
} difficulties;

void initGameModeModul(void);

void setGameMode(GameModes gameMode);

void runGame(void);

void setDifficulty(difficulties difficultyToSet);

void setStartGame(uint8_t start);

#endif /* LL_GAMEMODES_H_ */
