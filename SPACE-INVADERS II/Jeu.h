#pragma once
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <string>

#include "UIKit.h"
#include "Timer.h"
#include "Vaisseau.h"
#include "Martien.h"
#include "Laser.h"
#include "TesterCollision.h"
#include "Timer.h"

#include <fstream>
#include <stdlib.h>
#include <sstream>

using namespace std;



class Jeux {

public:


	static int jeux(int lvl);
	static void initialisation();
	static void timer(int timerScore);


};

