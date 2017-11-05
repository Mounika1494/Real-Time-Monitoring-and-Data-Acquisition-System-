#include "system.h"
#include "sequencer.h"
#include "error.h"
#include "led_driver.h"
#include "i2c.h"
#include "APDS9103.h"

#define APDS9301_ADDR 0x39

void *loggerThread(void *threadp)
{

  FILE *fp_data = NULL;
  FILE *fp_logger = NULL;
  int nbytes,prio;
  message_t sensor_recv;
  uint8_t previous_state = 0;

 while(1){
   fp_data = fopen("data.txt", "a");
  if(fp_data == NULL)
  {
    printf("Couldn't log data %d\n",FILE_ERROR);
    exit(-1);
  }
   fp_logger = fopen("logger.txt", "a");
   if(fp_logger == NULL)
   {
     printf("Couldn't log status %d\n",FILE_ERROR);
     exit(-1);
   }
    if((nbytes = mq_receive(log_mq,(char*)&sensor_recv, MAX_MSG_SIZE, &prio)) == ERROR)
    {
      perror("mq_receive");
    }
    else
    {
      if(sensor_recv.sensor == LIGHT){
        
        fprintf(fp_data, "%s Light is %f \n\n", sensor_recv.timestamp,sensor_recv.data.lightData);

      }
      else if (sensor_recv.sensor == TEMPERATURE){

        fprintf(fp_data, "%s Temperature is %f \n\n", sensor_recv.timestamp, sensor_recv.data.temperatureData);

      }
      else if (sensor_recv.type == LOG_FILE) {

        fprintf(fp_logger, "%s %s type: %d \n\n",sensor_recv.timestamp, sensor_recv.data.loggerData,sensor_recv.type);

      }
      
      if (sensor_recv.status == BAD){
        blink_led(10000);
        previous_state =1;
        
        
      }
      if(sensor_recv.status == GOOD)
      {
        if(previous_state == 1)
        {
          previous_state = 0;
          int file_APDS9301;
          char *filename = "/dev/i2c-2";
        
          i2c_init(&file_APDS9301,filename,APDS9301_ADDR);
          write_one_byte(&file_APDS9301, 0x80|0x00 , 0x03);
        }
      }
      

    }
    fclose(fp_data);
    fclose(fp_logger);
}


}
