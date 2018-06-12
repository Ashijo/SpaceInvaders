
#include "ExtraTerrestre.h"
#include <iostream>
#include "Maringuin.h"

using namespace std;

Maringuin::Maringuin(int a, int b):ExtraTerrestre (a,b) {

};


void Maringuin::travelMaringuin() {


	removeExtraTerrestre();


	if (coord.getPositionX()>=99){
		
		coord.setPositionY(coord.getPositionY() + 1);
		coord.setPositionX(coord.getPositionX() - 1);
	}
	else if (coord.getPositionX() <= 6) {
		coord.setPositionY(coord.getPositionY() + 1);
		coord.setPositionX(coord.getPositionX() + 1);
	
	}


	else {
		if (coord.getPositionY() % 2 == 0)
			coord.setPositionX(coord.getPositionX() - 1);
		else
			coord.setPositionX(coord.getPositionX() + 1);
	}


	travel = !travel;

	putExtraTerrestre();



};
