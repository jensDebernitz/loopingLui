/*
 * LL_Drinks.c
 *
 *  Created on: 28.04.2015
 *      Author: jdebernitz
 */

#ifndef SOURCE_TRINKS_LL_DRINKS_C_
#define SOURCE_TRINKS_LL_DRINKS_C_

typedef enum
{
   Drink_Beer = 0,
   Drink_Liquor,
   Drink_Wine,
   Drink_Sparkling_Wine,
   Drink_Water,

   Drink_Enum_Counter

}drinkNames;

/**
 * @brief init for the Drink Modul
 */
void initDrinkModul(void);

/**
 * @brief start searching a new Drink
 */
void startSearchNewDrink(void);


#endif /* SOURCE_TRINKS_LL_DRINKS_C_ */
