#include "Scheduler.h"
#include "User.h"
#include "MsgService.h"
#include "DetectMotionTask.h"
#include "ControlTask.h"
#include "CoffeeTask.h"


Scheduler sched;


void setup() {
  sched.init(100);
  MsgService.init();
  User* cUser = new User();
  DetectMotionTask* cDetectMotion = new DetectMotionTask(cUser);
  ControlTask* cControlTask = new ControlTask(cUser);
  CoffeeTask* mCoffeeTask = new CoffeeTask(cUser);
  cDetectMotion->init(100);
  cControlTask->init(100);
  mCoffeeTask->init(100);
  sched.addTask(cDetectMotion);
  sched.addTask(cControlTask);
  sched.addTask(mCoffeeTask);
  
 
}

void loop() {
  sched.run();

}
