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
* - If a player is right he gets full bet
* - If both players are right they get half of the bet
* - If the player is not right he loses cash
* - If the players don't pick the same answer they can bet/raise the reward for that round
* - Players can choose with what amount to start and set the increase/decrease bets
*/

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
  
    int amount(){
      return value;
    }
  
    void increase(int amount){
      value += amount;
    }
    
    void decrease(int amount){
        value -= amount;
    }
    
    bool has(int amount){
      return value >= amount;
    }
    
    bool greater(int amount){
      return value > amount;
    }
    
    bool lesser(int amount){
      return value < amount;
    }
    
    
    string toString(){
      return "£"+to_string(value);
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
  int countWins = 0;
  int countLosts = 0;
  
  bool getDecision(int chance = 50){
    return rand() % 100 < chance;
  }
  
  public:
  bool getPickDecision(int card){
    switch(card){
      case 1:    // If the current card is 1(Ace) the AI shall know that cannot be a lower card
        return true;
      case 2:
        return getDecision(90);
      case 3:
        return getDecision(80);
      case 13:        // If the current card is 13(King) the AI shall know that cannot be a higher card
        return false;
      case 12:
        return getDecision(10);
      case 11:
        return getDecision(20);
    }
    
    return getDecision(50);
  }
  
  int getBetAmount(Wallet wallet){
    // TODO:: Not sure if to implement
  }
  
  
  bool wantsToBet(int defaultBet = 0, int loseBet = 0) {
    if(wallet.lesser(loseBet)){
        return getDecision(20);
    }
    
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
        return to_string(number);
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
        cout << "[?] " << question << endl;
        cout << ">>> ";
        string option;
        cin >> option;
        return option;
    }
    
    bool confirm(string question){
      string option = ask(question + " (y/n): ");
      return option == "y" || option == "yes";
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
      cout << "[OK] " << name << " won " << to_string(amount) << endl;
    }
    
    void lost(string name, int amount){
      cout << "[X] " << name << " lost " << to_string(amount) << endl;
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


class Bet {
  
  private:
      int min = 10;
      int minLose = 0;
      int current = 10;
      int currentLose = 0;
      
  public:
    
    void set(int bet, int loseBet = 0){
      min = bet;
      minLose = loseBet;
      current = min;
      currentLose = loseBet;
    }
    
    void rise(int amount) {
      current += amount;
      currentLose += amount;
    }
    
    void reset() {
      current = min;
      currentLose = minLose;
    }
    
    int amount(){
      return current;
    }
    
    int halfAmount(){
      return current / 2;
    }
    
    int loseAmount(){
      return currentLose;
    }
  
};

class Game {
  private:
    bool keepAlive = true;
    int round = 0;

  public:
    Bet bet;
  
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
      bet.reset();
    }
    
   void reset(){
     round = 0;
   }

};

Output out;
Game game;
Deck deck;
Player player;
AI ai;

int main(){
  // SETUP
  player.setName(out.ask("What is your name? "));
  ai.setName("Player2");
  game.bet.set(stoi(out.ask("In what bet do yo want to play? ")), 40);
  // GAME LOOP
  while(game.isRunning()){
    // START A NEW ROUND
    game.newRound();
    deck.pick();
    cout << "Round " << game.getRound() << endl;
    out.header(player.getName() + " wallet: " + player.wallet.toString() + " | " + ai.getName() + " wallet: " + ai.wallet.toString());
    out.info("Card: ", deck.displayFirstCard());
    bool isHigher = out.confirm("The next card is higher?");
    bool aiHigher = ai.getPickDecision(deck.getFirstCard());
    out.picked(player.getName(), isHigher);
    out.picked(ai.getName(), aiHigher);
    
    // WANNA BET?
    if(isHigher != aiHigher){
      // CHECK WHO WANTS TO BET
      if(out.confirm(ai.getName() + " picked the opposite of you. Do you want to bet?") || ai.wantsToBet()) {
        string amount;
        // MAKE SURE EVERYONE IS ABLE TO PAY THAT AMOUNT
        do {
           amount = out.ask("With how much you want to raise the bet? ");
          if(stoi(amount) > player.wallet.amount()){
            out.warning("You don't have enough enough money to bet.");
          }
        } while(stoi(amount) > player.wallet.amount());
        out.info("Raising the amount with: ", amount);
        game.bet.rise(stoi(amount));
      }
    }
    
    // THE MOMENT OF TRUTH
    out.info("Second card was: ", deck.displaySecondCard());
    
    bool aiIsRight = deck.check(aiHigher);
    bool playerIsRight = deck.check(isHigher);

    // IF BOTH PLAYERS ARE RIGHT THEN WE SET THE BET AT HALF
    int bet = aiIsRight && playerIsRight ? game.bet.halfAmount() : game.bet.amount();
    int loseAmount = game.bet.loseAmount();
    
    // IS AI RIGHT OR WRONG?
    if(aiIsRight){
      ai.wallet.increase(bet);
      out.won(ai.getName(), bet);
    } else {
      ai.wallet.decrease(loseAmount);
      out.lost(ai.getName(), loseAmount);
    }
    
    // IS THE PLAYER RIGHT OR WRONG?
   if(playerIsRight) {
      player.wallet.increase(bet);
      out.won(player.getName(), bet);
    } else {
      player.wallet.decrease(loseAmount);
      out.lost(player.getName(), loseAmount);
    }
    
    // LET'S BREATH
    out.blank();
    deck.reset();
    
    // ARE YOU EVEN BROKE, BRO?
    if(ai.wallet.isEmpty()){
      cout << "[OK] Yey! You hav won the game with " << player.wallet.amount() << " in your wallet. Congrats!" << endl;
      game.exit();
    }
    
    if(player.wallet.isEmpty()){
       if(out.confirm("You're broke! You want to restart?")){
         player.wallet.reset();
         ai.wallet.reset();
         game.reset();
         deck.reset();
       } else {
         game.exit();
       }
    }
  }
  return 0;
}
