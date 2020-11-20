#include "Task.h"
#include "User.h"
#include "Sonar.h"
#include "Led.h"

class CoffeeTask: public Task {
public:
  CoffeeTask(User* cUser);
  void init(int period);
  void tick();

private:
  User* cUser;
  Sonar* sonar;
  Light* led1;
  Light* led2;
  Light* led3;

  int coffeeTakingTime;
  int NMAX = 3;


  enum{IDLE, COFFEE, DONE, TAKEN, MAINTENANCE} state;
};
