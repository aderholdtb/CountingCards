#include<iostream>
#include<fstream>
#include"dealer.h"
using namespace std;

<<<<<<< HEAD
Dealer::Dealer(int players, int decks) : Player(), Deck(){//CONSTRUCTOR
  ifstream inFile;
  string tempString = "";

  numOfDecks = decks;
=======
Dealer::Dealer(int players) : Player(), Deck(){
  ifstream inFile;//NEED TO GRAB THE BLACKJACK PLAY CARD
  string tempString ="";
>>>>>>> origin/master

  inFile.open("PairsAces.txt");//GRAB THE CARD VALUES FOR PAIRS AND ACES

<<<<<<< HEAD
  while(inFile>>tempString){
    aceDubs.push_back(tempString);//CREATE VECTOR FOR THEM
=======
  while(inFile>>tempString){//ADD ACE PLAY TO A VECTOR FOR EASY ACCESS
    aceDubs.push_back(tempString);
>>>>>>> origin/master
  }

  inFile.close();

  inFile.open("plays.txt");//GRAB REGULAR PLAYS FROM CARD

<<<<<<< HEAD
  while(inFile>>tempString){//CREATE VECTOR FOR THEM
=======
  while(inFile>>tempString){//ADD REGULAR HAND PLAYS TO A VECTOR (EX: NO PAIRS OR ACE IN HAND)
>>>>>>> origin/master
    reg.push_back(tempString);
  }

  inFile.close();

<<<<<<< HEAD
  for(int i = 0; i < players + 1; i++){//CREATE NEW PLAYERS
=======
  for(int i = 0; i < players + 1; i++){//ADD PLAYERS TO TABLE
>>>>>>> origin/master
    p[i].playerNumber = i + 1;
  }

  avgWinnings = 0;
  winningHands = 0;
  totalPlayers = players + 1;//ADD ONE TO PLAYERS FOR THE DEALER SPOT
}

Dealer::~Dealer(){
}

<<<<<<< HEAD
void Dealer::DealCards(){//DEALS OUT NEW CARDS
  for(int players = 0; players < totalPlayers; players++){//DELETES ALL PREVIOUS CARDS
    for(int j = 0; j < p[players].handCount; j++){//FOR EACH HAND
      p[players].hands[j].deleteCards();//DELETE CARDS
    }
    p[players].handCount = 1;//RESET HAND COUNT TO ONE
  }
  
  if(cardsLeft() < totalPlayers * 8){//SHUFFLE IF BELOW A CERTAIN CARD COUNT
=======
void Dealer::DealCards(){//DEAL THE CARDS FOR THIS HAND
  int regularBet = 5;

  for(int players = 0; players < totalPlayers; players++){
    for(int j = 0; j < p[players].handCount; j++){
      p[players].hands[j].deleteCards();
	}
    p[players].handCount = 1;
  }

  if(cardsLeft() < totalPlayers * 6){//CHECK FOR NEED TO SHUFFLE DECK
>>>>>>> origin/master
    shuffle();

    for(int i = 0; i < counters; i++){//RESET ALL COUNTERS FOR NEW SHUFFLE
      count[i] = 0;
    }
  }
  
  int card = 0;
<<<<<<< HEAD
  
  for(int i = 0; i < totalPlayers; i++){//DEAL OUT CARDS
    card = RemoveTop();
    
    for(int counts = 0; counts < counters; counts++){//EACH PLAYER BETS
      p[i].makeBet(count[counts], counts, numOfDecks);
    }
    
    p[i].hands[0].takeCard(card);//TAKE FIRST CARD
  }
  
  for(int i = 0; i < totalPlayers; i++){//TAKE SECOND CARD
=======
  for(int i = 0; i < totalPlayers; i++){//ADD TWO CARDS TO EVERY HAND
>>>>>>> origin/master
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

<<<<<<< HEAD
void Dealer::nextPlayer(){//NEXT PLAYERS TURN
  int dealerCard = p[0].hands[0].getCardValue(p[0].hands[0].firstCard -> value);//DEALERS FACE UP CARD
=======
void Dealer::nextPlayer(){//SIMULATE A HAND OF BLACKJACK
  int dealerCard = p[0].hands[0].getCardValue(p[0].hands[0].firstCard -> value);//GET DEALERS FACE UP CARD
>>>>>>> origin/master
  int play = -1;

<<<<<<< HEAD
  if(p[0].hands[0].handTotal() == 21){//IF DEALER HAS 21
    distributeWinnings(true);
=======
  if(p[0].hands[0].handTotal() == 21){//CHECK FOR IMMEDIATE 21
    distributeWinnings(true);//IF BLACKJACK DEALER
>>>>>>> origin/master
    getNewCount();
    return;
  }

<<<<<<< HEAD
  for(int i = 1; i < totalPlayers; i++){//FOR NUMBER OF PLAYERS
    for(int j = 0; j < p[i].handCount; j++){//FOR HAND COUNT

      if(p[i].hands[j].totalCards == 1)//IF SPLIT
	p[i].hands[j].takeCard(RemoveTop());

      if(p[i].hands[j].handTotal() > 20)//IF 21 OR BUST
        continue;

      play = getPlay(i, j, dealerCard);//GET PLAY
=======
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
>>>>>>> origin/master

      keepPlaying(i, j, dealerCard, play);//KEEP HITTING
    }
  }
<<<<<<< HEAD
  
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
=======

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
>>>>>>> origin/master
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
<<<<<<< HEAD
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
=======
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
>>>>>>> origin/master
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

<<<<<<< HEAD
void Dealer::getNewCount(){//GET NEW COUNT
=======
void Dealer::getNewCount(){//GET NEW COUNT FOR COUNTING CARDS
>>>>>>> origin/master
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

<<<<<<< HEAD

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
=======
void Dealer::distributeWinnings(bool BJ){//UPDATE WINNINGS
  int dealerHand = p[0].hands[0].handTotal();
  int pHandTotal = 0;  
  float BJPayout = 3/2;//TABLE PAYS 3 TO 2 ON BLACKJACK
  avgWinnings = 0;
>>>>>>> origin/master

  for(int i = 0; i < totalPlayers; i++){//CHECK EVERY PLAYERS HAND
    for(int j = 0; j < p[i].handCount; j++){
      pHandTotal = p[i].hands[j].handTotal();

<<<<<<< HEAD
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
=======
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
>>>>>>> origin/master
    }
  }
<<<<<<< HEAD
=======

  avgWinnings /= totalPlayers - 1;//GET AVG WINNINGS 
>>>>>>> origin/master
}
