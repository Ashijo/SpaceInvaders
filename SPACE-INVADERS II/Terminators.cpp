#include "Terminators.h"
#include <iostream>

using namespace std;


Terminators::Terminators(int a, int b) :ExtraTerrestre (a,b) {
	jiggle = true;
};



void Terminators::jiggleTerminators() {
	removeExtraTerrestre();

	if (jiggle) {
		cpt++;
		coord.setPositionX(coord.getPositionX() - 1);
	}
	else {
		cpt--;
		coord.setPositionX(coord.getPositionX() + 1);
	}
	if (cpt >= 3 || cpt <= 0)
	jiggle = !jiggle;

	putExtraTerrestre();
};