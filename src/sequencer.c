#include "system.h"
#include "sequencer.h"

static int i = 0;


void sighler (union sigval val){
  //printf("Handler entered with value :%d for %d times\n", val.sival_int, ++i);
  static int count;
  ++count;

  switch(count){
    case 1:
      sem_post(&lightSem);
      break;
    case 2:
      sem_post(&tempSem);
      count = 0;
      break;
    default:
      break;

  }

}

void *sequencerThread(void *threadp){


  // create 2 timers (http://devlib.symbian.slions.net/s3/GUID-B4039418-6499-555D-AC24-9B49161299F2.html)
  // 2 signals and 2 signal handlers

  printf("\n sequencer thread \n");

  int Ret;
  printf("\n in timer \n");

  pthread_attr_t attr;
  pthread_attr_init( &attr );

  struct sched_param parm;
  parm.sched_priority = 50;
  pthread_attr_setschedparam(&attr, &parm);

  struct sigevent sig;
  sig.sigev_notify = SIGEV_THREAD;
  sig.sigev_notify_function = sighler;
  sig.sigev_value.sival_int =20;
  sig.sigev_notify_attributes = &attr;

  //create a new timer.
  timer_t timerid;
  Ret = timer_create(CLOCK_REALTIME, &sig, &timerid);
  if (Ret == 0)
      {
      struct itimerspec in, out;
      in.it_value.tv_sec = 2;
      in.it_value.tv_nsec = 0;
      in.it_interval.tv_sec = 0;
      in.it_interval.tv_nsec = 100000000;
      //issue the periodic timer request here.
      Ret = timer_settime(timerid, 0, &in, &out);
      if(Ret == 0)
          sleep(8);
      else
          printf("timer_settime() failed with %d\n", errno);
      //delete the timer.
      timer_delete(timerid);
      }
  else
  printf("timer_create() failed with %d\n", errno);

}
