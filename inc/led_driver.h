/**********************************************************************************************************
* Copyright (C) 2017 by Mounika Reddy Edula
*
*Redistribution,modification or use of this software in source or binary fors is permitted as long 
*as the files maintain this copyright.Mounika Reddy Edula is not liable for any misuse of this material
*
*********************************************************************************************************/
/**
* @file i2c.h
* @brief I2C service function to talk to driver
*
*This header file provides functions to initialise i2c,write one byte,read one byte,read two byte
*
* @author Mounika Reddy Edula
* @       Jay Krishnan
* @date September 11/4/2017
* @version 1.0
*
*/
#ifndef LED_DRIVER_H
#define LED_DRIVER_H

typedef enum{
  BLINK = 1,
  ERROR
}return_type_t;
/***
* @brief read threshold high register for interrupt
*
*
*@param value to be written to register
* 
*@return int8_t ERROR - any error in connecting to the device
*               BLINK - successfull initialisation
*/
extern uint8_t blink_led(uint16_t period);

#endif