#include <random>
#include <sstream>
#include <iostream>
#include <algorithm>
#include "gamestate.h"

extern std::default_random_engine rng;

// shuffles the deck
void gameState::deckShuffle() {
	std::shuffle(fullDeck.begin(), fullDeck.end(), rng);
}

// resets the card on the table
void gameState::resetGame() {
	for (int i = 0; i < 13; i++) {
                for (int j = 0; j < 4; j++) {
                        suits[i][j] = false;
                }
        }
}

// constructor
gameState::gameState() : 
	 isGameOver{false}
{
	// storing the deck in order
	for (int i = 0; i < 4; i++) {
		std::string suit;
		
		if (i == 0) { suit = "C"; } 
		else if (i == 1) { suit = "D"; }
		else if (i == 2) { suit = "H"; }
		else { suit = "S"; }

		for (int j = 1; j <= 13; j++) {
			std::string card;
			
			if (j == 1) { card = "A" + suit; }
			else if (j == 10) { card = "T" + suit; }
			else if (j == 11) { card = "J" + suit; }
			else if (j == 12) { card = "Q" + suit; }
			else if (j == 13) { card = "K" + suit; }
			else {
			       	std::string rank = std::to_string(j);
				card = rank + suit;
			}	
			
			fullDeck.emplace_back(card);
		}
	}

	// initializing the Suit array
	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 4; j++) {
			suits[i][j] = false;
		}
	}
}

// prints the deck
void gameState::printDeck() {
	for(int i = 0; i < 4; i++) {
		for(int j = i * 13; j < (i + 1) * 13; j++) {
			std::cout << " " << fullDeck[j];
		}
		std::cout << std::endl;
	}
}

// returns the pos'th card of the deck
std::string gameState::getCard(int pos) { return fullDeck[pos]; }

// returns true if the card of rank 'rank' and suit 'suit' has been placed on the table and false otherwise
bool gameState::getSuit(int rank, int suit) { return suits[rank][suit]; }

// sets that the card of rank 'rank' and suit 'suit' has been placed on the table
void gameState::setSuit(int rank, int suit) { suits[rank][suit] = true; }

// determines if the game is over
bool gameState::gameOver() { return isGameOver; }

// sets that the game is over
void gameState::gameIsOver() { isGameOver = true; }

// returns a vector of the scores from the previous round
int * gameState::getScores() { return currentScores; }

// updates the score of player playerNum by adding val
void gameState::updateScore(int val, int playerNum) { currentScores[playerNum] += val; }

// sets that a player has had a score of 80 or above
void gameState::setOver80() { scoreOver80 = true; }

// returns true if a player has had a score of 80 or above
bool gameState::isOver80() { return scoreOver80; }

// prints the card with rank 'rank' and suit 'suit'
void gameState::printCard(int rank, int suit) {
	if (suits[rank][suit]) {
		std::cout << " ";
		if (rank == 0) {
			std::cout << "A";
		} else if (rank == 9) {
			std::cout << "T";
		} else if (rank == 10) {
			std::cout << "J";
		} else if (rank == 11) {
			std::cout << "Q";
		} else if (rank == 12) {
			std::cout << "K";
		} else {
			std::cout << rank + 1;
		}
	}
}
