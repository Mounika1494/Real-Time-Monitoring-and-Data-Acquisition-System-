/**********************************************************************************************************
* Copyright (C) 2017 by Mounika Reddy Edula
*
*Redistribution,modification or use of this software in source or binary fors is permitted as long 
*as the files maintain this copyright.Mounika Reddy Edula is not liable for any misuse of this material
*
*********************************************************************************************************/
/**
* @file TMP102.h
* @brief driver to setup the sensor
*
*This header file provides functions to initialise i2c,write one byte,read one byte,read two byte
*
* @author Mounika Reddy Edula
* @       Jay Krishnan
* @date September 11/4/2017
* @version 1.0
*
*/
#ifndef _TMP102_H
#define _TMP102_H

#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "i2c.h"

#define TEMPERATURE_REG 0x00
#define CONFIG_REG 0x01
#define THRESH_LOW 0x02
#define THRESH_HIGH 0x03
#define TMP102_ADDR 0x48
#define RESOLUTION 0.0625

//enum for status of each driver function
enum return_t{
  SUCCESS = 0,
  FAIL = -1
};


/***
* @brief Initialises the sensor APDS9301
*
*
*@param NONE
*
*@return int8_t fail - any error in connecting to the device
*               success - successfull initialisation
*/
extern int8_t TMP102_init();

/***
* @brief read temperature from TEMP_REG
*
*
*@param pointer to store data
*
*@return int8_t fail - any error in connecting to the device
*               success - successfull initialisation
*/
extern int8_t read_temperature(float_t *data);

/***
* @brief enter into SD mode with CONF_REG
*
*
*@param NONE
*
*@return int8_t fail - any error in connecting to the device
*               success - writing successfull 
*/
extern int8_t enter_power_save_mode();

/***
* @brief wake up from SD mode for reading temperature
*
*
*@param NONE
*
*@return int8_t fail - any error in connecting to the device
*               success - writing successfull 
*/
extern int8_t wakeup_power_save_mode();

/***
* @brief convert into F
*
*
*@param temperature in C
*
*@return temperature in F
* 
*/
extern float_t temperature_F(float_t data);

/***
* @brief convert into K
*
*
*@param temperature in C
*
*@return temperature in K
* 
*/
extern float_t temperature_K(float_t data);

/***
* @brief Set threshold low register for interrupt
*
*
*@param value to be written to register
* 
*@return int8_t fail - any error in connecting to the device
*               success - successfull initialisation
*/
extern int8_t set_TLOW(uint16_t value);

/***
* @brief Set threshold high register for interrupt
*
*
*@param value to be written to register
* 
*@return int8_t fail - any error in connecting to the device
*               success - successfull initialisation
*/
extern int8_t set_THIGH(uint16_t value);
#endif