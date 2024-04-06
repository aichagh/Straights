#ifndef _GAME_H_
#define _GAME_H_

#include <vector>
#include <string>
#include "observer.h"

class Observer;

class Game {
		std::vector <Observer *> observers;
	public:
		void attach(Observer * o);
		void detach(Observer * o);
		virtual void printDeck() = 0;
		virtual std::string getCard(int pos) = 0;
		virtual bool getSuit(int rank, int suit) = 0;
		virtual void setSuit(int rank, int suit) = 0;
		virtual int * getScores() = 0;
		virtual void printCard(int rank, int suit) = 0;
		virtual bool gameOver() = 0;
		virtual void gameIsOver() = 0;
		virtual void setOver80() = 0;
		virtual bool isOver80() = 0;
                virtual void deckShuffle() = 0;	
		virtual void resetGame() = 0;
		void win();
		void printAllScores();
		virtual void updateScore(int val, int playerNum) = 0;
		virtual ~Game() = default;	
		void notifyObserver(int n);
};

#endif

