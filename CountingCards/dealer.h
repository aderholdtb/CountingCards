#ifndef DEALER_H
#define DEALER_H
#include<vector>
#include<string>
#include"player.h"
#include"cards.h"
#include"hand.h"

const int maxTable = 5;

class Dealer : public Player , public Deck{
 public:
  Player p[maxTable];
  int totalPlayers;
  std::vector<std::string> aceDubs;
  std::vector<std::string> reg;
  int count;
  double avgWinnings;
  int winningHands;

  Dealer(int players);
  ~Dealer();
  void DealCards();
  void nextPlayer();
  bool checkForShuffle();
  int aceDoublesHand(bool, int, int);
  int regular(int, int);
  int play(std::string p);
  void displayAllHands();
  void distributeWinnings(bool);
  void getNewCount();
};

#endif