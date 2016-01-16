#ifndef PLAYER_H
#define PLAYER_H
#include"hand.h"

const int maxHand = 10;

class Player{
 public:
  Hand hands[maxHand];
  int handCount;
  int playerNumber;
  double chips;

  Player();
  ~Player();

  bool playType(int, int&, bool&);
  void split(int);
};

#endif
