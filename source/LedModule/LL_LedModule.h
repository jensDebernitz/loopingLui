/*
 * LL_LedModule.h
 *
 *  Created on: 01.08.2014
 *      Author: B�ro Debernitz
 */

#ifndef LL_LEDMODULE_H_
#define LL_LEDMODULE_H_

#include <stdint.h>

typedef enum
{
   Dot,
   No_Dot
} segmentDisplayDot;

typedef enum
{
	Figure_Zero = 0,
	Figure_One,
	Figure_Two,
	Figure_Three,
	Figure_Four,
	Figure_Five,
	Figure_Six,
	Figure_Seven,
	Figure_Eight,
	Figure_Nine,
	Figure_A,
	Figure_B,
	Figure_C,
	Figure_D,
	Figure_E,
   Figure_F,
} segmentDisplay;

typedef enum
{
   Led_Red_1 = 0,
   Led_Red_2,
   Led_Red_3,
   Led_Red_4,
   Led_Red_5,

   Led_Blue_1,
   Led_Blue_2,
   Led_Blue_3,

   Led_Yellow_1,
   Led_Yellow_2,
   Led_Yellow_3,
   Led_Yellow_4,
   Led_Yellow_5,

   Led_Blue_4,
   Led_Blue_5,
   Led_Blue_6,

   Led_Display_Max_Counter
}ledDisplay;


typedef enum
{
   LedOn = 0,
   LedOff,
   LedToggle
}ledStatus;

/**
 * @brief init the led Module
 */
void initSegmentDisplay(void);

/**
 * @brief setter for the seven segment display
 *
 * @param figure
 * @param dotPoint
 */
void setSegementDisplay(segmentDisplay figure);

/**
 * @brief setter for the Led
 *
 * @param displayed
 * @param status
 */
void setLED(ledDisplay displayed, ledStatus status);

void setLEDBlinking(ledDisplay displayed, uint8_t blinking, uint32_t frequency);

#endif /* LL_LEDMODULE_H_ */
