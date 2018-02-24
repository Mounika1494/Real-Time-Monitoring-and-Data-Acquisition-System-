#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>
#include <stdbool.h>
#include "../inc/APDS9103.h"
#include "../inc/i2c.h"

/***********************************************************************************
*@Filename:test_APDS9301.c
*
*@Description: Test cases using cmocka to test the boundary conditions for TMP102 driver
*pass null values
*
*@Author:Mounika Reddy Edula
*        Jay Krishnan
*@Date: 09/19/2017
*@Test Framework: CMocka
*************************************************************************************/

//#define TEMPERATURE_REG 0x00

void test_APDS9301_init(void **state)
{
    int return_value;
    return_value = APDS9301_init();
    assert_int_equal(return_value,SUCCESS);
}

void test_read_light_CH0(void **state)
{
    int return_value;
    return_value = APDS9301_init();
    assert_int_equal(return_value,SUCCESS);
    return_value = APDS9301_poweron();
    assert_int_equal(return_value,SUCCESS);
    float_t data;
    return_value = read_light_CH0(&data);
    assert_int_equal(return_value,SUCCESS);
}

void test_APDS9301_poweron(void **state)
{
    int return_value;
    return_value = APDS9301_init();
    assert_int_equal(return_value,SUCCESS);
    return_value = APDS9301_poweron();
    assert_int_equal(return_value,SUCCESS);
}

void test_APDS9301_powerof(void **state)
{
    uint16_t data;
    int return_value;
    return_value = APDS9301_init();
    assert_int_equal(return_value,SUCCESS);
    return_value = APDS9301_powerof();
    assert_int_equal(return_value,SUCCESS);
}

void test_set_thresh_low(void **state)
{
    uint16_t data;
    int return_value;
    return_value = APDS9301_init();
    assert_int_equal(return_value,SUCCESS);
    return_value = APDS9301_poweron();
    assert_int_equal(return_value,SUCCESS);
    return_value = set_thresh_low(0x0005);
    assert_int_equal(return_value,SUCCESS);
}

void test_set_THIGH(void **state)
{
    uint16_t data;
    int return_value;
    return_value = APDS9301_init();
     assert_int_equal(return_value,SUCCESS);
    return_value = APDS9301_poweron();
    assert_int_equal(return_value,SUCCESS);
    return_value = set_thresh_high(0x0020);
    assert_int_equal(return_value,SUCCESS);
}

int main(int argc,char **argv)
{
const struct CMUnitTest test[] = {
       cmocka_unit_test(test_APDS9301_init),
       cmocka_unit_test(test_read_light_CH0),
       cmocka_unit_test(test_APDS9301_poweron),
       cmocka_unit_test(test_set_thresh_low),
       cmocka_unit_test(test_set_THIGH),
       cmocka_unit_test(test_APDS9301_powerof)
       };

return cmocka_run_group_tests(test,NULL,NULL);
}

