
#include "i2c.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include "TMP102.h"

int file_TMP102;
char *filename = "/dev/i2c-2";

int8_t TMP102_init()
{
    if(i2c_init(&file_TMP102,filename,TMP102_ADDR) == fail)
    return FAIL;
    else
    return SUCCESS;
}

int8_t read_temperature(float_t *data)
{
    uint16_t read_data = 0;
    if(read_two_byte(&file_TMP102,TEMPERATURE_REG,&read_data) == fail)
    return FAIL;
    else
    {
        *data = (float_t)(((uint8_t)read_data<<4| read_data>>12)*RESOLUTION);
         return SUCCESS;
    }
   
}

int8_t enter_power_save_mode()
{
    uint8_t *buf = malloc(sizeof(uint8_t)*3);
    if(buf == NULL)
    return FAIL;
	buf[0]=CONFIG_REG;
	buf[2]=0b10100000;
	buf[1]=0b01100001;
	
	if(write_two_byte(&file_TMP102,&buf[0]) == fail)
	{
	    free(buf);
	    return FAIL;
	}
	
	else
	{
	    free(buf);
	    return SUCCESS;
	}
	
}


int8_t wakeup_power_save_mode()
{
    uint8_t *buf = malloc(sizeof(uint8_t)*3);
    if(buf == NULL)
    return FAIL;
	buf[0]=CONFIG_REG;
	buf[2]=0b10100000;
	buf[1]=0b01100000;
	
	if(write_two_byte(&file_TMP102,&buf[0]) == fail)
	{
	    free(buf);
	    return FAIL;
	}
	
	else
	{
	    free(buf);
	    return SUCCESS;
	}
	
}

