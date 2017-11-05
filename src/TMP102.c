
#include "i2c.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include "TMP102.h"

int file_TMP102;
char *filename = "/dev/i2c-2";

//TMP102 initialsation
int8_t TMP102_init()
{
    if(i2c_init(&file_TMP102,filename,TMP102_ADDR) == fail)
    return FAIL;
    else
    return SUCCESS;
}

//read temperature from temp_reg
int8_t read_temperature(float_t *data)
{
    uint16_t read_data = 0;
    uint16_t digital_temp = 0;
    if(read_two_byte(&file_TMP102,TEMPERATURE_REG,&read_data) == fail)
    return FAIL;
    else
    {
    	 digital_temp = ((uint8_t)read_data<<4| read_data>>12);
    	 if(digital_temp > 0x7FF)
	     {
            digital_temp |= 0xF000;
         }
        *data = (float_t)(digital_temp*RESOLUTION);
         return SUCCESS;
    }
   
}

//enter into SD mode by writing to CONF_REG
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

//wakeup from SD mode to read temperature
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

//Convert to Faranheit
float_t temperature_F(float_t data)
{
	data = (data)*9.0/5.0 + 32.0;
	return data;
}

//Convert to Kelvin
float_t temperature_K(float_t data)
{
	data = (data)+273;
	return data;
}

//Set TLOW for interrupt
int8_t set_TLOW(uint16_t value){
	
	uint8_t *buf = malloc(sizeof(uint8_t)*3);
    if(buf == NULL)
    return FAIL;
	buf[0]= THRESH_LOW;
	buf[2]= (value >> 8) & 0xff; 
	buf[1]= value & 0xff;
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

//set THIGH for interrupt
int8_t set_THIGH(uint16_t value){
	
	uint8_t *buf = malloc(sizeof(uint8_t)*3);
    if(buf == NULL)
    return FAIL;
	buf[0]= THRESH_HIGH;
	buf[2]= (value >> 8) & 0xff; 
	buf[1]= value & 0xff;
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

