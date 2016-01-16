#ifndef CARDS_H
#define CARDS_H

struct Card{
  int value;
  Card* next;
  Card* prev;
};

class Deck{
 public:
  Card* Top;
  int numOfDecks;
  int cardsLeftinDeck;

  Deck();
  ~Deck();
  int RemoveTop();
  void push(int Cardvalue);
  bool isEmpty();
  int cardsLeft();
  void shuffle();
  bool isFull();
  int getCard(int Cardvalue);
  void displayAll();
};

#endif
