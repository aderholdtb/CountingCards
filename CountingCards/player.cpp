#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include"player.h"
using namespace std;

Player::Player(){
  playerNumber = 0;
  handCount = 1;
  chips = 10000;
}

Player::~Player(){
  for(int i = 0; i < handCount; i++){
    hands[i].deleteCards();
  }
}

bool Player::playType(int play, int& hand, bool& takeCard){
  bool doubleD = true;

  if(play == 0)
    return false;
  else if(play == 1){
    takeCard = true;
    return true;
  }
  else if(play == 3){
      split(hand);
      handCount++;
      takeCard = true;
      return false;
  }
  else if(play == 4){
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
  else if(play == 5){
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

void Player::split(int hand){
  hands[hand + 1].takeCard(hands[hand].deleteFirstCard());
}
