#include "system.h"
#include "sequencer.h"
#include <sys/time.h>
#include "TMP102.h"

void *temperatureThread(void *threadp)
{

  int nbytes,prio;
  message_t sensor_recv;
  struct timeval tv;
  int file_TMP102;
  char *filename = "/dev/i2c-2";
  uint16_t data = 0;
  i2c_init(&file_TMP102,filename,TMP102_ADDR);
 while(1){

    printf("Waiting for temp_mq\n");
    if((nbytes = mq_receive(temp_mq, (char *)&sensor_recv, MAX_MSG_SIZE, &prio)) == ERROR)
    {
      perror("mq_receive");
    }
    else
    {

      printf("temp receive: msg %d received with priority = %d, length = %d\n",
           sensor_recv.type, prio, nbytes);
           
      if(sensor_recv.type == PROCESS_QUEUE){
        read_two_byte(&file_TMP102,TEMPERATURE_REG,&data);
        
        gettimeofday(&tv,NULL);
        sensor_recv.sensor = TEMPERATURE;
        sensor_recv.timestamp = tv.tv_sec;
        sensor_recv.status = GOOD;
        sensor_recv.data.temperatureData = ((uint8_t)data<<4| data>>12)*0.0625;

        if((nbytes = mq_send(proc_mq, (char *)&sensor_recv, sizeof(sensor_recv), 30)) == ERROR)
       // if((nbytes = mq_send(temp_mq, proc_msg, 13, 30)) == ERROR)
         {
           perror("mq_send");
         }
         else
         {
           printf("2_T. temp thread sending proc q: %d bytes: message successfully sent\n", nbytes);
         }

      }

    }

  }

}
