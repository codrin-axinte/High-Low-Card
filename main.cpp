#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

/*
* User Stories:
* As a user I would like the game to be easy to play
* As a user I woul like to be rewarded if my answer is right
* As a user I should be able to play alone or with an AI
* As a user I would like to enter my name
* Rules:
* - The first with no cash loses
* - If a player is right he gets full cash
* - If both players are right they both get full cash
* - If the player is not right he loses cash
* - If the players don't pick the same answer they can bet/raise the reward for that round
* - Players can choose with what amount to start and set the increase/decrease rates
*/

string Str(int value){
  return std::to_string(value);
}
int Num(string value){
  return std::stoi( value );
}

int shuffle(int min = 1, int max = 13){
    srand(time(NULL));
    return rand() % ((max-min) + 1) + min;
}
class Wallet {
  int value = 50;

  public:
    
    void reset(){
      value = 50;
    }
    
    int getValue(){
      return value;
    }
  
    void increase(int amount){
      value += amount;
    }
    
    void decrease(int amount){
        value -= amount;
    }
    
    bool isEmpty(){
      return value <= 0;
    }
    
    bool isNotEmpy(){
      return !isEmpty();
    }
  
};

class Player {
  
  private:
    string name;
  
  public:
   Wallet wallet;
   
   void setName(string value){
     name = value;
   }
   
  string getName(){
    return name;
  }
    
};

class AI : public Player {
  
  private:
  bool getDecision(int chance = 50){
    return rand() % 100 < chance;
  }
  
  public:
  bool getPickDecision(int card){
    switch(card){
      // If the current card is 1(Ace) the AI shall know that cannot be a lower card
      case 1:
        return true;
        // If the current card is 13(King) the AI shall know that cannot be a higher card
      case 13:
        return false;
      case 12:
        return getDecision(10);
      case 11:
        return getDecision(20);
    }
    
    return getDecision(50);
  }
  
  bool getBetDecision(){
    
    
  }
  
  bool wantsToBet(){
    return false;
  }
  
  string talk(){
    //string[] messages;
    //messages[] = "You're lucky";
    //messages[] = "Better luck next time";
  }
  
};


class Deck {
  private:
    int firstCard = 0;
    int secondCard = 0;
   public:
    string display(int number){
     if(number > 1 && number <= 10){
        return Str(number);
      }
  
      switch(number){
        case 1:
          return "Ace";
        case 11:
          return "Jack";
        case 12:
          return "Queen";
        case 13:
          return "King";
      }
      
  }
   
  bool check(bool isHigher = true){
    if(isHigher){
      return  secondCard > firstCard;
    }
    
    return secondCard < firstCard;
  }
  
  int getFirstCard(){
    return firstCard;
  }
  int getSecondCard(){
    return secondCard;
  }
  
  string displayFirstCard(){
    return display(firstCard);
  }
  
  string displaySecondCard(){
    return display(secondCard);
  }
  
  void reset(){
    firstCard = 0;
    secondCard = 0;
  }
    
  void pick(){
      firstCard = shuffle();
      do {
        secondCard = shuffle();
      } while(secondCard == firstCard);
  }  
};

class Output {
  
  public:
    string ask(string question){
        cout << "[?] " << question;
        string option;
        cin >> option;
        return option;
    }
    
    bool confirm(string question){
      string option = ask(question + " (y/n): ");
      
      return option == "y" || option == "Y" || option == "1" || option == "yes";
    }
    
    
    void info(string message, string value){
      cout << "[-] " << message << value << endl;
    }
    
    void warning(string message){
      cout << "[!] " << message << endl;
    }
    
    void blank(int length = 2){
     for(int i=0; i < length; i++){
        cout << endl;
      }
    }
    
    void divider(int length = 15){
      for(int i=0; i < length; i++){
        cout << "=";
      }
      cout << endl;
    }
    
    void won(string name, int amount){
      cout << "[OK] " << name << " won " << Str(amount) << endl;
    }
    
    void lost(string name, int amount){
      cout << "[X] " << name << " lost " << Str(amount) << endl;
    }
    
    void picked(string name, bool pick){
      info(name + " picked: ", pick ? "Higher" : "Lower");
    }
    
    void header(string message){
      int len = message.length();
      divider(len);
      cout << message << endl;
      divider(len);
    }
};

class Game {
  private:
    bool keepAlive = true;
    int round = 0;
    int bet = 50;
    int loseBet = 40;
    int roundBet = 0;
  public:
    bool isRunning(){
      return keepAlive;
    }
    
    void exit(){
      keepAlive = false;
    }
    
    int getRound(){
      return round;
    }
    
    void newRound(){
      round++;
      roundBet = bet;
    }
    
   void reset(){
     round = 0;
   }
   
   void setBet(int amount){
    bet = amount;
    roundBet = bet;
   }
   
   void setLoseBet(int amount){
     loseBet = amount;
   }
   
   void raiseBet(int amount){
     roundBet += amount;
   }
   
   
   int getBet(){
     return roundBet;
   }
   
   int getLoseBet(){
     return loseBet;
   }
};
Output out;
Game game;
Deck deck;
Player player;
AI ai;
int main(){
  game.setBet(50);
  game.setLoseBet(0);
  player.setName("Player1");
  ai.setName("Player2");
  while(game.isRunning()){
    game.newRound();
    deck.pick();
    cout << "Round " << game.getRound() << endl;
    string header = player.getName() + " wallet: " + Str(player.wallet.getValue()) + " | " + ai.getName() + " wallet: " + Str(ai.wallet.getValue());
    out.header(header);
    out.info("Card: ", deck.displayFirstCard());
    bool isHigher = out.confirm("The next card is higher?");
    bool aiHiger = ai.getPickDecision(deck.getFirstCard());
    out.picked(player.getName(), isHigher);
    out.picked(ai.getName(), aiHiger);
    if(isHigher != aiHiger){
      // Player can bet
      if(out.confirm(ai.getName() + " picked the opposite of you. Do you want to bet?")){
        string amount = out.ask("With how much you want to raise the bet? ");
        out.info('Raising the amount with: ', amount);
        game.riseBet(Num(amount));
      } else if(ai.wantsToBet()) {
        // Now the Ai wants a bet
      }
    }
    out.info("Second card was: ", deck.displaySecondCard());
    int bet = game.getBet();
    if(deck.check(aiHiger)){
      ai.wallet.increase(bet);
      out.won(ai.getName(), bet);
    } else {
      ai.wallet.decrease(game.getLoseBet());
      out.lost(ai.getName(), game.getLoseBet());
    }
  
   if(deck.check(isHigher)) {
      player.wallet.increase(bet);
      out.won(player.getName(), bet);
    } else {
      player.wallet.decrease(game.getLoseBet());
      out.lost(player.getName(), game.getLoseBet());
    }
    out.blank();
    
    deck.reset();
    if(player.wallet.isEmpty()){
       if(out.confirm("You're broke! You want to restart?")){
         player.wallet.reset();
         ai.wallet.reset();
         game.reset();
         deck.reset();
         // restart game
       } else {
         game.exit();
       }
    }
  }
  return 0;
}