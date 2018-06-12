
#ifndef TIMER_H
#define TIMER_H


class Timer {
private:
	long timer;
	long delai;

public:
	Timer (long delai);

	void start();

	bool estPret();
};

#endif
