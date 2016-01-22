#include<iostream>
#include<fstream>
#include"dealer.h"
using namespace std;

Dealer::Dealer(int players, int decks) : Player(), Deck(){//CONSTRUCTOR
  ifstream inFile;
  string tempString = "";

  numOfDecks = decks;

  inFile.open("PairsAces.txt");//GRAB THE CARD VALUES FOR PAIRS AND ACES

  while(inFile>>tempString){
    aceDubs.push_back(tempString);//CREATE VECTOR FOR THEM
  }

  inFile.close();

  inFile.open("plays.txt");//GRAB REGULAR PLAYS FROM CARD

  while(inFile>>tempString){//CREATE VECTOR FOR THEM
    reg.push_back(tempString);
  }

  inFile.close();

  for(int i = 0; i < players + 1; i++){//CREATE NEW PLAYERS
    p[i].playerNumber = i + 1;
  }

  avgWinnings = 0;
  winningHands = 0;
  totalPlayers = players + 1;//ADD ONE TO PLAYERS FOR THE DEALER SPOT
}

Dealer::~Dealer(){
}

void Dealer::DealCards(){//DEALS OUT NEW CARDS
  for(int players = 0; players < totalPlayers; players++){//DELETES ALL PREVIOUS CARDS
    for(int j = 0; j < p[players].handCount; j++){//FOR EACH HAND
      p[players].hands[j].deleteCards();//DELETE CARDS
    }
    p[players].handCount = 1;//RESET HAND COUNT TO ONE
  }
  
  if(cardsLeft() < totalPlayers * 8){//SHUFFLE IF BELOW A CERTAIN CARD COUNT
    shuffle();

    for(int i = 0; i < counters; i++){//RESET ALL COUNTERS FOR NEW SHUFFLE
      count[i] = 0;
    }
  }
  
  int card = 0;
  
  for(int i = 0; i < totalPlayers; i++){//DEAL OUT CARDS
    card = RemoveTop();
    
    for(int counts = 0; counts < counters; counts++){//EACH PLAYER BETS
      p[i].makeBet(count[counts], counts, numOfDecks);
    }
    
    p[i].hands[0].takeCard(card);//TAKE FIRST CARD
  }
  
  for(int i = 0; i < totalPlayers; i++){//TAKE SECOND CARD
    card = RemoveTop();
    p[i].hands[0].takeCard(card);
  }
}

int Dealer::getPlay(int player, int hand, int dealerCard){//GET PLAY FOR HIT, STAND, SPLIT, DOUBLEDOWN
  int play = p[player].hands[hand].handPlay();
  int firstCard = p[player].hands[hand].getCardValue(p[player].hands[hand].firstCard -> value);//FIRST CARD
  int secondCard = p[player].hands[hand].getCardValue(p[player].hands[hand].firstCard -> next -> value);//SECOND CARD IN HAND
  
  switch(play){
  case -1: 
    p[player].hands[hand].takeCard(RemoveTop());//IF HIT
    break;
  case 0:
    return regular(p[player].hands[hand].handTotal(), dealerCard);//GET PLAY FOR REGULAR HAND
  case 2:
    return aceDoublesHand(false, secondCard, dealerCard);//GET PLAY FOR PAIR
  case 1:
    if(firstCard == 11)
      return aceDoublesHand(true, secondCard, dealerCard);//GET PLAY FOR ACE IN HAND
    else
      return aceDoublesHand(true, firstCard, dealerCard);//GET PLAY FOR ACE IN HAND
  default:
    break;
  }
}

void Dealer::keepPlaying(int player, int hand, int dealerCard, int play){//KEEP HITTING
  bool keepPlaying = false;
  bool takeCard = false;
  
  keepPlaying = p[player].playType(play, hand, takeCard);//IF KEEP PLAYING == TRUE

  if(takeCard){//HIT 
    p[player].hands[hand].takeCard(RemoveTop());
    takeCard = false;
  }
  
  if(play == 3)//IF SPLIT
    return;
  
  if(p[player].hands[hand].handTotal() < 4)//IF # OF HANDS < 3 (LIMITS NUMBER OF SPLITS ALLOWED)
    p[player].hands[hand].takeCard(RemoveTop());
  
  while(keepPlaying){//WHILE KEEP HITTING
    if(p[player].hands[hand].handTotal() > 20)//IF 21 OR BUST
      break;
    
    //IF KEEP HITTING
    if(regular(p[player].hands[hand].handTotal(), dealerCard) == 1 || regular(p[player].hands[hand].handTotal(), dealerCard) == 4)
      p[player].hands[hand].takeCard(RemoveTop());
    else
      break;
  }
}

void Dealer::nextPlayer(){//NEXT PLAYERS TURN
  int dealerCard = p[0].hands[0].getCardValue(p[0].hands[0].firstCard -> value);//DEALERS FACE UP CARD
  int play = -1;

  if(p[0].hands[0].handTotal() == 21){//IF DEALER HAS 21
    distributeWinnings(true);
    getNewCount();
    return;
  }

  for(int i = 1; i < totalPlayers; i++){//FOR NUMBER OF PLAYERS
    for(int j = 0; j < p[i].handCount; j++){//FOR HAND COUNT

      if(p[i].hands[j].totalCards == 1)//IF SPLIT
	p[i].hands[j].takeCard(RemoveTop());

      if(p[i].hands[j].handTotal() > 20)//IF 21 OR BUST
        continue;

      play = getPlay(i, j, dealerCard);//GET PLAY

      keepPlaying(i, j, dealerCard, play);//KEEP HITTING
    }
  }
  
  while(p[0].hands[0].handTotal() < 17){//DEALERS TURN WHILE < 17
    p[0].hands[0].takeCard(RemoveTop());
  }

  distributeWinnings(false);//DISTRIBUTE THE WINNINGS IF DEALER DOES NOT HAVE BJ
  getNewCount();//GET THE NEW COUNTS
}

int Dealer::aceDoublesHand(bool ace, int card2, int dealerCard){//IF ACE OR DOUBLES
  string tempString = "";

  for(int i = 0; i < aceDubs.size(); i++){
    if(!ace){//IF PAIR
        tempString = aceDubs[(80 + (card2 - 2)*10) + dealerCard - 2];
	return play(tempString);//RETURN THE PLAY TYPE
      }
    else{//IF DOUBLES
        tempString = aceDubs[(card2 - 2)*10 + dealerCard - 2];
	return play(tempString);//RETURN THE PLAY TYPE
      }
  }

  return 0;
}

//========================================================//
// HI - LOW
// 2-6 = +1
// 7-9 = 0
// 10-A = -1
//========================================================//
void Dealer::hiLowCount(int card){//GET NEW COUNT FOR HI LOW
  if(card >= 10)//IF ACE OR TEN
    count[0]++;
  else if(card <= 6)//IF 6 OR BELOW
    count[0]--;
}

//========================================================//
// RED-SEVEN
// 2-6, RED 7 = +1
// 8,9 = 0
// 10-A, BLACK 7 = -1
//========================================================//
void Dealer::redSevenCount(int card){
  int redSeven = rand() % 2 + 1;

  if(card >= 10 || redSeven == 1)
    count[1]--;
  else if(card <= 6 || redSeven == 2)
    count[1]++;
}

//========================================================//
// OMEGA II
// 2,3,7 = +1
// 4,5,6 = +2
// 8, A = 0
// 9 = -1
// 10 = -2
//========================================================//
void Dealer::omegaCount(int card){
  switch(card){
  case 2: case 3: case 7:
    count[2]++;
    break;
  case 4: case 5: case 6:
    count[2] += 2;
    break;
  case 9:
    count[2]--;
    break;
  case 10:
    count[2] -= 2;
    break;
  default:
    break;
  }
}

//========================================================//
// WONG-HALVES
// 5 = +1.5
// 3,4,7 = +1
// 2,7 = +.5
// 8 = +0
// 9 = -.5
// 10,11 = -1
//========================================================//
void Dealer::wongHalves(int card){
  switch(card){
  case 10: case 11:
    count[3]--;
    break;
  case 2: case 7:
    count[3] += .5;
    break;
  case 3: case 4: case 6:
    count[3]++;
    break;
  case 5:
    count[3] += 1.5;
    break;
  case 9:
    count[3] -= .5;
    break;
  default:
    break;
  }
}

int Dealer::play(string p){
  if(p == "H")//IF HIT
    return 1;
  else if(p == "S")//IF STAND
    return 0;
  else if(p == "SP")//IF SPLIT
    return 3;
  else if(p == "Ds")//IF DOUBLE DOWN - STAND
    return 5;
  else//IF DOUBLE DOWN - HIT
    return 4;
}

int Dealer::regular(int handTotal, int dealerCard){//CHECK REGULAR HAND PLAY
  string tempString = "";

  for(int i = 0; i < reg.size(); i++){
    tempString = reg[(20 - handTotal)*10 + dealerCard - 2];
    return play(tempString);//RETURN PLAY
  }
}
 
void Dealer::displayAllHands(){//DISPLAY ALL HANDS WITH WINNINGS AND COUNT
  double avgWinnings = 0;

  cout<<"\n================================================"<<endl;
  cout<<"================================================"<<endl;

  for(int i = 0; i < totalPlayers; i++){//FOR EACH PLAYER
    if(i == 0)
      cout<<"\nDealer: "<<endl;
    else
      cout<<"\nPlayer "<<i + 1<<": "<<endl;

    for(int j = 0; j < p[i].handCount; j++){//FOR EACH HAND
      p[i].hands[j].displayCards(j);
    }
   
    if(i != 0){//WINNINGS
	cout<<"HI-LOW      Winnings: "<<p[i].chips[0]<<endl;
	cout<<"RED-SEVEN   Winnings: "<<p[i].chips[1]<<endl;
	cout<<"OMEGA II    Winnings: "<<p[i].chips[2]<<endl;
	cout<<"WONG-HALVES Winnings: "<<p[i].chips[3]<<endl;
    }
  }
  //COUNTS
  cout<<"\nHI-LOW       Count: "<<count[0]<<endl;
  cout<<"RED-SEVEN    Count: "<<count[1]<<endl;
  cout<<"OMEGA II     Count: "<<count[2]<<endl;
  cout<<"WONG-HALVES  Count: "<<count[3]<<endl;

  cout<<"\n================================================"<<endl;
  cout<<"================================================"<<endl;
}

void Dealer::getNewCount(){//GET NEW COUNT
  Card *curr = NULL;
  int value = 0;

  for(int i = 0; i < totalPlayers; i++){//FOR EACH PLAYER
    for(int j = 0; j < p[i].handCount; j++){//FOR EACH HAND
      curr = p[i].hands[j].firstCard;

      while(curr != NULL){//FOR ECH CARD THAT WAS ON THE TABLE
	value = p[i].hands[j].getCardValue(curr -> value); 
	
	hiLowCount(value);//UPDATE COUNT VALUES
	redSevenCount(value);
	omegaCount(value);
	wongHalves(value);

	curr = curr -> next;//NEXT CARD
      }
    }
  }
}


void Dealer::payOut(int player, int hand, bool win, bool BJ){//PAY THE PLAYERS
  double BJPayout = 1.5;

  for(int i = 0; i < counters; i++){
    if(BJ){//IF BLACKJACK
      p[player].chips[i] += (double)(p[i].hands[hand].handCost[i]*BJPayout);
    }
    else if(win){//IF WIN
      p[player].chips[i] += p[i].hands[hand].handCost[i];
    }
    else{//IF LOSE
      p[player].chips[i] -= p[i].hands[hand].handCost[i];
    }
  }
}

void Dealer::distributeWinnings(bool BJ){//CHECK HANDS FOR PAYOUT
  int dealerHand = p[0].hands[0].handTotal();
  int pHandTotal = 0;  

  for(int i = 0; i < totalPlayers; i++){
    for(int j = 0; j < p[i].handCount; j++){
      pHandTotal = p[i].hands[j].handTotal();

      if(BJ && pHandTotal != 21)//IF DEALER BLACKJACK
	payOut(i, j, false, false);
      else if(pHandTotal == 21 && p[i].hands[j].totalCards == 2){//IF PLAYER BLACKJACK
	payOut(i, j, true, true);
      }
      else if(pHandTotal <= 21){//IF IF NOT BUST
	if(dealerHand > 21 && pHandTotal <= 21){//IF DEALER BUST AND PLAYER NOT BUST
	  payOut(i, j, true, false);
	}
	else if(dealerHand > pHandTotal){//IF DEALER HAS HIGHER HAND
	  payOut(i, j, false, false);
	}
	else if(pHandTotal > dealerHand){//IF PLAYER HAS HIGHER HAND
	  payOut(i, j, true, false);
	}
      }
      else if(pHandTotal > 21)//IF PLAYER BUST
	payOut(i, j, false, false);
    }
  }
}
