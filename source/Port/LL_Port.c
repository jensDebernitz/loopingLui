/*
 * LL_Port.c
 *
 *  Created on: 28.04.2015
 *      Author: jdebernitz
 */
#include <stdlib.h>
#include "avr/io.h"

#include "Misc/Globaldefines.h"
#include "Timer/LL_Timer.h"
#include "LedModule/LL_LedModule.h"
#include "Port/LL_Port.h"

static const uint16_t TIME_ONE_SEC = 60;
static const uint16_t TIME_THREE_SEC = 180;

typedef void (*functionPointerPort)(void);
static functionPointerPort FunctionPointerList[Function_Pointer_Options_Enum_Count];

void portHandler(void);

void initPorts(void)
{
   //switch Port A to OutPut
   DDRA = 0xFF;

   // set PortB directions (piezo and motor control)
   DDRB |= (1 << PIEZO);
   DDRB |= (1 << MOTOR_IN_1) | (1 << MOTOR_IN_2);
   DDRB |= (1 << MOTOR_ENABLE);

   // set selected PortB pins to high
   PORTB |= (1 << MOTOR_ENABLE);
   PORTB |= (1 << PIEZO);

   // switch Port C to OutPut (LEDPort1)
   DDRC = 0xFF;

   // switch Port D to OutPut (LEDPort2)
   DDRD = 0xFF;

   //switch Port E to InPut
   DDRE = 0x00;

   //switch Port F to InPut
   DDRF = 0x00;
   PORTF = 0xFF;

   //init the function pointer list
   for (int i = 0; i < Function_Pointer_Options_Enum_Count; ++i)
   {
      FunctionPointerList[i] = NULL;
   }

   setFunctionPointerTimer0(portHandler);
}

uint8_t isSwitchPressed(uint8_t hardwareSwitch)
{
   if (PINF & (1 << hardwareSwitch))
   {
      return 0;
   }
   else
   {
      return 1;
   }
}
//Set void Function in the FuncionPoinerList0
uint8_t setFunctionPointerSwitch(functionPointerType type,
                                 void (*fp)(void))
{
   if (fp == NULL || type >= Function_Pointer_Options_Enum_Count)
   {
      return 1;
   }
   else
   {
      FunctionPointerList[type] = fp;
      return 0;
   }
}

void portHandler(void)
{
   static uint8_t pinBuffer = 0;
   static uint32_t timeCounter = 0;
   timeCounter++;

   if (pinBuffer == 0)
   {
      if (isSwitchPressed(SWITCH_1) && isSwitchPressed(SWITCH_2) && timeCounter >= TIME_ONE_SEC)
      {
         pinBuffer = 0x01;
      }

      if (isSwitchPressed(SWITCH_1) && !isSwitchPressed(SWITCH_2) && timeCounter >= TIME_ONE_SEC)
      {
         pinBuffer = 0x02;
      }

      if (!isSwitchPressed(SWITCH_1) && isSwitchPressed(SWITCH_2) && timeCounter >= TIME_ONE_SEC)
      {
         pinBuffer = 0x04;
      }
      else if (!isSwitchPressed(SWITCH_1) && !isSwitchPressed(SWITCH_2))
      {
         pinBuffer = 0;
         timeCounter = 0;
      }

   }
   else if (pinBuffer != 0)
   {
      if (pinBuffer == 0x01)
      {
         if (isSwitchPressed(SWITCH_1) && isSwitchPressed(SWITCH_2)
             && timeCounter >= TIME_THREE_SEC)
         {
            if (FunctionPointerList[Pressed_Switch_Both_Three_Seconds] != NULL)
            {
               FunctionPointerList[Pressed_Switch_Both_Three_Seconds]();
            }

            pinBuffer = 0;
            timeCounter = 0;
         }
         else if (!isSwitchPressed(SWITCH_1) && !isSwitchPressed(SWITCH_2)
                  && timeCounter < TIME_THREE_SEC)
         {
            if (FunctionPointerList[Pressed_Switch_Both_One_Seconds] != NULL)
            {
               FunctionPointerList[Pressed_Switch_Both_One_Seconds]();
            }

            pinBuffer = 0;
            timeCounter = 0;
         }
      }
      else if (pinBuffer == 0x02)
      {
         if (isSwitchPressed(SWITCH_1) && !isSwitchPressed(SWITCH_2)
             && timeCounter >= TIME_THREE_SEC)
         {
            if (FunctionPointerList[Pressed_Switch_1_Three_Seconds] != NULL)
            {
               FunctionPointerList[Pressed_Switch_1_Three_Seconds]();
            }

            pinBuffer = 0;
            timeCounter = 0;
         }
         else if (!isSwitchPressed(SWITCH_1) && !isSwitchPressed(SWITCH_2)
                  && timeCounter < TIME_THREE_SEC)
         {
            if (FunctionPointerList[Pressed_Switch_1_One_Seconds] != NULL)
            {
               FunctionPointerList[Pressed_Switch_1_One_Seconds]();
            }

            pinBuffer = 0;
            timeCounter = 0;
         }
      }
      else if (pinBuffer == 0x04)
      {
         if (!isSwitchPressed(SWITCH_1) && isSwitchPressed(SWITCH_2)
             && timeCounter >= TIME_THREE_SEC)
         {
            if (FunctionPointerList[Pressed_Switch_2_Three_Seconds] != NULL)
            {
               FunctionPointerList[Pressed_Switch_2_Three_Seconds]();
            }

            pinBuffer = 0;
            timeCounter = 0;
         }
         else if (!isSwitchPressed(SWITCH_1) && !isSwitchPressed(SWITCH_2)
                  && timeCounter < TIME_THREE_SEC)
         {
            if (FunctionPointerList[Pressed_Switch_2_One_Seconds] != NULL)
            {
               FunctionPointerList[Pressed_Switch_2_One_Seconds]();
            }

            pinBuffer = 0;
            timeCounter = 0;
         }
      }
   }
}

