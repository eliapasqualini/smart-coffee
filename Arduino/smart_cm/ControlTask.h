#include "Task.h"
#include "User.h"
#include "Sonar.h"
#include "Button.h"
#include "Pot.h"

class ControlTask: public Task {
public:
  ControlTask(User* cUser);
  void init(int period);
  void tick();

private:
  User* cUser;
  Sonar* sonar;
  Button* button;
  Pot* pot;

  //variabili
  int presenceTime;
  int sugarLevel;

  enum{IDLE, READY, START} state;
};
