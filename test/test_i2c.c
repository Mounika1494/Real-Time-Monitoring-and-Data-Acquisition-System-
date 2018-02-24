#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>
#include <stdbool.h>
#include "../inc/i2c.h"
#include "../inc/TMP102.h"

/***********************************************************************************
*@Filename:test_i2c.c
*
*@Description: Test cases using cmocka to test the boundary conditions for i2c driver
*pass null pointers, wrong slave address
*
*@Author:Mounika Reddy Edula
*        Jay Krishanan
*@Date: 09/19/2017
*@Test Framework: CMocka
*************************************************************************************/

//#define TEMPERATURE_REG 0x00
/*Test the add_item functionality of circular buffer*/
void test_i2c_init(void **state)
{
    int file;
    char *filename = "/dev/i2c-2";
    int return_value;
    int slaveAddress = 0x48;
    return_value = i2c_init(&file,filename,slaveAddress);
    assert_int_equal(return_value,success);
    slaveAddress = 0x01;
    return_value = i2c_init(&file,filename,slaveAddress);
    assert_int_equal(return_value,success);
}

void test_read_two_byte(void **state)
{
    int file;
    char *filename = "/dev/i2c-2";
    int return_value;
    int slaveAddress = 0x48;
    uint16_t data = 0;
    i2c_init(&file,filename,slaveAddress);
    return_value = read_two_byte(&file,TEMPERATURE_REG,&data);
    assert_int_equal(return_value,success);
    file = 0;//NULL Value
    return_value = read_two_byte(&file,TEMPERATURE_REG,&data);
    assert_int_equal(return_value,fail);   
}

void test_read_one_byte(void **state)
{
    int file;
    char *filename = "/dev/i2c-2";
    int return_value;
    int slaveAddress = 0x48;
    uint8_t data = 0;
    i2c_init(&file,filename,slaveAddress);
    return_value = read_one_byte(&file,TEMPERATURE_REG,&data);
    assert_int_equal(return_value,success);
    file = 0;//NULL Value
    return_value = read_one_byte(&file,TEMPERATURE_REG,&data);
    assert_int_equal(return_value,fail);   
}

void test_write_two_byte(void **state)
{
    int file;
    char *filename = "/dev/i2c-2";
    int return_value;
    uint16_t value = 0x0050;
    int slaveAddress = 0x48;
    uint8_t *buf = malloc(sizeof(uint8_t)*3);
    i2c_init(&file,filename,slaveAddress);
    buf[0]= THRESH_HIGH;
	buf[2]= (value >> 8) & 0xff; 
	buf[1]= value & 0xff;
	return_value = write_two_byte(&file,&buf[0]);
    assert_int_equal(return_value,success);
    file = 0;//NULL Value
    return_value = write_two_byte(&file,&buf[0]);
    assert_int_equal(return_value,fail);  
    return_value = write_two_byte(&file,NULL);
    assert_int_equal(return_value,fail); 
    free(buf);
}

void test_write_one_byte(void **state)
{
    int file;
    char *filename = "/dev/i2c-2";
    int return_value;
    int slaveAddress = 0x48;
    uint8_t data = 0;
    i2c_init(&file,filename,slaveAddress);
    return_value = write_one_byte(&file,TEMPERATURE_REG,data);
    assert_int_equal(return_value,success);
    file = 0;//NULL Value
    return_value = write_one_byte(&file,TEMPERATURE_REG,data);
    assert_int_equal(return_value,fail);
}

int main(int argc,char **argv)
{
const struct CMUnitTest test[] = {
       cmocka_unit_test(test_i2c_init),
       cmocka_unit_test(test_read_two_byte),
       cmocka_unit_test(test_read_one_byte),
       cmocka_unit_test(test_write_two_byte),
       cmocka_unit_test(test_write_one_byte)
       };

return cmocka_run_group_tests(test,NULL,NULL);
}

