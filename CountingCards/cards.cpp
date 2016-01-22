#include<iostream>
#include<vector>
#include"cards.h"
using namespace std;

Deck::Deck(){
  Top = NULL;
  numOfDecks = 2;
}

Deck::~Deck(){
  while(!isEmpty())//DESTRUCTOR REMOVE UNTIL EMPTY
    RemoveTop();
}

void Deck::displayAll(){
  Card* curr = Top;

  cout<<"[ ";

  while(curr != NULL){
    cout<<curr -> value<<" ";
    curr = curr -> next;
  }

  cout<<"]"<<endl;
}

int Deck::RemoveTop(){//REMOVE TOP CARD OF DECK
  Card* curr = Top;
  int card = 0;

  if(isEmpty()){//IF EMPTY
    cout<<"Deck is Empty"<<endl;
    return -1;
  }
  else if(curr -> next == NULL){//IF ONE CARD IN DECK
    card = curr -> value;
    Top = NULL;
    delete curr;
  }
  else{//IF MORE THAN ONE CARD IN DECK
    card = curr -> value;
    Top = curr -> next;
    delete curr;
  }

  return card;
}

void Deck::push(int Cardvalue){//ADD CARD TO THE TOP OF THE DECK
  Card* curr = Top, *newCard = NULL;
  newCard = new Card();//CREATE NEW CARD
  newCard -> value = Cardvalue;

  if(curr == NULL){//IF DECK IS EMPTY
    newCard -> prev = NULL;
    newCard -> next = NULL;
    Top = newCard;
  }
  else{//IF ONE OR MORE CARDS IN DECK
    curr -> prev = newCard;
    newCard -> next = curr;
    Top = newCard;
  }

}

bool Deck::isEmpty(){//CHECK IF EMPTY
  if(Top == NULL)//TRUE IF EMPTY
    return true;
  else
    return false;
}

bool Deck::isFull(){//CHECK IF FULL
  if(cardsLeft() == 52*numOfDecks)//TRUE IF FULL
    return true;
  else
    return false;
}

int Deck::cardsLeft(){//COUNTS THE CARDS IN THE DECK
  Card* curr = Top;
  int count = 0;

  while(curr != NULL){
    curr = curr -> next;
    count++;
  }

  return count;
}

int Deck::getCard(int position){//GRAB CARD OUT OF DECK
  Card* curr = Top;
  int Cardvalue = 0;

  for(int i = 1; i < position; i++){//GO TO CARD
    curr = curr -> next;
  }

  Cardvalue = curr -> value;//GET CARD VALUE

  if(curr -> next == NULL){//LINK PREVIOUS AND NEXT NODES
    curr -> prev -> next = NULL;
    delete curr;
  }
  else{
    curr -> prev -> next = curr -> next;
    delete curr;
  }

  return Cardvalue;
}

void Deck::shuffle(){//SHUFFLE THE DECK AGAIN, NEED AMOUNT OF DECKS
  int card = 0;
  int unusedCards = 52*numOfDecks;
  vector<int> d;

  while(!isEmpty())//EMPTY DECK
    RemoveTop();

  for(int i = 1; i <= 52*numOfDecks; i++){//ADD NEW CARDS TO DECK
    d.push_back(i);
  }

  while(d.size() != 0){//SHUFFLE
    card = rand() % d.size() + 0;
    push(d[card]);
    d.erase(d.begin() + card);
  }
}
