#include<iostream>
#include"hand.h"
using namespace std;

Hand::Hand(){
  firstCard = NULL;
  playerNumber = 0;
  totalCards = 0;
}

Hand::Hand(int player){
  firstCard = NULL;
  playerNumber = player;
}

Hand::~Hand(){
  deleteCards();
}

void Hand::doubleDown(){
  for(int i = 0; i < 4; i++){//DOUBLE DOWN FOR EVERY COUNT TYPE
    handCost[i]*=2;
  }

  doubleD=true;
}

void Hand::bet(double betAmount, int type){//BET FOR TYPE OF COUNT
  handCost[type] = betAmount;
}

void Hand::takeCard(int Cardvalue){//GRAB NEW CARD
  Card* curr = firstCard, *newCard = NULL;
  newCard = new Card();//CREATE NEW CARD
  newCard -> value = Cardvalue;
  newCard -> next = NULL;

  if(curr == NULL){//IF NO CARDS IN HAND
    firstCard = newCard;
  }
  else{//IF CARDS IN HAND ALREADY
    while(curr -> next != NULL){
      curr = curr -> next;
    }

    curr -> next = newCard;
    newCard -> prev = curr;
  }

  totalCards++;
}

void Hand::deleteCards(){//DELETE CARDS IN HAND
  Card* curr = firstCard;

  if(curr == NULL){//IF NO CARDS IN HAND
    return;
  }
  else{
    while(curr != NULL){//WHILE CARDS IN HAND
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

  while(curr != NULL){//WHILE THERE ARE CARDS LEFT IN HAND
    cardvalue = getCardValue(curr -> value);

    if(cardvalue == 11)
      aceCount++;

    count += cardvalue;
    curr = curr -> next;
  }

  for(int i = 0; i < aceCount; i++){//CHECK FOR ACES
    if(count > 21)
      count -= 10;
    else
      break;
  }

  return count;
}

int Hand::getCardValue(int card){//GET CARD VALUE
  card %= 13;

  if(card == 11 || card == 12 || card == 10)
    return 10;
  if(card == 0)
    return 11;

  return card + 1;
}

void Hand::displayCards(int hand){//DISPLAY ALL CARDS
  Card* curr = firstCard;
  int cardValue = 0;

  cout<<"Hand "<<hand + 1<<": ";

  while(curr != NULL){//FOR EVERY CARD IN HAND
    cardValue = curr -> value%52;
    cout<<getCardValue(cardValue);

    if(cardValue <=13){//IF HEART
      cout<<"H ";
    }
    else if(cardValue <= 26){//IF DIAMOND
      cout<<"D ";
    }
    else if(cardValue <= 39){//IF SPADE
      cout<<"S ";
    }
    else{//IF CLUB
      cout<<"C ";
    }

    curr = curr -> next;
  }

  cout<<" - Total: "<<handTotal()<<endl;//HAND TOTAL
}

int Hand::deleteFirstCard(){//DELETE FIRST CARD
  Card* curr = firstCard;
  int card = 0;

  if(curr == NULL){//IF NO CARDS IN HAND
    return -1;
  }
  else if(curr -> next == NULL){//IF ONE CARD IN HAND
    card = curr -> value;
    delete curr;
    firstCard = NULL;
  }
  else{//MORE THAN ONE CARD IN HAND
    card = curr -> value;
    firstCard = curr -> next;
    delete curr;
    firstCard -> prev = NULL;
  }

  totalCards--;
  return card;
}

int Hand::handPlay(){//GET TYPE OF PLAY 
  Card* curr = firstCard;

  if(totalCards == 2){
    int card1 = (firstCard -> value)%13;
    int card2 = (firstCard -> next -> value)%13;

    if(card1 == card2){//IF PAIR
      return 2;
    }
    else if(card1 == 0 || card2 == 0)//IF ACE
      return 1;
    else{//IF REGULAR HAND
      return 0;
    }
  }

  return -1;
}
