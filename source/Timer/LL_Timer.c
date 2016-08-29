/*
 * LL_Timer.c
 *
 *  Created on: 30.07.2014
 *      Author: B�ro Debernitz
 */

#include <stdint.h>
#include <stdio.h>

#include "avr/io.h"
#include "avr/interrupt.h"

#include "Timer/LL_Timer.h"

#define TIMER_0_ENTRYCOUNT     3

//TypeDef for the PointerList
typedef void (*functionPointerTimer)(void);
static functionPointerTimer FunctionPointerList0[TIMER_0_ENTRYCOUNT];
// semaphore to avoid interrupt overrun
static volatile unsigned int semaphoreCallFunctionPointerList[] =
{
  0 };

//State for the Set FunctionPointer List
static unsigned char functionPointerCount[] =
{
  0 };

//FunctionPointer List
static functionPointerTimer *FunctionPointerList[] =
{
  FunctionPointerList0 };

static const unsigned char maxfunctionPointerCount[] =
{
  TIMER_0_ENTRYCOUNT };

volatile static uint8_t timerTick10mSec;
volatile static uint8_t timerTick10mSecHelper;
volatile static uint8_t timerTick1Sec;

static const uint16_t MAX_PWM_VALUE = 0x3FF;

void timer0_init(void);
void PWM_init(void);
static void callFunctionPointerList(uint8_t);
static uint8_t addFunctionPointer(uint8_t tidx,
                                  functionPointerTimer fp);

/*
 * Interrupts
 */
ISR( TIMER0_OVF_vect)
{
   TCNT0 = 0xB2;

   timerTick10mSec++;
   timerTick10mSecHelper++;

   if (timerTick10mSecHelper >= 100)
   {
      timerTick1Sec++;
      timerTick10mSecHelper = 0;
   }

   callFunctionPointerList(0);

}

/*
 * publics functions
 */
void initTimer(void)
{
   //init the second timer with 10mSec
   timer0_init();

   PWM_init();
}

uint8_t getTimerTick10mSec(void)
{

   return timerTick10mSec;
}

uint8_t getTimerDiff10mSec(uint8_t timerTick)
{

   uint16_t helpTick = timerTick10mSec;

   if (helpTick < timerTick)
   {
      helpTick = timerTick10mSec + 255;
   }

   return (uint8_t) helpTick - timerTick;
}

uint8_t getTimerTick1Sec(void)
{

   return timerTick1Sec;
}

uint8_t getTimerDiff1Sec(uint8_t timerTick)
{

   uint16_t helpTick = timerTick1Sec;

   if (helpTick < timerTick)
   {
      helpTick = timerTick1Sec + 255;
   }

   return (uint8_t) helpTick - timerTick;
}

void enableTimer0Interrupt(void)
{
   TIMSK |= 0x01;
}

void setPWMOutput(pwmChannel channel, uint16_t duty)
{

   if(duty > MAX_PWM_VALUE)
   {
      duty = MAX_PWM_VALUE;
   }

   if (channel < PWM_Channel_Enum_Counter)
   {
      switch (channel)
      {
      case PWM_Channel_1A:
         OCR1A = duty;
         break;
      case PWM_Channel_1B:
         OCR1B = duty;
         break;
      default:
         break;
      }
   }
}

/*
 * private functions
 */

//TIMER0 initialize - prescale:1024
// WGM: CTC
// desired value: 10mSec
// actual value: 10,112mSec (-1,1%)
void timer0_init(void)
{
   TCCR0 = 0x00; //stop
   ASSR = 0x00; //set async mode
   TCNT0 = 0xB2; //set count
   OCR0 = 0x4E;
   TCCR0 = 0x07; //start timer
}

void PWM_init(void)
{
   TCCR1A = 0b10101011;
   TCCR1B = 0b00001010;
   OCR1AH = 0x03;
   OCR1AL = 0xFF;
   OCR1BH = 0x03;
   OCR1BL = 0xFF;
   OCR1CH = 0x03;
   OCR1CL = 0xFF;

}

static void callFunctionPointerList(uint8_t idx)
{
   uint8_t currentCount = 0;
   if (semaphoreCallFunctionPointerList[idx] == 0)
   {
      semaphoreCallFunctionPointerList[idx] = 1; // take semaphore
      currentCount = functionPointerCount[idx];
   }
   else
   {
      return;
   }
   unsigned char i = 0;
   while (i < currentCount)
   {
      //Call the void Functions from the List
      FunctionPointerList[idx][i]();
      i++;
   }
   semaphoreCallFunctionPointerList[idx] = 0; // release semaphore
   return;
}

static uint8_t addFunctionPointer(uint8_t tidx,
                                  functionPointerTimer fp)
{
   uint8_t oldCount = functionPointerCount[tidx];
   FunctionPointerList[tidx][oldCount] = fp;
   functionPointerCount[tidx] = oldCount + 1;

   return 0;
}

//Set void Function in the FuncionPoinerList0
uint8_t setFunctionPointerTimer0(void (*fp)(void))
{
   if ((fp == NULL) || (functionPointerCount[0] == maxfunctionPointerCount[0]))
   {
      return 1;
   }
   return addFunctionPointer(0, fp);
}

