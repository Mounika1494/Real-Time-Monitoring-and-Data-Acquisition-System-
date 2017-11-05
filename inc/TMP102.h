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
* @brief Initialises the i2c driver for a slave address
*
*
*@param fileHandle - file handle for that slave used for rest communication
*       filename -   pointer for the specific i2c-2/i2c-1
*       slaveAddress - address of the slave you want to communicate
*
*@return int8_t fail - any error in connecting to the device
*               success - successfull initialisation
*/
extern int8_t TMP102_init();

/***
* @brief Writing one byte of data to the given address
*
*
*@param file - file handle for communication to the respective slave
*       reg - Address of the Register
*       byte - data you want to write
*
*@return int8_t fail - any error in connecting to the device
*               success - writing successfull 
*/
extern int8_t read_temperature(float_t *data);

/***
* @brief Writing one byte of data to the given address
*
*
*@param file - file handle for communication to the respective slave
*       reg - Address of the Register
*       byte - data you want to write
*
*@return int8_t fail - any error in connecting to the device
*               success - writing successfull 
*/
extern int8_t enter_power_save_mode();

/***
* @brief Writing one byte of data to the given address
*
*
*@param file - file handle for communication to the respective slave
*       reg - Address of the Register
*       byte - data you want to write
*
*@return int8_t fail - any error in connecting to the device
*               success - writing successfull 
*/
extern int8_t wakeup_power_save_mode();

/***
* @brief Writing one byte of data to the given address
*
*
*@param file - file handle for communication to the respective slave
*       reg - Address of the Register
*       byte - data you want to write
*
*@return int8_t fail - any error in connecting to the device
*               success - writing successfull 
*/
extern float_t temperature_F(float_t data);

/***
* @brief Writing one byte of data to the given address
*
*
*@param file - file handle for communication to the respective slave
*       reg - Address of the Register
*       byte - data you want to write
*
*@return int8_t fail - any error in connecting to the device
*               success - writing successfull 
*/
extern float_t temperature_K(float_t data);

/***
* @brief Writing one byte of data to the given address
*
*
*@param file - file handle for communication to the respective slave
*       reg - Address of the Register
*       byte - data you want to write
*
*@return int8_t fail - any error in connecting to the device
*               success - writing successfull 
*/
extern int8_t set_TLOW(uint16_t value);

/***
* @brief Writing one byte of data to the given address
*
*
*@param file - file handle for communication to the respective slave
*       reg - Address of the Register
*       byte - data you want to write
*
*@return int8_t fail - any error in connecting to the device
*               success - writing successfull 
*/
extern int8_t set_THIGH(uint16_t value);
#endif