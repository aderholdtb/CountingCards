#ifndef HAND_H
#define HAND_H
#include"cards.h"

class Hand{
 public:
  Card* firstCard;//FIRST CARD IN HAND
  int playerNumber;//PLAYER NUMBER AT TABLE
  int totalCards;//TOTAL CARDS IN HAND
  bool doubleD;//IF DOUBLE DOWN
  double handCost[4];//HAND COST FOR EACH COUNT VALUE

  Hand();
  Hand(int player);
  ~Hand();

  void takeCard(int Cardvalue);//GRAB CARD 
  void deleteCards();//DELETE ALL CARDS
  int handTotal();//GET HAND TOTAL
  int getCardValue(int card);//GET CARD VALUE
  void displayCards(int hand);//DISPLAY CARDS
  int deleteFirstCard();//DELETE FIRST CARD
  int handPlay();//GET TYPE OF PLAY
  void doubleDown();//DOUBLE DOWN
  void bet(double betAmount, int);//BET 
};

#endif
