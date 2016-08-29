/*
 * LL_LedModule.c
 *
 *  Created on: 01.08.2014
 *      Author: B�ro Debernitz
 */

#include "Misc/GlobalDefines.h"
#include "Timer/LL_Timer.h"

#include "LedModule/LL_LedModule.h"

typedef struct
{
   uint8_t isBlinking;
   uint32_t blinkingFrequency;
   uint32_t blinkingCounter;
} blinkingInformationsStr;

blinkingInformationsStr blinkingInformations[Led_Display_Max_Counter];

void clearScreen(void);
void blinkingHandler(void);

void initSegmentDisplay(void)
{
   clearScreen();

   //init the blinking Struct
   for (int i = 0; i < Led_Display_Max_Counter; ++i)
   {
      blinkingInformations[i].blinkingFrequency = 0;
      blinkingInformations[i].isBlinking = 0;
      blinkingInformations[i].blinkingCounter = 0;
   }

   setFunctionPointerTimer0(blinkingHandler);

}

void setSegementDisplay(segmentDisplay figure)
{
   clearScreen();

   segmentDisplayDot dotPoint = No_Dot;

   switch (figure)
   {
   case Figure_Zero:
      PORTA = (LED_SEGMENT_A | LED_SEGMENT_B | LED_SEGMENT_C | LED_SEGMENT_D | LED_SEGMENT_E | LED_SEGMENT_F);
      break;
   case Figure_One:
      PORTA = (LED_SEGMENT_B | LED_SEGMENT_C);
      break;
   case Figure_Two:
      PORTA = (LED_SEGMENT_A | LED_SEGMENT_B | LED_SEGMENT_D | LED_SEGMENT_E | LED_SEGMENT_G);
      break;
   case Figure_Three:
      PORTA = (LED_SEGMENT_A | LED_SEGMENT_B | LED_SEGMENT_C | LED_SEGMENT_D | LED_SEGMENT_G);
      break;
   case Figure_Four:
      PORTA = (LED_SEGMENT_B | LED_SEGMENT_C | LED_SEGMENT_F | LED_SEGMENT_G);
      break;
   case Figure_Five:
      PORTA = (LED_SEGMENT_A | LED_SEGMENT_C | LED_SEGMENT_D | LED_SEGMENT_F | LED_SEGMENT_G);
      break;
   case Figure_Six:
      PORTA = (LED_SEGMENT_A | LED_SEGMENT_C | LED_SEGMENT_D | LED_SEGMENT_E | LED_SEGMENT_F
               | LED_SEGMENT_G);
      dotPoint = Dot;
      break;
   case Figure_Seven:
      PORTA = (LED_SEGMENT_A | LED_SEGMENT_B | LED_SEGMENT_C);
      break;
   case Figure_Eight:
      PORTA = (LED_SEGMENT_A | LED_SEGMENT_B | LED_SEGMENT_C | LED_SEGMENT_D | LED_SEGMENT_E
               | LED_SEGMENT_F | LED_SEGMENT_G);
      break;
   case Figure_Nine:
      PORTA = (LED_SEGMENT_A | LED_SEGMENT_B | LED_SEGMENT_C | LED_SEGMENT_D | LED_SEGMENT_F
               | LED_SEGMENT_G);
      dotPoint = Dot;
      break;
   case Figure_A:
      PORTA = (LED_SEGMENT_A | LED_SEGMENT_B | LED_SEGMENT_C | LED_SEGMENT_E | LED_SEGMENT_F
               | LED_SEGMENT_G);
      break;
   case Figure_B:
      PORTA = (LED_SEGMENT_C | LED_SEGMENT_D | LED_SEGMENT_E | LED_SEGMENT_F | LED_SEGMENT_G);
      break;
   case Figure_C:
      PORTA = (LED_SEGMENT_A | LED_SEGMENT_D | LED_SEGMENT_E | LED_SEGMENT_F);
      break;
   case Figure_D:
      PORTA = (LED_SEGMENT_B | LED_SEGMENT_C | LED_SEGMENT_D | LED_SEGMENT_E | LED_SEGMENT_G);
      break;
   case Figure_E:
      PORTA = (LED_SEGMENT_A | LED_SEGMENT_D | LED_SEGMENT_E | LED_SEGMENT_F | LED_SEGMENT_G);
      break;
   case Figure_F:
      PORTA = (LED_SEGMENT_A | LED_SEGMENT_E | LED_SEGMENT_F | LED_SEGMENT_G);
      break;
   default:
      break;
   }

   if (dotPoint == Dot)
   {
      PORTA |= LED_SEGMENT_DOT;
   }
   else
   {
      PORTA &= ~LED_SEGMENT_DOT;
   }
}

void setLED(ledDisplay displayed,
            ledStatus status)
{
   uint8_t *port;
   uint8_t operand;

   switch (displayed)
   {
   case Led_Red_1:
      port = (uint8_t*) &PORTC;
      operand = RED_1;
      break;
   case Led_Red_2:
      port = (uint8_t*) &PORTC;
      operand = RED_2;
      break;
   case Led_Red_3:
      port = (uint8_t*) &PORTC;
      operand = RED_3;
      break;
   case Led_Red_4:
      port = (uint8_t*) &PORTC;
      operand = RED_4;
      break;
   case Led_Red_5:
      port = (uint8_t*) &PORTC;
      operand = RED_5;
      break;
   case Led_Blue_1:
      port = (uint8_t*) &PORTD;
      operand = BLUE_1;
      break;
   case Led_Blue_2:
      port = (uint8_t*) &PORTD;
      operand = BLUE_2;
      break;
   case Led_Blue_3:
      port = (uint8_t*) &PORTD;
      operand = BLUE_3;
      break;
   case Led_Yellow_1:
      port = (uint8_t*) &PORTD;
      operand = YELLOW_1;
      break;
   case Led_Yellow_2:
      port = (uint8_t*) &PORTD;
      operand = YELLOW_2;
      break;
   case Led_Yellow_3:
      port = (uint8_t*) &PORTD;
      operand = YELLOW_3;
      break;
   case Led_Yellow_4:
      port = (uint8_t*) &PORTD;
      operand = YELLOW_4;
      break;
   case Led_Yellow_5:
      port = (uint8_t*) &PORTD;
      operand = YELLOW_5;
      break;
   case Led_Blue_4:
      port = (uint8_t*) &PORTC;
      operand = BLUE_4;
      break;
   case Led_Blue_5:
      port = (uint8_t*) &PORTC;
      operand = BLUE_5;
      break;
   case Led_Blue_6:
      port = (uint8_t*) &PORTC;
      operand = BLUE_6;
      break;
   default:
      return;
   }

   switch (status)
   {
   case LedOff:
      *port |= (1 << operand);
      break;
   case LedOn:
      *port &= ~(1 << operand);
      break;
   case LedToggle:
      *port ^= (1 << operand);
      break;
   }
}

void setLEDBlinking(ledDisplay displayed,
                    uint8_t blinking,
                    uint32_t frequency)
{
   if (displayed < Led_Display_Max_Counter)
   {
      blinkingInformations[displayed].isBlinking = blinking;
      blinkingInformations[displayed].blinkingFrequency = frequency;
   }
}

/*
 * private functions
 */
void clearScreen(void)
{
   PORTA = 0x00;
}

void blinkingHandler(void)
{
   for (int i = 0; i < Led_Display_Max_Counter; ++i)
   {
      if (blinkingInformations[i].isBlinking == 1)
      {
         blinkingInformations[i].blinkingCounter++;

         if (blinkingInformations[i].blinkingCounter >= blinkingInformations[i].blinkingFrequency)
         {
            setLED(i, LedToggle);
            blinkingInformations[i].blinkingCounter = 0;
         }
      }
   }
}

