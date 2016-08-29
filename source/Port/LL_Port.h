/*
 * LL_Port.h
 *
 *  Created on: 28.04.2015
 *      Author: jdebernitz
 */

#ifndef SOURCE_PORT_LL_PORT_H_
#define SOURCE_PORT_LL_PORT_H_

typedef enum
{
   Pressed_Switch_1_One_Seconds,
   Pressed_Switch_2_One_Seconds,
   Pressed_Switch_1_Three_Seconds,
   Pressed_Switch_2_Three_Seconds,
   Pressed_Switch_Both_One_Seconds,
   Pressed_Switch_Both_Three_Seconds,

   Function_Pointer_Options_Enum_Count
}functionPointerType;

/**
 * @brief init the ports
 */
void initPorts(void);

/**
 * @brief is switch Pressed
 *
 * @param hardwareSwitch
 * @return
 */
uint8_t isSwitchPressed(uint8_t hardwareSwitch);

/**
 * @brief setter for the function pointer
 *
 * @param type
 * @param fp
 *
 * @return
 */
uint8_t setFunctionPointerSwitch(functionPointerType type, void (*fp)(void));

#endif /* SOURCE_PORT_LL_PORT_H_ */
