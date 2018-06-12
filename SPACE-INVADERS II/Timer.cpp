#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <iostream>
using namespace std;

#include "Timer.h"


	Timer::Timer(long delai) {
		this->delai = delai;

	}

	void Timer::start() {
		this->timer = clock();
	}

	bool Timer::estPret() {
		bool pret = false;

		if (clock() >= timer + delai) {
			pret = true;
			timer = clock();
		}

		return pret;
	}
