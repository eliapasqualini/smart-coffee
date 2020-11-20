#include "Task.h"
#include "User.h"
#include "Pir.h"
#include "Sonar.h"
#include "Timer.h"

class DetectMotionTask: public Task {

public:

  DetectMotionTask(User* cUser);
  void init(int period);
  void tick();

private:
  void sleep();
  User* cUser;
  Pir* pir;
  Sonar* sonar;

  int arrivalTime;

  enum{STANDBY, ON, WELCOME} state;
};

