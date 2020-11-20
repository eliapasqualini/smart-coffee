#include "CoffeeTask.h"
#include "MsgService.h"
#include "SonarImpl.h"
#include "Led.h"

#define ECHO_PIN 7
#define TRIG_PIN 8
#define LED1_PIN 13
#define LED2_PIN 12
#define LED3_PIN 11
#define DT3 3000
#define DT4 5000
#define DIST2 0.1
#define NC 5

CoffeeTask::CoffeeTask(User* cUser){
  this->cUser = cUser;
  sonar = new SonarImpl(ECHO_PIN,TRIG_PIN);
  led1 = new Led(LED1_PIN);
  led1->switchOff();
  led2 = new Led(LED2_PIN);
  led2->switchOff();
  led3 = new Led(LED3_PIN);
  led3->switchOff();

}

void CoffeeTask::init(int period){
  Task::init(period);
  state = IDLE;
}

void CoffeeTask::tick(){
  switch(state){
    case IDLE:{
      if(cUser->checkWaitingCoffee()){
        cUser->sendMakingCoffee();
        state = COFFEE;
        NMAX--;
      }
     break;
    }
    case COFFEE:{
      delay(DT3/3);
      led1->switchOn();
      delay(DT3/3);
      led2->switchOn();
      delay(DT3/3);
      led3->switchOn();
      cUser->sendCoffeeReady();
      state = DONE;
      coffeeTakingTime = 0;
      break;
    }
    case DONE:{
      coffeeTakingTime += myPeriod;
      cUser->setCurrentDistance(sonar->getDistance());
      if (DT4 <= coffeeTakingTime){
        cUser->sendFlush();
        state = TAKEN;
        break;
      } else if( cUser->getCurrentDistance() <= DIST2){
          cUser->sendFlush();
          state = TAKEN;
          break;
        }
      break; 
    }
    case TAKEN:{
      led1->switchOff();
      led2->switchOff();
      led3->switchOff();
      
      if (NMAX > 0){
          state = IDLE;
          cUser->setReadyToOrder();
          break;
        } else {
            state = MAINTENANCE;
            cUser->sendNoCoffee();
        }
        
        break;
    }
    case MAINTENANCE:{
      //aspetto il messaggio di ricarica per poter cambiare stato
      if(MsgService.isMsgAvailable()){
        Msg* msg = MsgService.receiveMsg(); 
        const String& content = msg->getContent();
        if (content == "R"){
        state = IDLE;
        cUser->sendNC(String(NC));
        cUser->setRefilled();
        cUser->setMaintenance();
        cUser->sendRefilled();
        NMAX += NC;
        }
      }
      break;
      
    }
  }
}
