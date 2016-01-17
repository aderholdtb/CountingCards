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
  Player p[maxTable];//TABLE OF PLAYERS
  int totalPlayers;
  std::vector<std::string> aceDubs;//RULES FOR ACES AND DOUBLES
  std::vector<std::string> reg;//RULES FOR REGULAR HAND
  int count;//CARD COUNT
  double avgWinnings;
  int winningHands;

  Dealer(int players);
  ~Dealer();
  void DealCards();
  void nextPlayer();
  bool checkForShuffle();
  int aceDoublesHand(bool, int, int);//CHECK RULES FOR GIVEN HAND, ACE OR PAIR HAND
  int regular(int, int);//CHECK RULES FOR GIVEN HAND, REGUALR HAND
  int play(std::string p);//GET PLAY TYPE
  void displayAllHands();
  void distributeWinnings(bool);
  void getNewCount();
};

#endif
