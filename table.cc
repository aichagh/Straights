#include "table.h"
#include <iostream>

// constructor
Table::Table(Game * gameptr) : 
	gameptr{gameptr}
{ 
	gameptr->attach(this);
}

// these functions are empty because they must be overriden by all concrete observers
bool Table::has7S() { return true; }
int Table::getScore() { return 0; }
void Table::deal() {}
void Table::resetPlayer() {}
void Table::printScore(int total) {}

// destructor
Table::~Table() { gameptr->detach(this); }

// notify; prints the cards on the table; i.e. the cards that have been played.
void Table::notify() {
	std::cout << "Cards on the table:" << std::endl;
	std::cout << "Clubs:";
	for (int i = 0; i < 13; i++) {
		gameptr->printCard(i, 0);
	}
	std::cout << std::endl;
	std::cout << "Diamonds:";
        for (int i = 0; i < 13; i++) {
                gameptr->printCard(i, 1);
        }
	std::cout << std::endl;
	std::cout << "Hearts:";
        for (int i = 0; i < 13; i++) {
                gameptr->printCard(i, 2);
        }
	std::cout << std::endl;
	std::cout << "Spades:";
        for (int i = 0; i < 13; i++) {
                gameptr->printCard(i, 3);
        }
	std::cout << std::endl;
}
