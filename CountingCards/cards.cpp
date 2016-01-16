#include<iostream>
#include<vector>
#include"cards.h"
using namespace std;


Deck::Deck(){
  Top = NULL;
  numOfDecks = 8;
}

Deck::~Deck(){
  while(!isEmpty())
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

int Deck::RemoveTop(){
  Card* curr = Top;
  int card = 0;

  if(isEmpty()){
    cout<<"Deck is Empty"<<endl;
    return -1;
  }
  else if(curr -> next == NULL){
    card = curr -> value;
    Top = NULL;
    delete curr;
  }
  else{
    card = curr -> value;
    Top = curr -> next;
    delete curr;
  }

  return card;
}

void Deck::push(int Cardvalue){
  Card* curr = Top, *newCard = NULL;
  newCard = new Card();
  newCard -> value = Cardvalue;

  if(curr == NULL){
    newCard -> prev = NULL;
    newCard -> next = NULL;
    Top = newCard;
  }
  else{
    curr -> prev = newCard;
    newCard -> next = curr;
    Top = newCard;
  }

}

bool Deck::isEmpty(){
  if(Top == NULL)
    return true;
  else
    return false;
}

bool Deck::isFull(){
  if(cardsLeft() == 52*numOfDecks)
    return true;
  else
    return false;
}

int Deck::cardsLeft(){
  Card* curr = Top;
  int count = 0;

  while(curr != NULL){
    curr = curr -> next;
    count++;
  }

  return count;
}

int Deck::getCard(int position){
  Card* curr = Top;
  int Cardvalue = 0;

  for(int i = 1; i < position; i++){
    curr = curr -> next;
  }

  Cardvalue = curr -> value;

  if(curr -> next == NULL){
    curr -> prev -> next = NULL;
    delete curr;
  }
  else{
    curr -> prev -> next = curr -> next;
    delete curr;
  }

  return Cardvalue;
}

void Deck::shuffle(){
  int card = 0;
  int unusedCards = 52*numOfDecks;
  vector<int> d;

  while(!isEmpty())
    RemoveTop();

  for(int i = 1; i <= 52*numOfDecks; i++){
    d.push_back(i);
  }

  while(d.size() != 0){
    card = rand() % d.size() + 0;
    push(d[card]);
    d.erase(d.begin() + card);
  }
}