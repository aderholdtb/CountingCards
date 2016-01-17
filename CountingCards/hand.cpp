#include<iostream>
#include"hand.h"
using namespace std;

Hand::Hand(){
  firstCard = NULL;
  playerNumber = 0;
  totalCards = 0;
  handCost = 0;
}

Hand::Hand(int player){
  firstCard = NULL;
  playerNumber = player;
}

Hand::~Hand(){
  deleteCards();
}

void Hand::bet(double betAmount){//BET AMOUNT
  handCost = betAmount;
}

void Hand::takeCard(int Cardvalue){//ADD CARD TO HAND
  Card* curr = firstCard, *newCard = NULL;
  newCard = new Card();
  newCard -> value = Cardvalue;
  newCard -> next = NULL;

  if(curr == NULL){
    firstCard = newCard;
  }
  else{
    while(curr -> next != NULL){
      curr = curr -> next;
    }

    curr -> next = newCard;
    newCard -> prev = curr;
  }

  totalCards++;
}

void Hand::deleteCards(){//DELETE HAND
  Card* curr = firstCard;

  if(curr == NULL){
    return;
  }
  else{
    while(curr != NULL){
      firstCard = curr -> next;
      delete curr;
      curr = firstCard;
      totalCards--;
    }
  }
}

int Hand::handTotal(){//GET HAND TOTAL
  Card* curr = firstCard;
  int count = 0;
  int aceCount = 0;
  int cardvalue = 0;

  while(curr != NULL){
    cardvalue = getCardValue(curr -> value);

    if(cardvalue == 11)//UPDATE ACE COUNT
      aceCount++;

    count += cardvalue;
    curr = curr -> next;
  }

  for(int i = 0; i < aceCount; i++){
    if(count > 21)
      count -= 10;
    else
      break;
  }

  return count;
}

int Hand::getCardValue(int card){//RETURN CARD VALUE 1-11
  card %= 13;

  if(card == 11 || card == 12 || card == 10)
    return 10;
  if(card == 0)
    return 11;

  return card + 1;
}

void Hand::displayCards(int hand){//DISPLAY CARDS, SUIT AND CARD
  Card* curr = firstCard;
  int cardValue = 0;

  cout<<"Hand "<<hand + 1<<": ";

  while(curr != NULL){
    cardValue = curr -> value%52;
    cout<<getCardValue(cardValue);

    if(cardValue <=13){
      cout<<"H ";
    }
    else if(cardValue <= 26){
      cout<<"D ";
    }
    else if(cardValue <= 39){
      cout<<"S ";
    }
    else{
      cout<<"C ";
    }

    curr = curr -> next;
  }

  cout<<" - Total: "<<handTotal()<<endl;
}

int Hand::deleteFirstCard(){
  Card* curr = firstCard;
  int card = 0;

  if(curr == NULL){
    return -1;
  }
  else if(curr -> next == NULL){
    card = curr -> value;
    delete curr;
    firstCard = NULL;
  }
  else{
    card = curr -> value;
    firstCard = curr -> next;
    delete curr;
    firstCard -> prev = NULL;
  }

  totalCards--;
  return card;
}

int Hand::handPlay(){
  Card* curr = firstCard;

  if(totalCards == 2){
    int card1 = (firstCard -> value)%13;
    int card2 = (firstCard -> next -> value)%13;

    if(card1 == card2){//IF PAIR
      return 2;
    }
    else if(card1 == 0 || card2 == 0)//IF ACE IN HAND
      return 1;
    else{
      return 0;
    }
  }

  return -1;
}
