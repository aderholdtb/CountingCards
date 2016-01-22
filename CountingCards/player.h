#ifndef PLAYER_H
#define PLAYER_H
#include"hand.h"

const int maxHand = 10;

class Player{
 public:
<<<<<<< HEAD
  Hand hands[maxHand];//TOTAL HANDS
  int handCount;//NUMBER OF HANDS
  int playerNumber;//PLAYER NUMBER AT TABLE
  double chips[4];//CHIPS FOR EVERY COUNT
=======
  Hand hands[maxHand];//HANDS
  int handCount;//AMOUNT OF HANDS
  int playerNumber;
  double chips;//AMOUNT OF CHIPS
>>>>>>> origin/master

  Player();
  ~Player();

<<<<<<< HEAD
  bool playType(int, int&, bool&);//GET PLAY TYPE FOR CARDS IN HAND
  void split(int);//SPLIT CARDS
  void makeBet(double count, int type, int decks);//MAKE A BET
=======
  bool playType(int, int&, bool&);//PLAY TYPE
  void split(int);//SPLIT HAND
>>>>>>> origin/master
};

#endif