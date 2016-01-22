#ifndef HAND_H
#define HAND_H
#include"cards.h"

class Hand{
 public:
  Card* firstCard;//FIRST CARD IN HAND
<<<<<<< HEAD
  int playerNumber;//PLAYER NUMBER AT TABLE
  int totalCards;//TOTAL CARDS IN HAND
  bool doubleD;//IF DOUBLE DOWN
  double handCost[4];//HAND COST FOR EACH COUNT VALUE
=======
  int playerNumber;
  int totalCards;
  bool doubleD;//IF DOUBLE DOWN HAND
  double handCost;//AMOUNT BET
>>>>>>> origin/master

  Hand();
  Hand(int player);
  ~Hand();

<<<<<<< HEAD
  void takeCard(int Cardvalue);//GRAB CARD 
  void deleteCards();//DELETE ALL CARDS
  int handTotal();//GET HAND TOTAL
  int getCardValue(int card);//GET CARD VALUE
  void displayCards(int hand);//DISPLAY CARDS
  int deleteFirstCard();//DELETE FIRST CARD
  int handPlay();//GET TYPE OF PLAY
  void doubleDown();//DOUBLE DOWN
  void bet(double betAmount, int);//BET 
=======
  void takeCard(int Cardvalue);
  void deleteCards();
  int handTotal();
  int getCardValue(int card);//1-11
  void displayCards(int hand);
  int deleteFirstCard();
  int handPlay();
  void doubleDown(){handCost*=2;doubleD=true;}//UPDATE BET
  void bet(double betAmount);
>>>>>>> origin/master
};

#endif
