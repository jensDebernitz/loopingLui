/*
 * LL_Trinks.c
 *
 *  Created on: 28.04.2015
 *      Author: jdebernitz
 */

#include <stdlib.h>

#include "Timer/LL_Timer.h"
#include "LedModule/LL_LedModule.h"

#include "Drinks/LL_Drinks.h"

volatile static int searchDrinkStarts;
static const uint16_t LED_SHIFT_TIME = 5; //LED shift Time * 10
static const uint16_t MAX_TIME_SEARCH = 500; //MaxTime search a drink * 10
static const uint16_t SHOW_TIME = 500; //show time for the result * 10
static uint32_t timeCounter = 0;

void clearAllDrinks(void);
/*
 * Prototypes
 */

void drinkModulHandler(void);

/*
 * public functions
 */
void initDrinkModul(void)
{
   searchDrinkStarts = 0;
   timeCounter = 0;
   setFunctionPointerTimer0(drinkModulHandler);

   clearAllDrinks();
}

void startSearchNewDrink(void)
{
   searchDrinkStarts = 1;
}

/*
 * private functions
 */

void drinkModulHandler(void)
{
   timeCounter++;
   static int oldRandomValue = 0;

   if (1 == searchDrinkStarts)
   {
      if (timeCounter < MAX_TIME_SEARCH)
      {
         if ((timeCounter % LED_SHIFT_TIME) == 0)
         {
            int randomValue = rand();
            setLED(oldRandomValue, LedOff);
            setLED(randomValue % 5, LedOn);
            oldRandomValue = randomValue % 5;
         }
      }
      else if (timeCounter == MAX_TIME_SEARCH)
      {
         setLEDBlinking(oldRandomValue, 1, 10);
      }
      else if (timeCounter == (SHOW_TIME + MAX_TIME_SEARCH))
      {
         clearAllDrinks();
         timeCounter = 0;
         searchDrinkStarts = 0;
      }
   }
   else
   {
      timeCounter = 0;
      searchDrinkStarts = 0;
   }
}

void clearAllDrinks(void)
{
   for (int i = Led_Red_1; i <= Led_Red_5; ++i)
   {
      setLED(i, LedOff);
      setLEDBlinking(i, 0, 0);
   }
}
