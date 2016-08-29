/*
 * LL_Motor.c
 *
 *  Created on: 01.08.2014
 *      Author: B�ro Debernitz
 */

#include <stdlib.h>
#include "avr/io.h"

#include "Misc/GlobalDefines.h"
#include "Timer/LL_Timer.h"

#include "Motor/LL_Motor.h"

pwmChannel forwardChannel;
uint16_t currentSpeed;

void initEngine(void)
{
   setDirection(forwards);
   setSpeed(SPEED_STOP);
}

void setSpeed(uint16_t speed)
{
   if (speed > SPEED_MAX)
   {
      speed = SPEED_MAX;
   }
   currentSpeed = speed;
   setPWMOutput(forwardChannel, currentSpeed);
}

void setDirection(movingDirection direction)
{
   if (forwards == direction)
   {
      forwardChannel = PWM_Channel_1A;
      setPWMOutput(PWM_Channel_1B, SPEED_STOP);
   }
   else if (backwards == direction)
   {
      forwardChannel = PWM_Channel_1B;
      setPWMOutput(PWM_Channel_1A, SPEED_STOP);
   }
   else
   {
      // no more directions
   }
   setPWMOutput(forwardChannel, currentSpeed);
}
