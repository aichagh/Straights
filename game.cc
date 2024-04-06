#include "game.h"
#include <iostream>

// constructor
void Game::attach(Observer *o) { observers.emplace_back(o); }

// destructor
void Game::detach(Observer *o) {
  for (auto it = observers.begin(); it != observers.end(); ) {
    if (*it == o) it = observers.erase(it);
    else ++it;
  }
}

// notifies all the observers
void Game::notifyObserver(int n) {
   for (int j = 0; (j < 13 && !this->gameOver()); j++) {
      for (int i = 0; (i < 4) && !(this->gameOver()); i++) {
         observers[4]->notify();
         observers[n]->notify();
         n = (n + 1) % 4;
      }
   }

   for (int i = 0; i < 4; i++) {
      this->updateScore(observers[i]->getScore(), i);
   }

   int * scores = this->getScores();
   for (int i = 0; i < 4; i++) {
	   if (scores[i] >= 80) {
		this->setOver80();
		break;
	   }
   }

   if (!this->gameOver()) {
      this->printAllScores();
      this->resetGame();
      for(int i = 0; i < 4; i++) {
         observers[i]->resetPlayer();
      }
  }
}

// prints the scores of the current round
void Game::printAllScores() {
   int * scores = this->getScores();
   for (int i = 0; i < 4; i++) {
      observers[i]->printScore(scores[i]);
   }
}

// determines the winner
void Game::win() {
   std::vector <int> winners;
   int * scores = this->getScores();
   int minScore = scores[0];
   for (int i = 0; i < 4; i++) {
      if (scores[i] < minScore) {
	      minScore = scores[i];
      }
   }

   for (int i = 0; i < 4; i++) {
	   if (scores[i] == minScore) {
		   winners.emplace_back(i);
	   }
   }

   for (int i = 0; i < winners.size(); i++) {
      std::cout << "Player" << winners[i] + 1 << " wins!" <<  std::endl;
   }
}
