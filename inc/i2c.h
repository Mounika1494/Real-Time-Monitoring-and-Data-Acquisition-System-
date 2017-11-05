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
#ifndef _I2C_H
#define _I2C_H

#include <stdint.h>

//enum for status of each driver function
enum return_code{
  success = 0,
  fail = -1
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
extern int8_t i2c_init(int *fileHandle, char *filename, uint8_t slaveAddress);


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
extern int8_t write_one_byte(int *file, uint8_t reg, uint8_t data);

/***
* @brief Reading one byte of data from given address
*
*
*@param file - file handle for communication to the respective slave
*       reg - Address of the Register
*       byte - pointer to data read
*
*@return int8_t fail - any error in connecting to the device
*               success - writing successfull 
*/
extern int8_t read_one_byte(int *file, uint8_t reg, uint8_t *data);

/***
* @brief Reading two byte of data from given address
*
*
*@param file - file handle for communication to the respective slave
*       reg - Address of the Register
*       byte - pointer to data read
*
*@return int8_t fail - any error in connecting to the device
*               success - writing successfull 
*/
extern int8_t read_two_byte(int *file, uint8_t reg, uint16_t *data);

extern int8_t write_two_byte(int *file,uint8_t* data);

#endif
