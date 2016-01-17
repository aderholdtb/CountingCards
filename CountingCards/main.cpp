#include<iostream>
#include<vector>
#include<fstream>
#include<ctime>
#include"cards.h"
#include"player.h"
#include"dealer.h"
using namespace std;

void exportWinningHands(vector<int> winHands);//UPDATE AMOUNT OF WINNING HANDS FOR THIS ROUND
void exportCount(vector<int> count);//UPDATE COUNT FOR EACH ROUND OF CARDS
void exportAvgWin(vector<double> avgWin);//AVERAGE WINNINGS FOR HAND

int main(){
  srand(time(NULL));

  Dealer d(4);//AMOUNT OF PLAYERS AT TABLE
  vector<double> avgWin;
  vector<int> winHands;
  vector<int> count;
  
  for(int i = 0; i < 1000; i++){
    d.DealCards();
    d.nextPlayer();

    winHands.push_back(d.winningHands);
    count.push_back(d.count);
    avgWin.push_back(d.avgWinnings);
  }
  
  exportWinningHands(winHands);
  exportCount(count);
  exportAvgWin(avgWin);
    
    d.displayAllHands();  

  return 0;
}

void exportWinningHands(vector<int> winHands){//AMOUNT OF WINNING HANDS FOR ROUND
  ofstream outFile;
  outFile.open("winHands.txt");

  for(int i = 0; i < winHands.size(); i++){
    outFile<<winHands[i]<<"\n";
  }

  outFile.close();
}

void exportCount(vector<int> count){//COUNT AFTER EACH ROUND
  ofstream outFile;
  outFile.open("count.txt");

  for(int i = 0; i < count.size(); i++){
    outFile<<count[i]<<"\n";
  }

  outFile.close();
}

void exportAvgWin(vector<double> avgWin){//AVERAGE WINNINGS FOR ROUND
  ofstream outFile;
  outFile.open("avgWin.txt");

  for(int i = 0; i < avgWin.size(); i++){
    outFile<<avgWin[i]<<"\n";
  }

  outFile.close();
}
