#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include"player.h"
using namespace std;

Player::Player(){
  playerNumber = 0;
<<<<<<< HEAD
  handCount = 1;

  for(int i = 0; i < 4; i++){//START WITH 10000 CHIPS
    chips[i] = 10000;
  }
=======
  handCount = 1;//AMOUNT OF HANDS
  chips = 10000;//STARTING CHIPS
>>>>>>> origin/master
}

Player::~Player(){
  for(int i = 0; i < handCount; i++){
    hands[i].deleteCards();
  }
}

bool Player::playType(int play, int& hand, bool& takeCard){//TYPE OF PLAY FOR HAND
  bool doubleD = true;

  if(play == 0)//IF STAND
    return false;
  else if(play == 1){//IF HIT
<<<<<<< HEAD
=======
    takeCard = true;
>>>>>>> origin/master
    return true;
  }
  else if(play == 3){//IF SPLIT
      split(hand);
      handCount++;
      takeCard = true;
      return false;
  }
<<<<<<< HEAD
  else if(play == 4){//IF DOUBLE DOWN HIT
=======
  else if(play == 4){//IF DOUBLE DOWN - STAND
>>>>>>> origin/master
    if(doubleD){
      hands[hand].doubleDown();
      takeCard = true;
      return false;
    }
    else{
      return true;
    }
  }
<<<<<<< HEAD
  else if(play == 5){//IF DOUBLE DOWN STAND
=======
  else if(play == 5){//IF DOUBLE DOWN - HIT
>>>>>>> origin/master
    if(doubleD){
      hands[hand].doubleDown();
      takeCard = true;
      return false;
    }
    else{
      return false;
    }
  }
}

<<<<<<< HEAD
void Player::split(int hand){//SPLIT HAND
  hands[hand + 1].takeCard(hands[hand].deleteFirstCard());//ADD CARD TO SECOND HAND

  for(int i = 0 ; i < 4; i++){//UPDATE HAND COST
    hands[hand + 1].handCost[i] = hands[hand].handCost[i];
  }
}

void Player::makeBet(double count, int type, int decks){//MAKE BET BASED ON COUNT
  int regBet = 50;//REGULAR BET WITH NO COUNT

  switch(type){
  case 0: case 2: case 3://IF HI-LOW, OMEGA, OR WONG-HALVES
    if(count/decks >= 3)//IF COUNT IS ABOVE 3
      hands[0].handCost[type] = regBet + count/decks;//MAKE BIGGER BET
    else
      hands[0].handCost[type] = regBet;//MAKE REGUALR BET
    break;
  case 1://IF RED-SEVEN
    if((count - (2* decks))/decks >= 3)//IF COUNT IS ABOVE 3
      hands[0].handCost[type] = regBet + count/decks;//BIGGER BET
    else
      hands[0].handCost[type] = regBet;//MAKE REGULAR BET
    break;
  default:
    break;
  }
=======
void Player::split(int hand){//ADD NEW HAND AND SPLIT CARDS
  hands[hand + 1].takeCard(hands[hand].deleteFirstCard());
>>>>>>> origin/master
}
