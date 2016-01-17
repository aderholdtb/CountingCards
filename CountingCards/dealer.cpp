#include<iostream>
#include<fstream>
#include"dealer.h"
using namespace std;

Dealer::Dealer(int players) : Player(), Deck(){
  ifstream inFile;//NEED TO GRAB THE BLACKJACK PLAY CARD
  string tempString ="";

  inFile.open("PairsAces.txt");

  while(inFile>>tempString){//ADD ACE PLAY TO A VECTOR FOR EASY ACCESS
    aceDubs.push_back(tempString);
  }

  inFile.close();

  inFile.open("plays.txt");

  while(inFile>>tempString){//ADD REGULAR HAND PLAYS TO A VECTOR (EX: NO PAIRS OR ACE IN HAND)
    reg.push_back(tempString);
  }

  inFile.close();

  for(int i = 0; i < players + 1; i++){//ADD PLAYERS TO TABLE
    p[i].playerNumber = i + 1;
  }

  avgWinnings = 0;
  winningHands = 0;
  totalPlayers = players + 1;
}

Dealer::~Dealer(){
}

void Dealer::DealCards(){//DEAL THE CARDS FOR THIS HAND
  int regularBet = 5;

  for(int players = 0; players < totalPlayers; players++){
    for(int j = 0; j < p[players].handCount; j++){
      p[players].hands[j].deleteCards();
	}
    p[players].handCount = 1;
  }

  if(cardsLeft() < totalPlayers * 6){//CHECK FOR NEED TO SHUFFLE DECK
    shuffle();
    count = 0;
  }

  int card = 0;
  for(int i = 0; i < totalPlayers; i++){//ADD TWO CARDS TO EVERY HAND
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

void Dealer::nextPlayer(){//SIMULATE A HAND OF BLACKJACK
  int dealerCard = p[0].hands[0].getCardValue(p[0].hands[0].firstCard -> value);//GET DEALERS FACE UP CARD
  int play = -1;
  bool keepPlaying = true;
  bool takeCard = false;

  if(p[0].hands[0].handTotal() == 21){//CHECK FOR IMMEDIATE 21
    distributeWinnings(true);//IF BLACKJACK DEALER
    getNewCount();
    return;
  }

  for(int i = 1; i < totalPlayers; i++){//RUN THROUGH EVERY PLAYERS HAND
    for(int j = 0; j < p[i].handCount; j++){//AMOUNT OF HANDS THAT PLAYER HAS (ONLY WHEN SPLITTING)
      if(p[i].hands[j].handTotal() > 20)
	continue;

      if(p[i].hands[j].totalCards == 1)//IF ONLY ONE CARD IN HAND
	p[i].hands[j].takeCard(RemoveTop());

	play = p[i].hands[j].handPlay();//GET PLAY TYPE (EX: HIT, STAND, ETC.)

	if(play == -1){//IF HIT
	  p[i].hands[j].takeCard(RemoveTop());
	}
	else if(play == 0){//GET PLAY FOR REGUALR HAND (NO PAIR OR ACES)
	  play = regular(p[i].hands[j].handTotal(), dealerCard);
       	}
	else if(play == 2){//IF ACES IN HAND
	  play = aceDoublesHand(false, p[i].hands[j].getCardValue(p[i].hands[j].firstCard -> next -> value), dealerCard);
	}
	else if(play == 1){//IF PAIR
	  if(p[i].hands[j].getCardValue(p[i].hands[j].firstCard -> value) == 11){
	    play = aceDoublesHand(true, p[i].hands[j].getCardValue(p[i].hands[j].firstCard -> next -> value), dealerCard);
	  }
	  else{
	    play = aceDoublesHand(true, p[i].hands[j].getCardValue(p[i].hands[j].firstCard -> value), dealerCard);
	  }
	}

	  keepPlaying = p[i].playType(play, j, takeCard);//IF NEED TO KEEP HITTING

	if(takeCard){//TAKE A CARD
	  p[i].hands[j].takeCard(RemoveTop());
	  takeCard = false;
	}
	
	if(play == 3)//IF SPLIT
	  continue;

	if(p[i].hands[j].handTotal() < 4)//IF HAND COUNT IS LESS THAN 4
	  p[i].hands[j].takeCard(RemoveTop());

	while(keepPlaying){//KEEP HITTING
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

  while(p[0].hands[0].handTotal() < 17){//FINISH DEALERS HAND
    p[0].hands[0].takeCard(RemoveTop());
  }

  distributeWinnings(false);//DEALER DOES NOT HAVE BLACKJACK
  getNewCount();
}

int Dealer::aceDoublesHand(bool ace, int card2, int dealerCard){//IF ACE OR PAIR IN HAND
  string tempString = "";

  for(int i = 0; i < aceDubs.size(); i++){
    if(!ace){
        tempString = aceDubs[(80 + (card2 - 2)*10) + dealerCard - 2];//CHECK RULE ON CARD FOR ACE
	return play(tempString);//RETURN PLAY TYPE
      }
    else{//CHECK PAIR
        tempString = aceDubs[(card2 - 2)*10 + dealerCard - 2];//CHECK RULE ON CARD FOR PAIR
	return play(tempString);//RETURN PLAY TYPE
      }
  }

  return 0;
}


int Dealer::play(string p){
  if(p == "H")//HIT
    return 1;
  else if(p == "S")//STAND
    return 0;
  else if(p == "SP")//SPLIT
    return 3;
  else if(p == "Ds")//DOUBLE DOWN - STAND
    return 5;
  else//DOUBLE DOWN - HIT
    return 4;
}

int Dealer::regular(int handTotal, int dealerCard){//CHECK RULE FOR REGULAR HAND
  string tempString = "";
  
  for(int i = 0; i < reg.size(); i++){
    tempString = reg[(20 - handTotal)*10 + dealerCard - 2];//GET RULE ON CARD
    return play(tempString);//GET PLAY TYPE
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

void Dealer::getNewCount(){//GET NEW COUNT FOR COUNTING CARDS
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

void Dealer::distributeWinnings(bool BJ){//UPDATE WINNINGS
  int dealerHand = p[0].hands[0].handTotal();
  int pHandTotal = 0;  
  float BJPayout = 3/2;//TABLE PAYS 3 TO 2 ON BLACKJACK
  avgWinnings = 0;

  for(int i = 0; i < totalPlayers; i++){//CHECK EVERY PLAYERS HAND
    for(int j = 0; j < p[i].handCount; j++){
      pHandTotal = p[i].hands[j].handTotal();

      if(BJ && pHandTotal != 21)//IF DEALER HAS BLACKJACK AND PLAYER DOES NOT
	p[i].chips -= p[i].hands[j].handCost;
      else if(pHandTotal == 21 && p[i].hands[j].totalCards == 2){//IF PLAYER BLACKJACK
	winningHands++;
	p[i].chips += p[i].hands[j].handCost*BJPayout;
      }
      else if(pHandTotal <= 21){//IF PLAYER NOT BUST
	if(dealerHand > 21 && pHandTotal <= 21){//IF DEALER BUST
	  winningHands++;
	  p[i].chips += p[i].hands[j].handCost;
	}
	else if(dealerHand > pHandTotal){//IF DEALER HAND BEATS PLAYER HAND
	  p[i].chips -= p[i].hands[j].handCost;
	}
	else if(pHandTotal > dealerHand){//IF PLAYER HAND BEATS DEALERS
	  winningHands++;
	  p[i].chips += p[i].hands[j].handCost;
	}
      }
      else if(pHandTotal > 21)//IF PLAYER BUST
	p[i].chips -= p[i].hands[j].handCost;

      p[i].hands[j].handCost = 0;//RESET HAND COST FOR NEW HAND
    }
      avgWinnings += p[i].chips;
  }

  avgWinnings /= totalPlayers - 1;//GET AVG WINNINGS 
}
