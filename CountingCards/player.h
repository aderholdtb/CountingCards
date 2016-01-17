#ifndef PLAYER_H
#define PLAYER_H
#include"hand.h"

const int maxHand = 10;

class Player{
 public:
  Hand hands[maxHand];//HANDS
  int handCount;//AMOUNT OF HANDS
  int playerNumber;
  double chips;//AMOUNT OF CHIPS

  Player();
  ~Player();

  bool playType(int, int&, bool&);//PLAY TYPE
  void split(int);//SPLIT HAND
};

#endif
