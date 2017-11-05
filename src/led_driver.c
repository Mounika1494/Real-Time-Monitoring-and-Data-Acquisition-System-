#include<stdio.h>
#include <unistd.h>
#include <stdint.h>

//blink led with frequency given
uint8_t blink_led(uint16_t period){
	FILE* LEDHandle = NULL;
	const char *LEDBrightness = "/sys/class/leds/beaglebone:green:usr0/brightness";
    int i =0;
    for(i=0;i<2;i++){
	if((LEDHandle = fopen(LEDBrightness,"r+")) !=NULL){
		fwrite("1",sizeof(char),1,LEDHandle);
		fclose(LEDHandle);
	}
	else
	return ERROR;
 	usleep(period);
 	if((LEDHandle = fopen(LEDBrightness,"r+")) != NULL){
 		fwrite("0",sizeof(char),1,LEDHandle);
 		fclose(LEDHandle);
 		}
 	else
 	return ERROR;
	}
	return BLINK;
}