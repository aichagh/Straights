#ifndef _TABLE_H_
#define _TABLE_H_

#include "observer.h"
#include "gamestate.h"
#include <vector>

class Table : public Observer {
		Game * gameptr;
	public:
		Table(Game * gameptr);
		~Table();
		bool has7S();
		int getScore();
		void deal();
		void resetPlayer();
		void printScore(int total);
		void notify() override;
};

#endif
