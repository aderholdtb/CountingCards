#include<iostream>
#include<fstream>
#include"dealer.h"
using namespace std;

Dealer::Dealer(int players) : Player(), Deck(){
  ifstream inFile;
  string tempString ="";

  inFile.open("PairsAces.txt");

  while(inFile>>tempString){
    aceDubs.push_back(tempString);
  }

  inFile.close();

  inFile.open("plays.txt");

  while(inFile>>tempString){
    reg.push_back(tempString);
  }

  inFile.close();

  for(int i = 0; i < players + 1; i++){
    p[i].playerNumber = i + 1;
  }

  avgWinnings = 0;
  winningHands = 0;
  totalPlayers = players + 1;
}

Dealer::~Dealer(){
}

void Dealer::DealCards(){
  int regularBet = 5;

  for(int players = 0; players < totalPlayers; players++){
    for(int j = 0; j < p[players].handCount; j++){
      p[players].hands[j].deleteCards();
	}
    p[players].handCount = 1;
  }

  if(cardsLeft() < totalPlayers * 6){
    shuffle();
    count = 0;
  }

  int card = 0;
  for(int i = 0; i < totalPlayers; i++){
    card = RemoveTop();

    if(count <= 0)
      p[i].hands[0].bet(regularBet);
    else
      p[i].hands[0].bet(regularBet + count/numOfDecks);

    p[i].hands[0].takeCard(card);
  }

  for(int i = 0; i < totalPlayers; i++){
    card = RemoveTop();
    p[i].hands[0].takeCard(card);
  }
}

void Dealer::nextPlayer(){
  int dealerCard = p[0].hands[0].getCardValue(p[0].hands[0].firstCard -> value);
  int play = -1;
  bool keepPlaying = true;
  bool takeCard = false;

  if(p[0].hands[0].handTotal() == 21){
    distributeWinnings(true);
    getNewCount();
    return;
  }

  for(int i = 1; i < totalPlayers; i++){
    for(int j = 0; j < p[i].handCount; j++){
      if(p[i].hands[j].handTotal() > 20)
	continue;

      if(p[i].hands[j].totalCards == 1)
	p[i].hands[j].takeCard(RemoveTop());

	play = p[i].hands[j].handPlay();

	if(play == -1){
	  p[i].hands[j].takeCard(RemoveTop());
	}
	else if(play == 0){
	  play = regular(p[i].hands[j].handTotal(), dealerCard);
       	}
	else if(play == 2){
	  play = aceDoublesHand(false, p[i].hands[j].getCardValue(p[i].hands[j].firstCard -> next -> value), dealerCard);
	}
	else if(play == 1){
	  if(p[i].hands[j].getCardValue(p[i].hands[j].firstCard -> value) == 11){
	    play = aceDoublesHand(true, p[i].hands[j].getCardValue(p[i].hands[j].firstCard -> next -> value), dealerCard);
	  }
	  else{
	    play = aceDoublesHand(true, p[i].hands[j].getCardValue(p[i].hands[j].firstCard -> value), dealerCard);
	  }
	}

	  keepPlaying = p[i].playType(play, j, takeCard);

	if(takeCard){
	  p[i].hands[j].takeCard(RemoveTop());
	  takeCard = false;
	}
	if(play == 3)
	  continue;

	if(p[i].hands[j].handTotal() < 4)
	  p[i].hands[j].takeCard(RemoveTop());

	while(keepPlaying){
          if(p[i].hands[j].handTotal() > 20)
            break;

	  if(regular(p[i].hands[j].handTotal(), dealerCard) == 1){
	    p[i].hands[j].takeCard(RemoveTop());
	  }
	  else{
	    break;
	  }
	}

	  keepPlaying = true;
	  takeCard = false;
    }
  }

  while(p[0].hands[0].handTotal() < 17){
    p[0].hands[0].takeCard(RemoveTop());
  }

  distributeWinnings(false);
  getNewCount();
}

int Dealer::aceDoublesHand(bool ace, int card2, int dealerCard){
  string tempString = "";

  for(int i = 0; i < aceDubs.size(); i++){
    if(!ace){
        tempString = aceDubs[(80 + (card2 - 2)*10) + dealerCard - 2];
	return play(tempString);
      }
    else{
        tempString = aceDubs[(card2 - 2)*10 + dealerCard - 2];
	return play(tempString);
      }
  }

  return 0;
}


int Dealer::play(string p){
  //  cout<<"p : "<<p<<endl;
  if(p == "H")
    return 1;
  else if(p == "S")
    return 0;
  else if(p == "SP")
    return 3;
  else if(p == "Ds")
    return 5;
  else
    return 4;
}

int Dealer::regular(int handTotal, int dealerCard){
  string tempString = "";
  for(int i = 0; i < reg.size(); i++){
    tempString = reg[(20 - handTotal)*10 + dealerCard - 2];
    return play(tempString);
  }

}
 
void Dealer::displayAllHands(){
  double avgWinnings = 0;

  cout<<"\n================================================"<<endl;
  cout<<"================================================"<<endl;

  for(int i = 0; i < totalPlayers; i++){
    cout<<"\nPlayer "<<i + 1<<": "<<endl;
    for(int j = 0; j < p[i].handCount; j++){
      p[i].hands[j].displayCards(j);
    }
   
    if(i != 0){
      cout<<"Winnings: "<<p[i].chips<<endl;
      avgWinnings += p[i].chips;
    }
  }

  cout<<"Avg Winnings: "<<avgWinnings/(totalPlayers-1)<<endl;
  cout<<"Count: "<<count<<endl;

  cout<<"\n================================================"<<endl;
  cout<<"================================================"<<endl;
}

void Dealer::getNewCount(){
  Card *curr = NULL;
  for(int i = 0; i < totalPlayers; i++){
    for(int j = 0; j < p[i].handCount; j++){
      curr = p[i].hands[j].firstCard;

      while(curr != NULL){
	if(p[i].hands[j].getCardValue(curr -> value) >= 10)
	  count--; 
	else if(p[i].hands[j].getCardValue(curr -> value) < 7)
	  count++;

	curr = curr -> next;
      }
    }
  }
}

void Dealer::distributeWinnings(bool BJ){
  int dealerHand = p[0].hands[0].handTotal();
  int pHandTotal = 0;  
  float BJPayout = 3/2;
  avgWinnings = 0;

  for(int i = 0; i < totalPlayers; i++){
    for(int j = 0; j < p[i].handCount; j++){
      pHandTotal = p[i].hands[j].handTotal();

      if(BJ && pHandTotal != 21)
	p[i].chips -= p[i].hands[j].handCost;
      else if(pHandTotal == 21 && p[i].hands[j].totalCards == 2){
	winningHands++;
	p[i].chips += p[i].hands[j].handCost*BJPayout;
      }
      else if(pHandTotal <= 21){
	if(dealerHand > 21 && pHandTotal <= 21){
	  winningHands++;
	  p[i].chips += p[i].hands[j].handCost;
	}
	else if(dealerHand > pHandTotal){
	  p[i].chips -= p[i].hands[j].handCost;
	}
	else if(pHandTotal > dealerHand){
	  winningHands++;
	  p[i].chips += p[i].hands[j].handCost;
	}
      }
      else if(pHandTotal > 21)
	p[i].chips -= p[i].hands[j].handCost;

      p[i].hands[j].handCost = 0;
    }
      avgWinnings += p[i].chips;
  }

  avgWinnings /= totalPlayers - 1;
}
