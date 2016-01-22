#include<iostream>
#include<vector>
#include<fstream>
#include"cards.h"
#include"player.h"
#include"dealer.h"
using namespace std;

void exportWinningHands(vector<int> winHands);//UPDATE AMOUNT OF WINNING HANDS FOR THIS ROUND
void exportCount(vector<int> count);//UPDATE COUNT FOR EACH ROUND OF CARDS
void exportAvgWin(vector<double> avgWin);//AVERAGE WINNINGS FOR HAND

int main(int argc, char* argv[]){
  if(argc < 3){
    cout<<"Command line should have 1:Players, 2:Decks, 3:Number of hands"<<endl;
    exit(1);
  }

  srand(time(NULL));//RANDOM NUMBER GENERATOR

<<<<<<< HEAD
  Dealer d(atoi(argv[1]), atoi(argv[2]));
  int hands = atoi(argv[3]);
=======
  Dealer d(4);//AMOUNT OF PLAYERS AT TABLE
  vector<double> avgWin;
  vector<int> winHands;
  vector<int> count;
>>>>>>> origin/master
  
  for(int i = 0; i < hands; i++){//FOR AMOUNT OF DEALS
    d.DealCards();
    d.nextPlayer();
  }
    
  d.displayAllHands();  //DISPLAY FINAL HANDS

  return 0;
}

<<<<<<< HEAD
void exportWinningHands(vector<int> winHands){//EXPORT WINNINGS TO TEXT FILE
=======
void exportWinningHands(vector<int> winHands){//AMOUNT OF WINNING HANDS FOR ROUND
>>>>>>> origin/master
  ofstream outFile;
  outFile.open("winHands.txt");

  for(int i = 0; i < winHands.size(); i++){
    outFile<<winHands[i]<<"\n";
  }

  outFile.close();
}

<<<<<<< HEAD
void exportCount(vector<int> count){//EXPORT COUNT TO TEXT FILE
=======
void exportCount(vector<int> count){//COUNT AFTER EACH ROUND
>>>>>>> origin/master
  ofstream outFile;
  outFile.open("count.txt");

  for(int i = 0; i < count.size(); i++){
    outFile<<count[i]<<"\n";
  }

  outFile.close();
}

<<<<<<< HEAD
void exportAvgWin(vector<double> avgWin){//EXPORT AVERAGE WINNINGS TO TEXT FILE
=======
void exportAvgWin(vector<double> avgWin){//AVERAGE WINNINGS FOR ROUND
>>>>>>> origin/master
  ofstream outFile;
  outFile.open("avgWin.txt");

  for(int i = 0; i < avgWin.size(); i++){
    outFile<<avgWin[i]<<"\n";
  }

  outFile.close();
}
