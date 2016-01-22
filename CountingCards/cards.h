#ifndef CARDS_H
#define CARDS_H

<<<<<<< HEAD
struct Card{//INDIVIDUAL CARD
=======
struct Card{//NODE CARD
>>>>>>> origin/master
  int value;
  Card* next;
  Card* prev;
};

class Deck{//LINKED LIST DECK
 public:
<<<<<<< HEAD
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
=======
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
>>>>>>> origin/master
};

#endif