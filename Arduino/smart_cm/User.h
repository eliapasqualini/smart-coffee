#ifndef _USER_
#define _USER_

#include "MsgService.h"

#define DISTMAX 1.00

class User{

public:

  User();

  bool checkPresence(); 
  bool checkReadyToOrder(); 
  bool checkWaitingCoffee();
  bool checkRefilled(); 
  bool checkMaintenance();
  bool checkGoAway(); 

  void setPresence(bool p); 
  void setReadyToOrder();
  void setWaitingCoffee();
  void setRefilled(); 
  void setMaintenance();
  void setGoAway(); 

  void sendWelcome();
  void sendSugar(String sugar);
  void sendMakingCoffee();
  void sendCoffeeReady();
  void sendNoCoffee();
  void sendRefilled();
  void sendFlush();
  void sendNC(String nc);

  float getCurrentDistance();
  void setCurrentDistance(float distance);
  
private:

  bool presence; 
  bool readyToOrder; 
  bool waitingCoffee; 
  bool maintenance;
  bool refilled; 
  bool goAway;

  float currentDistance;
};

#endif
