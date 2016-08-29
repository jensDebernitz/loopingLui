/*
 * LL_Motor.h
 *
 *  Created on: 01.08.2014
 *      Author: B�ro Debernitz
 */

#ifndef LL_MOTOR_H_
#define LL_MOTOR_H_

#include <stdint.h>

typedef enum
{
   forwards,
   backwards
} movingDirection;

/**
 * Init engine setup
 */
void initEngine(void);

/**
 * set engine speed
 * @param speed to set
 */
void setSpeed(uint16_t speed);

/**
 * set engine direction
 * @param direction direction to set
 */
void setDirection(movingDirection direction);

#endif /* LL_MOTOR_H_ */
