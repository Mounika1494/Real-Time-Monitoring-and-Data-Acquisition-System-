#include "APDS9103.h"
#include "i2c.h"
#include <math.h>

int file_APDS9301;
char *file = "/dev/i2c-2";

int8_t APDS9301_init()
{
    if(i2c_init(&file_APDS9301,file,APDS9301_ADDR) == fail)
    return FAIL;
    else
    return SUCCESS;
}

int8_t read_light_CH0(float_t *data)
{
    uint16_t read_data = 0;
    if(read_two_byte(&file_APDS9301,CMD_REG|CMD_REG_WORD|LSB_CH0_ADDR, &read_data) == fail)
    //if(read_two_byte(&file_APDS9301,0x80|0x20|0x0C, &data)==fail)
    return FAIL;
    else
    {
        *data = (float_t)read_data;
        return SUCCESS;
    }
}

int8_t read_light_CH1(float_t *data)
{
    uint16_t read_data = 0;
    if(read_two_byte(&file_APDS9301,CMD_REG|CMD_REG_WORD|LSB_CH1_ADDR, &read_data) == fail)
    return FAIL;
    else
    {
        *data = (float_t)read_data;
        return SUCCESS;
    }
}

int8_t APDS9301_poweron()
{
    if(write_one_byte(&file_APDS9301, CMD_REG|CNTL_REG_ADDR , POWER_ON) == fail)
    return FAIL;
    else
    return SUCCESS;
}

int8_t APDS9301_powerof()
{
    /*if(write_one_byte(&file_APDS9301, CMD_REG|CNTL_REG_ADDR , POWER_OFF) == fail)*/
    if(write_one_byte(&file_APDS9301, 0x80|0x00 , 0x03) == fail)
    return FAIL;
    else
    return SUCCESS;
}


int8_t set_thresh_low(uint16_t value)
{
    uint8_t *buf = malloc(sizeof(uint8_t)*3);
    if(buf == NULL)
    return FAIL;
	buf[0]=CMD_REG|CMD_REG_WORD|THRESH_LOW_LSB;
	buf[1]=value & 0xff;
	buf[2]=(value >> 8) & 0xff;

	if(write_two_byte(&file_APDS9301,&buf[0]) == fail)
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

int8_t read_thresh_low(uint16_t *value)
{

	if(read_two_byte(&file_APDS9301, CMD_REG|CMD_REG_WORD|THRESH_LOW_LSB,value) == fail)
	{
	    
	    return FAIL;
	}
	
	else
	{
	    
	    return SUCCESS;
	}
}

int8_t set_thresh_high(uint16_t value)
{
    uint8_t *buf = malloc(sizeof(uint8_t)*3);
    if(buf == NULL)
    return FAIL;
	buf[0]=CMD_REG|CMD_REG_WORD|THRESH_HIGH_LSB;
	buf[1]=value & 0xff;
	buf[2]=(value >> 8) & 0xff;

	if(write_two_byte(&file_APDS9301,&buf[0]) == fail)
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

int8_t read_thresh_high(uint16_t *value)
{

	if(read_two_byte(&file_APDS9301,CMD_REG|CMD_REG_WORD|THRESH_HIGH_LSB,value) == fail)
	{
	    
	    return FAIL;
	}
	
	else
	{
	    
	    return SUCCESS;
	}
}

float_t cal_luminosity(float_t data_CH0,float_t data_CH1)
{
	float ratio = 0;
	float luminousity = 0;
	ratio  =  data_CH1/data_CH0;
	if(ratio>0 && ratio <= 0.5)
	{
		luminousity = (0.0304*data_CH0)-(0.062*data_CH0*pow (ratio, 1.4));
		return luminousity;
	}
	if(ratio>0.5 && ratio <= 0.61)
	{
		return (0.0224*data_CH0) - (0.031*data_CH1);
	}
	if(ratio >0.61 && ratio <=0.80)
	{
		return (0.0128*data_CH0) - (0.0153*data_CH1);
	}
	if(ratio >0.80 && ratio <=1.30)
	{
		return (0.00146*data_CH0) - (0.00112*data_CH1);
	}
	if(ratio >1.30)
	{
		return 0;
	}
}




