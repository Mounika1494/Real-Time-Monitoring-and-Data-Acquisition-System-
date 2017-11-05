/**********************************************************************************************************
* Copyright (C) 2017 by Mounika Reddy Edula
*
*Redistribution,modification or use of this software in source or binary fors is permitted as long 
*as the files maintain this copyright.Mounika Reddy Edula is not liable for any misuse of this material
*
*********************************************************************************************************/
/**
* @file APDS9103.h
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
#ifndef LIGHT_SENSOR_H
#define LIGHT_SENSOR_H

#include <stdint.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

//enum for status of each driver function
enum return_t{
  SUCCESS = 0,
  FAIL = -1
};

//register address
#define APDS9301_ADDR 0x39

//ADC channel address
#define LSB_CH0_ADDR 0x0C
#define USB_CH0_ADDR 0x0D
#define LSB_CH1_ADDR 0x0E
#define USB_CH1_ADDR 0x0F

//Command byte
#define CMD_REG             0x80
#define CMD_REG_WORD        0x20

//control registers
#define CNTL_REG_ADDR    0x00
#define POWER_ON      0x03
#define POWER_OFF     0x00

//Threshold registers
#define THRESH_LOW_LSB   0x02
#define THRESH_LOW_MSB  0x03
#define THRESH_HIGH_LSB   0x04
#define THRESH_HIGH_MSB  0x05


/***
* @brief Initialises the sensor APDS9301
*
*
*@param NONE
*
*@return int8_t fail - any error in connecting to the device
*               success - successfull initialisation
*/
extern int8_t APDS9301_init();



/***
* @brief read ADC values from Channel 0
*
*
*@param pointer to store data
*
*@return int8_t fail - any error in connecting to the device
*               success - successfull initialisation
*/
extern int8_t read_light_CH0(float_t *data);


/***
* @brief read ADC values from Channel 1
*
*
*@param pointer to store data
*
*@return int8_t fail - any error in connecting to the device
*               success - successfull initialisation
*/
extern int8_t read_light_CH1(float_t *data);

/***
* @brief power on the sensor with control register
*
*
*@param NONE
*
*@return int8_t fail - any error in connecting to the device
*               success - successfull initialisation
*/
extern int8_t APDS9301_poweron();


/***
* @brief power off the sensor with control register
*
*
*@param NONE
*
*@return int8_t fail - any error in connecting to the device
*               success - successfull initialisation
*/
extern int8_t APDS9301_powerof();

/***
* @brief Set threshold low register for interrupt
*
*
*@param value to be written to register
* 
*@return int8_t fail - any error in connecting to the device
*               success - successfull initialisation
*/
extern int8_t set_thresh_low(uint16_t value);

/***
* @brief Set threshold high register for interrupt
*
*
*@param value to be written to register
* 
*@return int8_t fail - any error in connecting to the device
*               success - successfull initialisation
*/
extern int8_t set_thresh_high(uint16_t value);


/***
* @brief read threshold low register for interrupt
*
*
*@param value to be written to register
* 
*@return int8_t fail - any error in connecting to the device
*               success - successfull initialisation
*/
extern int8_t read_thresh_low(uint16_t* value);


/***
* @brief read threshold high register for interrupt
*
*
*@param value to be written to register
* 
*@return int8_t fail - any error in connecting to the device
*               success - successfull initialisation
*/
extern int8_t read_thresh_high(uint16_t* value);

/***
* @brief calculate luminosity based on ADC channel readings
*
*
*@param data_CH0 - ADC_CH0(reading)
*       data_CH1 - ADC_CH1(reading)
*
*@return int8_t fail - any error in connecting to the device
*               success - successfull initialisation
*/
extern float_t cal_luminosity(float_t data_CH0,float_t data_CH1);

#endif