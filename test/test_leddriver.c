#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>
#include <stdbool.h>
#include "../inc/led_driver.h"

/***********************************************************************************
*@Filename:test_leddriver.c
*
*@Description: Test cases using cmocka to test the boundary conditions for leddriver driver
*pass null values
*
*@Author:Mounika Reddy Edula 
*        Jay Krishnan
*@Date: 09/19/2017
*@Test Framework: CMocka
*************************************************************************************/
void test_blink_led(void **state)
{
    int return_value;
    return_value = blink_led(1000);
    assert_int_equal(return_value,BLINK);
    return_value = blink_led(0);
    assert_int_equal(return_value,ERROR_L);
}

int main(int argc,char **argv)
{
const struct CMUnitTest test[] = {
       cmocka_unit_test(test_blink_led)
       };

return cmocka_run_group_tests(test,NULL,NULL);
}