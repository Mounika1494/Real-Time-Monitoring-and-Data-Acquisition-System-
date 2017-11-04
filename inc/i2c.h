#ifndef _I2C_H
#define _I2C_H

#include <stdint.h>

enum return_code{
  SUCCESS = 0,
  FAIL = -1
};

extern int8_t i2c_init(int *fileHandle, char *filename, uint8_t slaveAddress);

extern int8_t write_one_byte(int *file, uint8_t reg, uint8_t data);

extern int8_t read_one_byte(int *file, uint8_t reg, uint8_t *data);

extern int8_t read_two_byte(int *file, uint8_t reg, uint16_t *data);

#endif