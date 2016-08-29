/*
 * LL_Timer.h
 *
 *  Created on: 30.07.2014
 *      Author: B�ro Debernitz
 */

#ifndef LL_TIMER_H_
#define LL_TIMER_H_

#include "stdint.h"

typedef enum
{
   PWM_Channel_1A = 0,
   PWM_Channel_1B,

   PWM_Channel_Enum_Counter
}pwmChannel;


/*!
 * \brief init the Timer
 */
void initTimer(void);

/**
 * \brief return the current Timer Tick
 *
 * \return current timer tick
 */
uint8_t getTimerTick10mSec(void);

/**
 * \brief return the different from the tick to current tick
 *
 * \return timer diff value
 */
uint8_t getTimerDiff10mSec(uint8_t timerTick);

/**
 * \brief return the current Timer Tick
 *
 * \return current timer tick
 */
uint8_t getTimerTick1Sec(void);

/**
 * \brief return the different from the tick to current tick
 *
 * \return timer diff value
 */
uint8_t getTimerDiff1Sec(uint8_t timerTick);

/**
 * \brief enable Timer Interrupt
 */
void enableTimer0Interrupt(void);

/**
 * @brief setter for the PWM
 *
 * @param channel
 * @param duty
 */
void setPWMOutput(pwmChannel channel, uint16_t duty);

/**
 * \brief setter for the function Pointer list in the 10Msec Timer
 *
 * @param fp
 * @return
 */
uint8_t setFunctionPointerTimer0(void (*fp)(void));
#endif /* LL_TIMER_H_ */
