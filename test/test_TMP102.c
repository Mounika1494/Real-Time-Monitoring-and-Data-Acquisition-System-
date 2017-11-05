#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>
#include <stdbool.h>
#include "../inc/TMP102.h"
#include "../inc/i2c.h"

/***********************************************************************************
*@Filename:test_circbuffer.c
*
*@Description: Test cases using cmocka to test the boundary conditions for circular buffer
*pass null pointers, loop back,removing elements,destroy
*
*@Author:Mounika Reddy Edula
*@Date: 09/19/2017
*@Test Framework: CMocka
*************************************************************************************/

//#define TEMPERATURE_REG 0x00
/*Test the add_item functionality of circular buffer*/
void test_TMP102_init(void **state)
{
    int return_value;
    return_value = TMP102_init();
    assert_int_equal(return_value,SUCCESS);
}

void test_read_temperature(void **state)
{
    uint16_t data;
    int return_value;
    return_value = TMP102_init();
    assert_int_equal(return_value,SUCCESS);
    read_temperature(&data);
    assert_int_equal(return_value,SUCCESS);
}

void test_enter_power_save_mode(void **state)
{
    uint16_t data;
    int return_value;
    return_value = TMP102_init();
    assert_int_equal(return_value,SUCCESS);
    return_value = enter_power_save_mode();
    assert_int_equal(return_value,SUCCESS);
}

void test_wakeup_power_save_mode(void **state)
{
    uint16_t data;
    int return_value;
    return_value = TMP102_init();
    assert_int_equal(return_value,SUCCESS);
    return_value = wakeup_power_save_mode();
    assert_int_equal(return_value,SUCCESS);
}

void test_set_TLOW(void **state)
{
    uint16_t data;
    int return_value;
    return_value = TMP102_init();
    assert_int_equal(return_value,SUCCESS);
    return_value = set_TLOW(0x0005);
    assert_int_equal(return_value,SUCCESS);
}

void test_set_THIGH(void **state)
{
    uint16_t data;
    int return_value;
    return_value = TMP102_init();
    assert_int_equal(return_value,SUCCESS);
    return_value = set_THIGH(0x0020);
    assert_int_equal(return_value,SUCCESS);
}

int main(int argc,char **argv)
{
const struct CMUnitTest test[] = {
       cmocka_unit_test(test_TMP102_init),
       cmocka_unit_test(test_read_temperature),
       cmocka_unit_test(test_set_THIGH),
       cmocka_unit_test(test_set_TLOW),
       cmocka_unit_test(test_wakeup_power_save_mode),
       cmocka_unit_test(test_enter_power_save_mode),
       };

return cmocka_run_group_tests(test,NULL,NULL);
}

