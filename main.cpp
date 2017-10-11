#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

using namespace std;

/*
* The shuffle funtion returns a random number between a min and a max.
*/
int shuffle(int min = 1, int max = 13){
    srand(time(NULL));
    return rand() % ((max-min) + 1) + min;
}
/*
 * The Role of the Wallet is to store the money of a player. It's basically a wrapper for math functions for sum,sub and some comparations. 
*/
class Wallet {
  int value = 50;

  public:
    // Resets the value back to 50
    void reset(){
      value = 50;
    }
    
	
	// Returns the value. Amount of cash in wallet
    int amount(){
      return value;
    }
	// Icreases the cash with a given amount
    void increase(int amount){
      value += amount;
    }

	// Decreases the cash with a given amount
    void decrease(int amount){
        value -= amount;
    }
    
	// There is this amount of cash in wallet? Checks if there are more or at least equal the amount given
    bool has(int amount){
      return value >= amount;
    }
    
	// This stricts compare the greater of the amount given
    bool greater(int amount){
      return value > amount;
    }
    // Check if the amount given is strictly lesser than cash amount
    bool lesser(int amount){
      return value < amount;
    }
    
    // A nice format disply for the cash
    string toString(){
      return "£"+to_string(value);
    }
    
	// Checks if the wallet is empty
    bool isEmpty(){
      return value <= 0;
    }
    // Checks if the wallet is not empty
    bool isNotEmpy(){
      return !isEmpty();
    }
  
};


class Player {
  
  private:
    string name;
  
  public:
	Wallet wallet;

   // Sets the player name
   void setName(string value){
     name = value;
   }

  // Returns the player name
  string getName(){
    return name;
  }
    
};
/*
* The AI extends the player the preserve the same functions as him, AI can have a name(they have a soul too, they deserve more)
*/
class AI : public Player {
  
  private:
	  // Some variables to store the ai performances so we can have a mood system, AI should talk based on his mood system
	  int countWins = 0; 
	  int countLosts = 0;
  
 // Returns a decision based on the given chance, defaults to a 50/50 chance. This is mainly used to pick a card
  bool getDecision(int chance = 50){
    return rand() % 100 < chance;
  }
  
  public:
  bool getPickDecision(int card){
    switch(card){
      case 1:    // If the current card is 1(Ace) the AI shall know that cannot be a lower card
        return true;
      case 2:	// There is a very small chance to get a lower card less than 2, so is like 90% chance to pick a higher card
        return getDecision(90);
      case 3:	// As the same as two, this time we assume like 80% chance to pick a higher card
        return getDecision(80);
      case 13:  // If the current card is 13(King) the AI shall know that cannot be a higher card
        return false;
      case 12:	// Same as 3, this time the opposite, there is a 10% chance to pick a higher card
        return getDecision(10);
      case 11: // Same as 12, with a 20% chance
        return getDecision(20);
	  default: // If is none from above, we default to a 50/50 chance
		  return getDecision(50);
    }
  }
  /*
  * The idea for the bet amount is to let the AI actually think how much he can bet based on his stats like: his current money, loses/wins, the current card.
  */
  int getBetAmount(Wallet wallet){
	 // TODO:: Not sure if to implement or not
  }
  
  /*
  * Returns AI's decision to bet or not based on his stats
  */
  bool wantsToBet(int defaultBet = 0, int loseBet = 0) {
	if(wallet.lesser(loseBet)){
        return getDecision(20);
    }
    
    return false;
  }
  /*
  * Returns a random message based on his mood. Mood is influenced by his wins/loses.
  */
  string talk(){
    //string[] messages;
    //messages[] = "You're lucky";
    //messages[] = "Better luck next time";
  }
  
};

/*
* The Deck class 
*/
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
      cout << "[OK] Yey! You have won the game with " << player.wallet.amount() << " in your wallet. Congrats!" << endl;
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
