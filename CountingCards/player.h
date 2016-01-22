#ifndef PLAYER_H
#define PLAYER_H
#include"hand.h"

const int maxHand = 10;

class Player{
 public:
  Hand hands[maxHand];//TOTAL HANDS
  int handCount;//NUMBER OF HANDS
  int playerNumber;//PLAYER NUMBER AT TABLE
  double chips[4];//CHIPS FOR EVERY COUNT

  Player();
  ~Player();

  bool playType(int, int&, bool&);//GET PLAY TYPE FOR CARDS IN HAND
  void split(int);//SPLIT CARDS
  void makeBet(double count, int type, int decks);//MAKE A BET
};

#endif