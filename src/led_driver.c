#include<stdio.h>
#include <unistd.h>
#include <stdint.h>

uint8_t blink_led(char* state){
	FILE* LEDHandle = NULL;
	const char *LEDBrightness = "/sys/class/leds/beaglebone:green:usr0/brightness";
    int i =0;
    //while(1){
    //for(i=0;i<2;i++){
	if((LEDHandle = fopen(LEDBrightness,"r+")) !=NULL){
		fwrite(state,sizeof(char),1,LEDHandle);
		fclose(LEDHandle);
	}
// 	usleep(1000);
// 	if((LEDHandle = fopen(LEDBrightness,"r+")) != NULL){
// 		fwrite("0",sizeof(char),1,LEDHandle);
// 		fclose(LEDHandle);
// 		}
//	}
//    }
	return 0;
}