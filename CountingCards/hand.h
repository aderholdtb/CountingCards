#ifndef HAND_H
#define HAND_H
#include"cards.h"

class Hand{
 public:
  Card* firstCard;//FIRST CARD IN HAND
  int playerNumber;
  int totalCards;
  bool doubleD;//IF DOUBLE DOWN HAND
  double handCost;//AMOUNT BET

  Hand();
  Hand(int player);
  ~Hand();

  void takeCard(int Cardvalue);
  void deleteCards();
  int handTotal();
  int getCardValue(int card);//1-11
  void displayCards(int hand);
  int deleteFirstCard();
  int handPlay();
  void doubleDown(){handCost*=2;doubleD=true;}//UPDATE BET
  void bet(double betAmount);
};

#endif
