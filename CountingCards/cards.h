#ifndef CARDS_H
#define CARDS_H

struct Card{//NODE CARD
  int value;
  Card* next;
  Card* prev;
};

class Deck{
 public:
  Card* Top;//TOP OF THE DECK------>COULD HAVE MADE PRIVATE VARIABLE
  int numOfDecks;
  int cardsLeftinDeck;

  Deck();
  ~Deck();
  int RemoveTop();//POP TOP OF THE DECK
  void push(int Cardvalue);//ADD CARD TO THE DECK
  bool isEmpty();
  int cardsLeft();
  void shuffle();//SHUFFLE THE CARDS IN THE DECK
  bool isFull();
  int getCard(int Cardvalue);
  void displayAll();
};

#endif
