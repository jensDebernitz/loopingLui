/*
 * LL_GameModes.c
 *
 *  Created on: 01.08.2014
 *      Author: B�ro Debernitz
 */

#include <stdlib.h>
#include <stdio.h>
#include "avr/io.h"

#include "Misc/GlobalDefines.h"

#include "LedModule/LL_LedModule.h"

#include "GameModes/LL_GameModes.h"

#include "Timer/LL_Timer.h"

#include "Motor/LL_Motor.h"

GameModes globalGameMode;
uint8_t randomSpeed;
uint8_t randomDirection;
uint8_t timerTick;
uint8_t startGame;

void initGameModeModul(void)
{
   timerTick = getTimerTick1Sec();
   startGame = 0;
}

void setGameMode(GameModes gameMode)
{
   globalGameMode = gameMode;

   switch (gameMode)
   {
   case GameMode_0:
      setSegementDisplay(Figure_Zero);
      setSpeed(SPEED_STOP);
      randomSpeed = 0;
      randomDirection = 0;
      break;
   case GameMode_1:
      setSegementDisplay(Figure_One);
      setSpeed(SPEED_NORMAL);
      setDirection(forwards);
      break;
   case GameMode_2:
      setSegementDisplay(Figure_Two);
      setDirection(forwards);
      break;
   case GameMode_3:
      setSegementDisplay(Figure_Three);
      break;
   case GameMode_4:
      setSegementDisplay(Figure_Four);
      break;
   case GameMode_5:
      setSegementDisplay(Figure_Five);
      break;
   case GameMode_6:
      setSegementDisplay(Figure_Six);
      break;
   case GameMode_7:
      setSegementDisplay(Figure_Seven);
      break;
   default:
      break;
   }
}

void runGame(void)
{

   if (1 == startGame)
   {
      int8_t random = rand() % 100;
      setSpeed(1023);

      if (getTimerDiff1Sec(timerTick) >= 5)
      {
         timerTick = getTimerTick1Sec();

         if (random >= 50)
         {
            setDirection(forwards);
            setSegementDisplay(1);
         }
         else
         {
            setDirection(backwards);
            setSegementDisplay(2);
         }
      }
   }
   else
   {
      timerTick = getTimerTick1Sec();
      setSpeed(0);
   }
}

void setDifficulty(difficulties difficultyToSet)
{

}

void setStartGame(uint8_t start)
{
   startGame = start;
}
