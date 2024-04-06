#ifndef _OBSERVER_H_
#define _OBSERVER_H_

class Observer {
	public:
		virtual void notify() = 0;
		virtual bool has7S() = 0;
		virtual int getScore() = 0;
		virtual void deal() = 0;
		virtual void resetPlayer() = 0;
		virtual void printScore(int total) = 0;
		virtual ~Observer() = default;
};

#endif
