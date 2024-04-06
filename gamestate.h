#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#include "game.h"
#include <string>
#include <vector>

class gameState: public Game {
		// private fields
	        int seed;
		bool isGameOver;
		std::vector <std::string>fullDeck;
		bool suits[13][4];
		int currentScores[4];
		bool scoreOver80;

		// private methods
		bool getSuit(int rank, int suit);
		std::string getCard(int pos);
		void setSuit(int rank, int suit);
	public:
		gameState();
		void printDeck();
		bool gameOver();
		void gameIsOver();
		int * getScores();
		void setOver80();
		bool isOver80();
		void deckShuffle();
		void resetGame();
		void printCard(int rank, int suit);
		void updateScore(int val, int playerNum);
};

#endif
