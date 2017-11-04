#include "system.h"
#include "APDS9103.h"
#include "sequencer.h"
#include <sys/time.h>


#ifdef POSIX_QUEUE
  #include <mqueue.h>
#else
  #include <message_service.h>
#endif

void *lightThread(void *threadp)
{
  int nbytes,prio;
  struct timeval tv;
  message_t sensor_recv;
  int file;
  uint8_t data;
  uint16_t data2;
  char *filename = "/dev/i2c-2";
  i2c_init(&file, filename, SLAVE);
  write_one_byte(&file, 0x80|0x00 , 0x03);

  while(1){
    printf("\n waiting on light_mq \n");
    if((nbytes = mq_receive(light_mq, (char*)&sensor_recv, MAX_MSG_SIZE, &prio)) == ERROR)
    {
      perror("mq_receive");
    }
    else
    {

      printf("light receive: msg %d received with priority = %d, length = %d\n",
             sensor_recv.type, prio, nbytes);
      if(sensor_recv.type == PROCESS_QUEUE) {
        // memset(&sensor_recv,0,sizeof(sensor_recv));
        read_two_byte(&file,0x80|0x20|0x0C, &data2 );
        gettimeofday(&tv,NULL);
        sensor_recv.sensor = LIGHT;
        sensor_recv.timestamp = tv.tv_sec;
        sensor_recv.status = GOOD;
        sensor_recv.data.lightData = (float_t)data2;
        printf("***************************\n lightdata: %f timestamp %lu\n",sensor_recv.data.lightData,sensor_recv.timestamp );
        if((nbytes = mq_send(proc_mq, (char *)&sensor_recv, sizeof(sensor_recv), 30)) == ERROR)
       // if((nbytes = mq_send(temp_mq, proc_msg, 13, 30)) == ERROR)
         {
           perror("mq_send");
         }
         else
         {
           printf("2_L. light thread sending proc q: %d bytes: message successfully sent\n", nbytes);
         }
      }


    }


 }

}
