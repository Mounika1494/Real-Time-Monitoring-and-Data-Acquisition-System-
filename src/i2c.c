#include "i2c.h"
#include <pthread.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>


static pthread_mutex_t i2c_mutex = PTHREAD_MUTEX_INITIALIZER;

int8_t i2c_init(int *fileHandle, char *filename, uint8_t slaveAddress){

  //char *filename = "/dev/i2c-2";
  pthread_mutex_lock(&i2c_mutex);
  if ((*fileHandle = open(filename, O_RDWR)) < 0) {

      perror("Failed to open the i2c bus");
      return FAIL;
  }

  //int addr = 0b0111001;          // The I2C address of the ADC
  if (ioctl(*fileHandle, I2C_SLAVE, slaveAddress) < 0) {

      printf("Failed to acquire bus access and/or talk to slave.\n");
      return FAIL;
  }
  else{
      printf("connected successfully\n");
  }
  pthread_mutex_unlock(&i2c_mutex);
  pthread_mutex_destroy(&i2c_mutex);

  return SUCCESS;
}


int8_t write_one_byte(int *fileHandle, uint8_t reg, uint8_t data){

    //uint8_t command_byte = (0x80|reg );// command|no idea|register address
  pthread_mutex_lock(&i2c_mutex);
  if (write(*fileHandle, &reg, 1) != 1) {
  	perror("Write error: ");
    return FAIL;
  }
  if (write(*fileHandle, &data, 1) != 1) {
	perror("Write error:");
  return FAIL;
  }
  pthread_mutex_unlock(&i2c_mutex);
  pthread_mutex_destroy(&i2c_mutex);
  return SUCCESS;

}


int8_t read_one_byte(int *fileHandle, uint8_t reg, uint8_t *data){

    //uint8_t command_byte = (0x80|reg );//commandbyte|reg address
  pthread_mutex_lock(&i2c_mutex);
  if (write(*fileHandle, &reg, 1) != 1) {
		perror("Write error:");
    return FAIL;
	}
	if (read(*fileHandle, data, 1) != 1) {
		perror("Read error:");
    return FAIL;
	}
	//printf("reg val is: %d\n", *data );
  pthread_mutex_unlock(&i2c_mutex);
  pthread_mutex_destroy(&i2c_mutex);
  return SUCCESS;
}


int8_t read_two_byte(int *fileHandle, uint8_t reg, uint16_t *data){

  //  uint8_t command_byte = (0x80|0x20|reg );//commandbyte|reg address
  pthread_mutex_lock(&i2c_mutex);
  if (write(*fileHandle, &reg, 1) != 1) {
		perror("Write error:");
    return FAIL;
	}
	if (read(*fileHandle, data, 2) != 2) {
		perror("Read error:");
    return FAIL;
	}
	//printf("reg val is: %d\n", *data );
  pthread_mutex_unlock(&i2c_mutex);
  pthread_mutex_destroy(&i2c_mutex);
  return SUCCESS;
}
