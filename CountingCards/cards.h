#ifndef CARDS_H
#define CARDS_H

struct Card{//INDIVIDUAL CARD
  int value;
  Card* next;
  Card* prev;
};

class Deck{//LINKED LIST DECK
 public:
  Card* Top;//TOP OF THE DECK
  int numOfDecks;//NUMBER OF DECKS
  int cardsLeftinDeck;//CARDS LEFT

  Deck();
  ~Deck();
  int RemoveTop();//REMOVES FIRST CARD FROM DECK
  void push(int Cardvalue);//ADDS CARD TO DECK
  bool isEmpty();//CHECKS IF EMPTY
  int cardsLeft();//AMOUNT OF CARDS LEFT IN DECK
  void shuffle();//SHUFFLES THE DECK(S)
  bool isFull();//CHECKS IF FULL
  int getCard(int Cardvalue);//GRABS A CARD FROM THE DECK
  void displayAll();//DISPLAYS ALL CARDS IN DECK
};

#endif