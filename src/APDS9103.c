
#include "i2c.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include "APDS9103.h"

int file_APDS9301;
char *file = "/dev/i2c-2";

int8_t APDS9301_init()
{
    if(i2c_init(&file_APDS9301,file,APDS9301_ADDR) == fail)
    return FAIL;
    else
    return SUCCESS;
}

int8_t read_light(float_t *data)
{
    uint16_t read_data = 0;
    if(read_two_byte(&file_APDS9301,0x80|0x20|0x0C, &read_data) == fail)
    return FAIL;
    else
    return SUCCESS;
}


