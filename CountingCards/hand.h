#ifndef HAND_H
#define HAND_H
#include"cards.h"

class Hand{
 public:
  Card* firstCard;
  int playerNumber;
  int totalCards;
  bool doubleD;
  double handCost;

  Hand();
  Hand(int player);
  ~Hand();

  void takeCard(int Cardvalue);
  void deleteCards();
  int handTotal();
  int getCardValue(int card);
  void displayCards(int hand);
  int deleteFirstCard();
  int handPlay();
  void doubleDown(){handCost*=2;doubleD=true;}
  void bet(double betAmount);
};

#endif
