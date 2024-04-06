#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <random>

#include "player.h"
#include "table.h"
#include "observer.h"
#include "game.h"
#include "gamestate.h"

std::default_random_engine rng;

int main (int argc, char *argv[]) {
	// setting up the seed
	int seed;

	if (argc == 2) {
		std::istringstream ss(argv[1]);
		if (!(ss >> seed)) {
  			std::cout << "Invalid seed" << std::endl;
			return 1;
		}
	} else {
		srand((unsigned) time(0));
		seed = std::rand();
	}
	
	std::default_random_engine temp(seed);
	rng = temp;

	// setting up the variables
	Game * game = new gameState;

	std::string command, card;
	std::vector <Observer *> obs;

	// determine which players are human and which are CPU:
	
	for (int i = 1; i <= 4; i++) {
	   do {
	   std::cout << "Is Player" << i << " a human (h) or a computer (c)?" << std::endl;
	   std::cin >> command;
	   }
	   while (!(command == "h" || command == "c"));
		
	   // making the player
	   if (command == "h") {
	      Observer *p = new Player {game, false, i};
	      obs.emplace_back(p);
	   } else {
	      Observer *p = new Player {game, true, i};
	      obs.emplace_back(p);
	   }
	}
	
	Observer *t = new Table {game};
	obs.emplace_back(t);

	// game starts
	while (!game->gameOver() && !game->isOver80()) {

	  game->deckShuffle();
	  for (int i = 0; i < 4; i++) {
		  obs[i]->deal();
	  }
	  std::cout << "A new round begins. ";
	  
	  // finding which player goes first (i.e. the one with the 7 of Spades)
	   int currentPlayer = 0;
	   for (int i = 0; i < 4; i++) {
	      if (obs[i]->has7S()) {
  	 	 currentPlayer = i;
		 std::cout << "It’s Player" << i + 1 << "’s turn to play." << std::endl;
		 break;
	      }
	   }

	   // round start; a round ends when all players have played all 13 cards in hand
           game->notifyObserver(currentPlayer);
	}

	// if any player scores over 80 points, the game ends
	if (game->isOver80()) {
	   game->win();	   
	}

	for (auto n:obs) {
	   delete n;
        }
}
