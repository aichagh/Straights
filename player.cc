#include "player.h"
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

// constructor
Player::Player(Game * gameptr, bool CPU, int playerNum) :
	gameptr{gameptr}, scoreSoFar{0}, CPU{CPU}, playerNum{playerNum}
{
	gameptr->attach(this);
}

// destructor
Player::~Player() {
	gameptr->detach(this);
}

// prints the result of the addition of the score from the last round and the score of the current round
void Player::printScore(int total) {
	std::cout << "Player" << playerNum << "'s discards: ";
	for (int i = 0; i < discardPile.size(); i++) {
		std::cout << " " << discardPile[i];
	}
	std::cout << std::endl << "Player" << playerNum << "'s score: ";
	std::cout << total - scoreSoFar << " + " << scoreSoFar << " = " << total << std::endl;
}

// deals the ith sequence of 13 cards in the deck (eg: player1 gets the first 13 cards)
void Player::deal() {
	for (int i = 13 * (playerNum - 1); i < 13 * playerNum; i++) {
                hand.emplace_back(gameptr->getCard(i));
        }
}

// resets the discard pile and the score before the next round begins
void Player::resetPlayer() {
	for (int i = 0; i < discardPile.size(); i++) {
		discardPile.erase(discardPile.begin() + i);
	}
	scoreSoFar = 0;
}

// returns the current score of the round
int Player::getScore() { return scoreSoFar; }

// removes 'card' from the hand and places it on the discard pile
void Player::discard(std::string card) {
	// adding the card to the discard pile
	discardPile.emplace_back(card);
	
	// removing the card from the hand
	for (int i = 0; i < hand.size(); i++) {
		if (hand[i] == card) {
			hand.erase(hand.begin() + i);
		}	
	}

	// updates the score according to the rank
	char rank = card[0];
        if (rank == 'A') { scoreSoFar += 1; }
        else if (rank == 'T') { scoreSoFar += 10; }
        else if (rank == 'J') { scoreSoFar += 11; }
        else if (rank == 'Q') { scoreSoFar += 12; }
        else if (rank == 'K') { scoreSoFar += 13; }
        else { scoreSoFar += rank - '0'; }
}

// removes 'card' from the hand then places it on the table
void Player::play(std::string card) {
	char rank = card[0];
	char suit = card[1];
	int suitInt;

	for (int i = 0; i < 4; i++) {
		if (suit == 'C') {
			suitInt = 0;
		} else if (suit == 'D') {
			suitInt = 1;
		} else if (suit == 'H') {
			suitInt = 2;
		} else {
			suitInt = 3;
		}
	}

	if (rank == 'A') {
                gameptr->setSuit(0, suitInt);
        } else if (rank == 'T') {
                gameptr->setSuit(9, suitInt);
        } else if (rank == 'J') {
                gameptr->setSuit(10, suitInt);
        } else if (rank == 'Q') {
                gameptr->setSuit(11, suitInt);
        } else if (rank == 'K') {
                gameptr->setSuit(12, suitInt);
        } else {
                int rankInt = rank - '0' - 1;
                gameptr->setSuit(rankInt, suitInt);
        }

	// removing the card from the hand
	for (int i = 0; i < hand.size(); i++) {
                if (hand[i] == card) {
                        hand.erase(hand.begin() + i);
                }
        }

}

// determines if 'card' is a legal play
bool Player::isLegal(std::string card) { 
	char rank = card[0];
	char suit = card[1];
	int suitInt;
	int rankInt;

	if (rank == 'A') { rankInt = 0; } 
	else if (rank == 'T') { rankInt = 9; }
	else if (rank == 'J') { rankInt = 10; } 
	else if (rank == 'Q') { rankInt = 11; } 
	else if (rank == 'K') { rankInt == 12; } 
	else { rankInt = rank - '0' - 1; }


	if (suit == 'C') { suitInt = 0; } 
	else if (suit == 'D') { suitInt = 1; } 
	else if (suit == 'H') { suitInt = 2; } 
	else if ((suit == 'S') && (rankInt == 6)) {
		return true;
	} else if (rankInt == 0) {
		return gameptr->getSuit(rankInt + 1, 3);
	} else if (rankInt == 12) {
		return gameptr->getSuit(rankInt - 1, 3);
	} else {
		return (gameptr->getSuit(rankInt - 1, 3) || gameptr->getSuit(rankInt + 1, 3));
	}

	if (rankInt == 0) {
		return (gameptr->getSuit(rankInt, 3) && gameptr->getSuit(rankInt + 1, suitInt));
	} else if (rankInt == 12) {
		return (gameptr->getSuit(rankInt, 3) && gameptr->getSuit(rankInt - 1, suitInt));
	} else if (rankInt == 6) {
		return gameptr->getSuit(rankInt, 3);
	} else {
		return (gameptr->getSuit(rankInt, 3) && ((gameptr->getSuit(rankInt - 1, suitInt) || gameptr->getSuit(rankInt + 1, suitInt))));
	}
}

// returns a vector of all the legal plays
std::vector <std::string> Player::legalPlays() {
	std::vector <std::string> allLegalPlays;
	for (int i = 0; i < hand.size(); i++) {
		if (this->isLegal(hand[i])) {
			allLegalPlays.emplace_back(hand[i]);
		}
	}
	return allLegalPlays;
}

// changes the player to a computer (CPU)
void Player::changeCPU() { CPU = true; }

// determines if the player has the 7 of Spades in hand
bool Player::has7S() {
	for (int i = 0; i < hand.size(); i++) {
		if (hand[i] == "7S") {
			return true;
		}
	}
	return false;
}

// determines if 'card' is in the hand
bool Player::cardInHand(std::string card) {
	for (int i = 0; i < hand.size(); i++) {
                if (hand[i] == card) {
                        return true;
                }
        }
        return false;
}


// notify
void Player::notify() {
   // if this player is a CPU, it plays the first card that can be played.
   // If no legal plays are possible, it discards the first card in the hand.
   
   if (this->CPU) {
      
      std::vector <std::string> plays = this->legalPlays();
      if (plays.size() != 0) {
	 std::cout << "Player" << this->playerNum << " plays " << plays[0] << "." <<  std::endl;
         this->play(plays[0]);
      } else {
	 std::cout << "Player" << this->playerNum << " discards " << hand[0] << "." << std::endl;
         this->discard(hand[0]);
      }

   } else { // if the player is human
      
      std::cout << "Your hand:";
      for (int i = 0; i < hand.size(); i++) {
         std::cout << " " << hand[i];
      }
      std::vector <std::string> plays = this->legalPlays();
      std::cout << std::endl << "Legal plays:";
      for (int i = 0; i < plays.size(); i++) {
	      std::cout << " " << plays[i];
      }
      std::cout << std::endl;

      std::string command, card;
      bool move = false;

      while(!move) {

	 std::cin >> command;
         
	 if (command == "quit") {
            gameptr->gameIsOver(); 
            break;
         }

         else if (command == "play") {
            std::cin >> card;
            if (!(this->isLegal(card))) {
               std::cout << "This is not a legal play." << std::endl;
            } else if (this->cardInHand(card)) {
                this->play(card);
	        std::cout << "Player" << this->playerNum << " plays " << card << "." << std::endl;
	    	move = true;
	    } else {
		std::cout << "This card is not in your hand." << std::endl;
	    }
	 }

         else if (command == "discard") {
            std::cin >> card;
	    std::vector <std::string> plays = this->legalPlays();

	    if (plays.size() != 0) {
	       std::cout << "You have a legal play. You may not discard." << std::endl;
	    } 
	    
	    else if (this->cardInHand(card)) {
	       this->discard(card);
               std::cout << "Player" << this->playerNum << " discards " << card << "." << std::endl;
	       move = true;
	    } else {
	       std::cout << "This card is not in your hand. You may not discard it." << std::endl;
	    }
	 }

         else if (command == "deck") {
            // print the deck
	    gameptr->printDeck();
         }

         else if (command == "ragequit") {
	    // change the current player to a CPU
	    std::cout << "Player" << this->playerNum << " ragequits. A computer will now take over." << std::endl;
	    this->changeCPU();
	    move = true;

         } else {
            std::cout << "This is not a valid command." << std::endl;
	 }
      }
   }
}
