#include "ControlTask.h"
#include "MsgService.h"
#include "SonarImpl.h"
#include "ButtonImpl.h"
#include "PotImpl.h"

#define ECHO_PIN 7
#define TRIG_PIN 8
#define BTN_PIN 3
#define POT_PIN A0
#define DIST1 0.3
#define DT2 5000

ControlTask::ControlTask(User* cUser){
  this->cUser = cUser;
  sonar = new SonarImpl(ECHO_PIN,TRIG_PIN);
  button = new ButtonImpl(BTN_PIN);
  pot = new PotImpl(POT_PIN);
}

void ControlTask::init(int period){
  Task::init(period);
  state = IDLE;
}

void ControlTask::tick(){
  switch(state){
    case IDLE:{
      if(cUser->checkReadyToOrder()){
        state = READY;
        presenceTime = 0;
        sugarLevel = map(pot->getValue(),0,1023,0,5);
        cUser->sendSugar(String(sugarLevel));
      }
      break;

    }
    case READY:{
      //caso in cui non rilevi più nessuno per un certo tempo DT2
      cUser->setCurrentDistance(sonar->getDistance());
      if(cUser->getCurrentDistance() > DIST1){
        presenceTime += myPeriod;
        if(presenceTime >= DT2){
          cUser->setGoAway();
          state = IDLE;
          break;
        }
      } else {
        presenceTime = 0;
      }
      
      if(sugarLevel != map(pot->getValue(),0,1023,0,5)){
        sugarLevel = map(pot->getValue(),0,1023,0,5);
        cUser->sendSugar(String(sugarLevel));
      }
      
      //se premo il bottone cambio stato
      if(button->isPressed()){
        state = START;
        cUser->setWaitingCoffee();
      }
      break;

    }
    case START:{
      //controllo se c'è stato il refill, in caso torno ad idle
      if(cUser->checkMaintenance()){
        state = IDLE;
        break;
      }
      //se non bisogna fare il refill torno in ready
      if(cUser->checkReadyToOrder()){
        state = READY;
        break;
      }
      break;      
    }
  }
}
