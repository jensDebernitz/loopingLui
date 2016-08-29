/*
 * GlobalDefines.h
 *
 *  Created on: 30.07.2014
 *      Author: B�ro Debernitz
 */

#ifndef GLOBALDEFINES_H_
#define GLOBALDEFINES_H_

#include "avr/io.h"

#define OFF       0
#define ON        1
#define TOGGLE    2

#define GAME_MODE_1    0
#define GAME_MODE_2    1
#define GAME_MODE_3    2
#define GAME_MODE_4    3
#define GAME_MODE_5    4
#define GAME_MODE_6    5

#define SPEED_STOP         10
#define SPEED_NORMAL       512
#define SPEED_MAX          1023

#define PIEZO              PB0
#define MOTOR_IN_1         PB6
#define MOTOR_IN_2         PB5
#define MOTOR_ENABLE       PB7

#define RED_1              PC3
#define RED_2              PC4
#define RED_3              PC5
#define RED_4              PC6
#define RED_5              PC7

#define BLUE_1             PD0
#define BLUE_2             PD1
#define BLUE_3             PD2
#define BLUE_4             PC0
#define BLUE_5             PC1
#define BLUE_6             PC2

#define YELLOW_1           PD3
#define YELLOW_2           PD4
#define YELLOW_3           PD5
#define YELLOW_4           PD6
#define YELLOW_5           PD7

#define SWITCH_1           PF1
#define SWITCH_2           PF0

#define LED_SEGMENT_A      0x80
#define LED_SEGMENT_B      0x40
#define LED_SEGMENT_C      0x20
#define LED_SEGMENT_D      0x10
#define LED_SEGMENT_E      0x08
#define LED_SEGMENT_F      0x04
#define LED_SEGMENT_G      0x02
#define LED_SEGMENT_DOT    0x01

#endif /* GLOBALDEFINES_H_ */
