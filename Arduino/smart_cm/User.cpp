#include "User.h"

#define MSG_WELCOME "W"
#define MSG_MAKING_COFFEE "M"
#define MSG_COFFEE_READY "C"
#define MSG_NO_COFFEE "N"
#define MSG_REFILLED "R"
#define MSG_FLUSH "F"
#define MSG_NC "A"
#define MSG_SUGAR "S"

User::User(){

  presence = false;
  readyToOrder = false;
  waitingCoffee = false;
  refilled = false;
  maintenance = false;
  goAway = false;

  currentDistance = DISTMAX + 1;
}

void User::setCurrentDistance(float d){
  currentDistance = d;
}

float User::getCurrentDistance(){
  return currentDistance;
}

bool User::checkPresence(){
  return presence;
}

bool User::checkReadyToOrder(){
  bool isReadyToOrder = readyToOrder;
  readyToOrder = false;
  return isReadyToOrder;
}

bool User::checkRefilled(){
  bool isRefilled = refilled;
  refilled = false;
  return isRefilled;
}

bool User::checkMaintenance(){
  bool isMaintenance = maintenance;
  maintenance = false;
  return isMaintenance;
}

bool User::checkGoAway(){
  bool isGoAway = goAway;
  goAway = false;
  return isGoAway;
}

bool User::checkWaitingCoffee(){
  bool isWaitingCoffee = waitingCoffee;
  waitingCoffee = false;
  return isWaitingCoffee;
}

void User::setRefilled(){
  refilled = true;
}

void User::setMaintenance(){
  maintenance = true;
}

void User::setPresence(bool p){
  presence = p;
}

void User::setReadyToOrder(){
  readyToOrder = true;
}

void User::setGoAway(){
  goAway = true;
}

void User::setWaitingCoffee(){
  waitingCoffee = true;
}

void User::sendWelcome(){
  MsgService.sendMsg(MSG_WELCOME);
}

void User::sendMakingCoffee(){
  MsgService.sendMsg(MSG_MAKING_COFFEE);
}

void User::sendCoffeeReady(){
  MsgService.sendMsg(MSG_COFFEE_READY);
}

void User::sendNoCoffee(){
  MsgService.sendMsg(MSG_NO_COFFEE);
}

void User::sendRefilled(){
  MsgService.sendMsg(MSG_REFILLED);
}

void User::sendFlush(){
  MsgService.sendMsg(MSG_FLUSH);
}

void User::sendSugar(String sugar){
  MsgService.sendMsg(MSG_SUGAR+sugar);
}

void User::sendNC(String nc){
  MsgService.sendMsg(MSG_NC+nc);
}

