#include "system.h"
#include "sequencer.h"
#include <sys/time.h>
#include "TMP102.h"
#include "datetime_service.h"

//Temperature thread which interacts with TMP102.c driver and logs into logger.txt any error and data into data.txt 
void *temperatureThread(void *threadp)
{

  int nbytes,prio;
  message_t sensor_recv;
  float_t data;
  TMP102_init();
  //change to write_2_byte
  if(1){
    sprintf(sensor_recv.data.loggerData,"%s","DEBUG INFO: Temperature sensor initialization success\n"); 
    sensor_recv.status = GOOD; 
  }else{
    sprintf(sensor_recv.data.loggerData,"%s","DEBUG ERROR: Temperature sensor initialization failed\n");
    sensor_recv.status = BAD;
  }

  sprintf(sensor_recv.timestamp,"%s",getDateString());
  sensor_recv.type = LOG_FILE;
  if((nbytes = mq_send(log_mq, (char *)&sensor_recv, sizeof(sensor_recv), 30)) == ERROR)
  {
    perror("mq_send");
  }
  else
  {
    printf("Light: init for log file: %d bytes: message successfully sent\n", nbytes);
  }
  
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
        
        if (wakeup_power_save_mode()==FAIL){

          sprintf(sensor_recv.data.loggerData,"%s","DEBUG ERROR:Temperature sensor read failed\n"); 
          sensor_recv.status = BAD; 
          sprintf(sensor_recv.timestamp,"%s",getDateString());
          sensor_recv.type = LOG_FILE;
          if((nbytes = mq_send(log_mq, (char *)&sensor_recv, sizeof(sensor_recv), 30)) == ERROR)
          {
            perror("mq_send");
          }
          else
          {
            printf("Temerature: init for log file: %d bytes: message successfully sent\n", nbytes);
          }  
      }
        
        read_temperature(&data);
        if(data > 25)
        {
         sensor_recv.type = QUERY_QUEUE; 
         if((nbytes = mq_send(light_mq, (char *)&sensor_recv, sizeof(sensor_recv), 30)) == ERROR)
           {
             perror("mq_send");
           }
           else
           {
             printf("2_T. temp thread sending proc q: %d bytes: message successfully sent\n", nbytes);
           }
        }
        else
        {
          sensor_recv.sensor = TEMPERATURE;
          sprintf(sensor_recv.timestamp,"%s",getDateString());
          sensor_recv.status = GOOD;
          sensor_recv.data.temperatureData = data;
          if((nbytes = mq_send(proc_mq, (char *)&sensor_recv, sizeof(sensor_recv), 30)) == ERROR)
           {
             perror("mq_send");
           }
           else
           {
             printf("2_T. temp thread sending proc q: %d bytes: message successfully sent\n", nbytes);
           }
         }
         enter_power_save_mode();
      }
      else if(sensor_recv.type == QUERY_QUEUE)
      {
          if (wakeup_power_save_mode()==FAIL){

          sprintf(sensor_recv.data.loggerData,"%s","DEBUG ERROR:Temperature sensor read failed\n"); 
          sensor_recv.status = BAD; 
          sprintf(sensor_recv.timestamp,"%s",getDateString());
          sensor_recv.type = LOG_FILE;
          if((nbytes = mq_send(log_mq, (char *)&sensor_recv, sizeof(sensor_recv), 30)) == ERROR)
          {
            perror("mq_send");
          }
          else
          {
            printf("Temerature: init for log file: %d bytes: message successfully sent\n", nbytes);
          }  
        }
        sensor_recv.type = QUERY_QUEUE;
        read_temperature(&data);
        sensor_recv.sensor = TEMPERATURE;
        sprintf(sensor_recv.timestamp,"%s",getDateString());
        sensor_recv.status = GOOD;
        sensor_recv.data.temperatureData = data;
        if((nbytes = mq_send(log_mq, (char *)&sensor_recv, sizeof(sensor_recv), 30)) == ERROR)
          {
             perror("mq_send");
          }
          else
          {
             printf("2_T. temp thread sending proc q: %d bytes: message successfully sent\n", nbytes);
          }
        
          enter_power_save_mode();
      }

    }

  }

}
