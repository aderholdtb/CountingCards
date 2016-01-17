#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include"player.h"
using namespace std;

Player::Player(){
  playerNumber = 0;
  handCount = 1;//AMOUNT OF HANDS
  chips = 10000;//STARTING CHIPS
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
    takeCard = true;
    return true;
  }
  else if(play == 3){//IF SPLIT
      split(hand);
      handCount++;
      takeCard = true;
      return false;
  }
  else if(play == 4){//IF DOUBLE DOWN - STAND
    if(doubleD){
      hands[hand].doubleDown();
      takeCard = true;
      return false;
    }
    else{
      takeCard = true;
      return false;
    }
  }
  else if(play == 5){//IF DOUBLE DOWN - HIT
    if(doubleD){
      hands[hand].doubleDown();
      takeCard = true;
      return false;
    }
    else{
      takeCard = true;
      return false;
    }
  }
}

void Player::split(int hand){//ADD NEW HAND AND SPLIT CARDS
  hands[hand + 1].takeCard(hands[hand].deleteFirstCard());
}
