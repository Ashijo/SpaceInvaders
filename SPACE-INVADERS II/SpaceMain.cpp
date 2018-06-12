
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>

#include "UIKit.h"
#include "Timer.h"
#include "Vaisseau.h"
#include "Martien.h"
#include "Laser.h"
#include "TesterCollision.h"
#include "Jeu.h"
#include "Ecrans.h"




int main()
{

	int lvl = Ecran::ecranDebut();

	
	while (lvl != 4) {
		lvl = Jeux::jeux(lvl);
	};


	Ecran::ecranFinal();



	return 0;
}
