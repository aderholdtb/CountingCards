#ifndef DEALER_H
#define DEALER_H
#include<vector>
#include<string>
#include"player.h"
#include"cards.h"
#include"hand.h"

const int maxTable = 5;
const int counters = 4;

class Dealer : public Player , public Deck{
 public:
  Player p[maxTable];//PLAYERS
  int totalPlayers;//TOTAL PLAYERS
  std::vector<std::string> aceDubs;//BLACKJACK CARD FOR ACE AND PAIRS 
  std::vector<std::string> reg;//BLACKJACK CARD FOR REGUALR HAND
  double count[counters];//COUNTS
  double avgWinnings;//AVERAGE WINNINGS PER ROUND
  int winningHands;//NUMBER OF WINNING HANDS

  Dealer(int players, int decks);
  ~Dealer();
  void DealCards();//DEAL CARDS TO EACH PLAYER
  void nextPlayer();//NEXT PLAYERS TURN
  bool checkForShuffle();//CHECK FOR A SHUFFLE
  int aceDoublesHand(bool, int, int);//IF ACE OR PAIR IN HAND
  int regular(int, int);//IF REGULAR HAND
  int play(std::string p);//GET PLAY TYPE
  void displayAllHands();
  void distributeWinnings(bool);//CHECK PLAYERS HANDS
  void getNewCount();//UPDATE COUNTS
  int getPlay(int, int, int);//GET PLAY TYPE FOR HAND
  void keepPlaying(int, int, int, int);//IF KEEP HITTING
  void hiLowCount(int);//UPDATE COUNTS
  void redSevenCount(int);
  void omegaCount(int);
  void wongHalves(int);
  void payOut(int, int, bool, bool);//PAY THE PLAYERS
};

#endif