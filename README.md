# High-Low Card
> A player is show a random playing card, then asked to decide whether the next card will be "higher" or "lower". If the guess is correct the player is awarded with a 'cash' price.

![Flowchart](https://github.com/codrin-axinte/High-Low-Card/blob/master/High-Low%20Card%20Flowchart.png)
One to two paragraph statement about your product and what it does.

### Rules:
  * The first with no cash loses
  * If a player is right he gets full bet
  * If both players are right they get half of the bet
  * If the player is not right he loses cash
  * If the players don't pick the same answer they can bet/raise the reward for that round
  * Players can choose with what amount to start and set the increase/decrease bets

## Installation
OS X & Linux:
```sh
g++ -Wall main.cpp -o highlowcard
```
*-Wall and -W
    When compiling with g++, the options -Wall and -W include extra warnings specific to C++ (the warnings relate to member functions and virtual classes). The use of these options is always recommended while developing a program.*

Windows:
```
 Run the executable
```

## Usage example

The game is based on the players intuition to bet if the next card will be higher. 
On the game start the player is asked to set a default winning bet to play. This amount will be given to the player if he guessed right, however if it's wrong then a the half amount of the default bet will be withdrawn from his wallet. To make the game more engaging there is a `raise bet` event which is triggered if players chosed opposite options then they can raise the bet.

### User Stories:
 *As a player I would like...*
  * To enter my name
  * The game to be easy to play and engaging
  * To be rewarded if my answer is right
  * To be able to play against an AI

### Possible Future Extensions
    * AI can choose to bet their own amount
    * AI outputs a message based on their mood.
    * On game start it is a dice roll to decide which player goes first. This improves the bet system.
    * Play against another player online
    * Have some stats about player last games(Wins/Loses, Biggest played bet)
    * A player vault which holds the players total money. If the vaults empty, the player needs a real payment recharge.
*\* There so many things that can be done for such a small game, I could write an entire page.*

## Release History
* 1.0.2
    * Added bet feature
    * Player can play against AI
* 0.1.0
    * The first proper release
* 0.0.1
    * Work in progress

## Meta

Codrin Axinte – [@LinkedIn](https://www.linkedin.com/in/codrin-axinte-93776814b/) – xntcodrin@yahoo.com – loopbytes@yahoo.com

Distributed under the XYZ license. See ``LICENSE`` for more information.

[https://github.com/codrin-axinte](https://github.com/codrin-axinte)

## Contributing

1. Fork it (<https://github.com/codrin-axinte/yourproject/fork>)
2. Create your feature branch (`git checkout -b feature/fooBar`)
3. Commit your changes (`git commit -am 'Add some fooBar'`)
4. Push to the branch (`git push origin feature/fooBar`)
5. Create a new Pull Request
