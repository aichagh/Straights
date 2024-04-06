#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <string>
#include "observer.h"
#include "gamestate.h"

class Observer;

class Player : public Observer {
		Game * gameptr;
		int scoreSoFar;
		std::vector <std::string> hand;
		std::vector <std::string> discardPile;
		bool CPU;
		int playerNum;	

	public:
		Player(Game * gameptr, bool CPU, int playerNum);		
		void discard(std::string card);
		void play(std::string card);
		bool isLegal(std::string card);
		std::vector <std::string> legalPlays();
		void changeCPU();
		bool cardInHand(std::string card);
		bool has7S() override;
		void notify() override;
		int getScore();
		void setScore(int n);
		void deal();
		void resetPlayer();
		void printScore(int total);
		~Player();
};

#endif
