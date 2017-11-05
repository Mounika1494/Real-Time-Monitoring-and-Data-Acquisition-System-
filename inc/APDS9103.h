#ifndef LIGHT_SENSOR_H
#define LIGHT_SENSOR_H

#include <stdint.h>

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
#define CMD_REG_WORD        0xA0

#define CONTROL_REG_ADDR    0x00
#define POWER_ON      0x03
#define POWER_OFF     0x00

#define ID_REG_ADDR      0x0A 

#define THRESH_LOW_LSB   0x02
#define THRESH_LOW_MSB  0x03


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
extern int8_t read_light(float_t *data);
#endif