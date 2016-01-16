#include<iostream>
#include<vector>
#include<fstream>
#include<ctime>
#include"cards.h"
#include"player.h"
#include"dealer.h"
using namespace std;

void exportWinningHands(vector<int> winHands);
void exportCount(vector<int> count);
void exportAvgWin(vector<double> avgWin);

int main(){
  srand(time(NULL));

  Dealer d(4);
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

void exportWinningHands(vector<int> winHands){
  ofstream outFile;
  outFile.open("winHands.txt");

  for(int i = 0; i < winHands.size(); i++){
    outFile<<winHands[i]<<"\n";
  }

  outFile.close();
}
void exportCount(vector<int> count){
  ofstream outFile;
  outFile.open("count.txt");

  for(int i = 0; i < count.size(); i++){
    outFile<<count[i]<<"\n";
  }

  outFile.close();
}
void exportAvgWin(vector<double> avgWin){
  ofstream outFile;
  outFile.open("avgWin.txt");

  for(int i = 0; i < avgWin.size(); i++){
    outFile<<avgWin[i]<<"\n";
  }

  outFile.close();
}
