/*
 * main.c
 *
 *  Created on: 29.07.2014
 *      Author: B�ro Debernitz
 */

// Atmel Includes
#include <stdlib.h>
#include "avr/io.h"
#include "avr/interrupt.h"

// Hardware Includes
#include "Misc/GlobalDefines.h"
#include "Drinks/LL_Drinks.h"
#include "Timer/LL_Timer.h"
#include "Port/LL_Port.h"
#include "LedModule/LL_LedModule.h"
#include "Motor/LL_Motor.h"
#include "GameModes/LL_GameModes.h"

/*********************************************************************************
 CONSTANT DEFINITIONS
 *********************************************************************************/

#define time()       TCNT0

/*********************************************************************************
 MACROS
 *********************************************************************************/

/*********************************************************************************
 PROTOTYPES
 *********************************************************************************/

int main(void);
void initDevices(void);
void callBackSwitch1OneSec(void);
void callBackSwitch1ThreeSec(void);
void callBackSwitch2OneSec(void);
void callBackSwitch2ThreeSec(void);



/*********************************************************************************
 GLOBAL VARIABLES
 *********************************************************************************/

uint8_t random_nr;
uint8_t led_mode;

/*********************************************************************************
 SUBROUTINES
 *********************************************************************************/

void initDevices(void)
{
   initPorts();
   initTimer();
   initEngine();
   initGameModeModul();

   initSegmentDisplay();
   initDrinkModul();

   setFunctionPointerSwitch(Pressed_Switch_1_One_Seconds, callBackSwitch1OneSec);
   setFunctionPointerSwitch(Pressed_Switch_1_Three_Seconds, callBackSwitch1ThreeSec);
   setFunctionPointerSwitch(Pressed_Switch_2_One_Seconds, callBackSwitch2OneSec);
   setFunctionPointerSwitch(Pressed_Switch_2_Three_Seconds, callBackSwitch2ThreeSec);

   MCUCR = 0x00;
   EICRA = 0x00; //extended ext ints
   EICRB = 0x00; //extended ext ints
   EIMSK = 0x00;
   ETIMSK = 0x00; //extended timer interrupt sources
   enableTimer0Interrupt();
   sei();
}


/*********************************************************************************
 MAIN ROUTINE
 *********************************************************************************/

int main(void)
{
   initDevices();

   setSpeed(1023);

   do
   {
//      if(isSwitchPressed(SWITCH_1) && isSwitchPressed(SWITCH_2))
//      {
//         // Acoustic reset
//         setSegementDisplay(0, 1);
//         PORTB &= ~(1 << PIEZO);
//      }
//      else if (isSwitchPressed(SWITCH_1))
//      {
//         startSearchNewDrink();
//         setSegementDisplay(1, 1);
//         PORTB |= (1 << PIEZO);
//      }
//      else if (isSwitchPressed(SWITCH_2))
//      {
//         setSegementDisplay(2, 1);
//         PORTB |= (1 << PIEZO);
//      }
//      else
//      {
//         setSegementDisplay(3, 1);
//         PORTB |= (1 << PIEZO);
//      }
      runGame();

   } while (1);

   return 0;
}

void callBackSwitch1OneSec(void)
{
   static uint8_t toggleBit = 0;
   toggleBit ^= 1;
   setLEDBlinking(Led_Blue_2, toggleBit, 0x10);
   setStartGame(1);
}

void callBackSwitch1ThreeSec(void)
{
   static uint8_t toggleBit = 0;
   toggleBit ^= 1;
   setLEDBlinking(Led_Blue_3, toggleBit, 0x10);
}

void callBackSwitch2OneSec(void)
{
   static uint8_t toggleBit = 0;
   toggleBit ^= 1;
   setLEDBlinking(Led_Blue_4, toggleBit, 0x10);
   setStartGame(0);
}

void callBackSwitch2ThreeSec(void)
{
   static uint8_t toggleBit = 0;
   toggleBit ^= 1;
   setLEDBlinking(Led_Blue_5, toggleBit, 0x10);
}
