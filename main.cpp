#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

string Str(int value){
  return std::to_string(value);
}
int random(int min = 1, int max = 13){
    srand(time(NULL));
    return rand() % ((max-min) + 1) + min;
}
class Wallet {
  int value = 100;
  int incBy = 50;
  int decBy = 40;
  
  public:
    int getValue(){
      return value;
    }
    
    int increaseRate(){
      return incBy;
    }
    
    int decreaseRate(){
      return decBy;
    }
    
    void increase(){
      value += incBy;
    }
    
    void decrease(){
      value -= decBy;
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

class AI : Player {
  
  private:
    string mood = "default";
  
  public:

  bool affirmative(){
      int chance = random(1, 100);
      return chance > 50;
  }
  
  
  bool getPickDecision(int card){
    // If the current card is 1(Ace) the AI shall know that cannot be a lower card
    if(card == 1 ){
      return true;
    }
    // If the current card is 13(King) the AI shall know that cannot be a higher card
    if(card == 13){
      return false;
    }
  }
  
  bool getBetDecision(){
   // Must implement the AI to choose if to bet, if yes than how much
  }
  
  bool talk(){
    // implement AI to send messages to player according his mood
  }
  
  void setMood(string value){
     mood = value;
  }
  
  string getMood(){
    return mood;
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
      firstCard = random();
      do {
        secondCard = random();
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
};


class Game {
  private:
    bool keepAlive = true;
    int round = 0;
   
    
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
    }
    
   
};
Output out;
Game game;
Deck deck;
Player player;
Player player2;
int main(){

  while(game.isRunning()){
    game.newRound();
    deck.pick();
    cout << "Round " << game.getRound() << endl;
    out.divider(30);
    cout << "Your wallet: " << player.wallet.getValue();
    cout << " | Player2 wallet: " << player2.wallet.getValue() << endl;
    out.divider(30);
    out.info("Card: ", deck.displayFirstCard());
    bool isHigher = out.confirm("The next card is higher?");
    
    out.blank();
    out.info("Second card was: ", deck.displaySecondCard());
   if(deck.check(isHigher)) {
      player.wallet.increase();
      cout << "[OK] You're lucky! You've won " << player.wallet.increaseRate() << endl;
    } else {
      player.wallet.decrease();
      cout << "[X] Better luck next time! You've lost " << player.wallet.decreaseRate() << endl;
    }
    out.blank();
    
    deck.reset();
    if(player.wallet.isEmpty()){
       if(out.confirm("You're broke! You want to restart?")){
         // restart game
       } else {
         game.exit();
       }
    }
  }
  return 0;
}