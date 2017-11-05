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
#define APDS9301_ADDR 0x39


#define LSB_CH0_ADDR 0x0C
#define USB_CH0_ADDR 0x0D
#define LSB_CH1_ADDR 0x0E
#define USB_CH1_ADDR 0x0F


#define CMD_REG             0x80
#define CMD_REG_WORD        0x20

#define CNTL_REG_ADDR    0x00
#define POWER_ON      0x03
#define POWER_OFF     0x00

#define ID_REG_ADDR      0x0A 

#define THRESH_LOW_LSB   0x02
#define THRESH_LOW_MSB  0x03
#define THRESH_HIGH_LSB   0x04
#define THRESH_HIGH_MSB  0x05



#define IC_REG_ADDR  0x06
#define IEN_MASK 0x10
#define NO_OF_CYCLES_MASK 0x0F



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
extern int8_t APDS9301_init();



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
extern int8_t read_light_CH0(float_t *data);

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
extern int8_t read_light_CH1(float_t *data);

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
extern int8_t APDS9301_poweron();


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
extern int8_t APDS9301_powerof();

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
extern int8_t set_thresh_low(uint16_t value);

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
extern int8_t set_thresh_high(uint16_t value);


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
extern int8_t read_thresh_low(uint16_t* value);


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
extern int8_t read_thresh_high(uint16_t* value);

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
extern float_t cal_luminosity(float_t data_CH0,float_t data_CH1);

#endif