#include<stdio.h>
#include <unistd.h>
#include <stdint.h>
#include "../inc/led_driver.h"

//blink led with frequency given
uint8_t blink_led(uint16_t period){
	FILE* LED = NULL;
	if(period == 0)
	return ERROR_L;
	const char *LEDBright = "/sys/class/leds/beaglebone:green:usr0/brightness";
    int i =0;
    for(i=0;i<2;i++){
	if((LED = fopen(LEDBright,"r+")) !=NULL){
		fwrite("1",sizeof(char),1,LED);
		fclose(LED);
	}
	else
	return ERROR_L;
 	usleep(period);
 	if((LED = fopen(LEDBright,"r+")) != NULL){
 		fwrite("0",sizeof(char),1,LED);
 		fclose(LED);
 		}
 	else
 	return ERROR_L;
	}
	return BLINK;
}