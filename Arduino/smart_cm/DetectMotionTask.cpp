#include "DetectMotionTask.h"
#include "PirImpl.h"
#include "MsgService.h"
#include "SonarImpl.h"
#include <avr/sleep.h>
#include <avr/sleep.h>

#define PIR_PIN 2
#define ECHO_PIN 7
#define TRIG_PIN 8
#define DIST1 0.3
#define DT1 1000


DetectMotionTask::DetectMotionTask(User* cUser){
  this->cUser = cUser;
  pir = new PirImpl(PIR_PIN);
  sonar = new SonarImpl(ECHO_PIN,TRIG_PIN);
}

void DetectMotionTask::init(int period){
  Task::init(period);
  state = STANDBY;
}

void DetectMotionTask::tick(){
  switch(state){
    case STANDBY:{
      if(pir->isDetected()){
        cUser->setPresence(true);
      }
      if(cUser->checkPresence()){
        state = ON;
        arrivalTime = 0;
      } else if(!pir->isDetected()){
        sleep();
      }
      break;
    }
    case ON:{
      arrivalTime += myPeriod;
      cUser->setCurrentDistance(sonar->getDistance());
      cUser->setPresence(pir->isDetected());
      if(cUser->checkPresence()){
        if (cUser->getCurrentDistance() <= DIST1){
          if (arrivalTime >= DT1){
            state = WELCOME;
            cUser->sendWelcome();
            cUser->setReadyToOrder();
          } else {
            break;
          }
        } else {
          state = STANDBY;
          cUser->sendFlush();
        }
      } else {
        state = STANDBY;
        cUser->sendFlush();
      }
      break;
    }
    case WELCOME:{
      //permette di passare allo stato di standby dopo aver effettuato il refill
      if(cUser->checkRefilled()){
        state = STANDBY;
        break;

      }
      //permette di passare allo stato di on dopo che sono trascorsi DT2 secondi senza rilevare presenza nello stato di ready
      if(cUser->checkGoAway()){
        state = ON;
        break;
      }
      break;
    }
  }
}

void interruptHandler(){}

void DetectMotionTask::sleep(){
  delay(50);   
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable(); 
  attachInterrupt(digitalPinToInterrupt(PIR_PIN), interruptHandler, RISING);
  sleep_mode();
  detachInterrupt(digitalPinToInterrupt(PIR_PIN)); 
  sleep_disable(); 
  power_all_enable();  
}
