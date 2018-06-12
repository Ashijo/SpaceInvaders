#pragma once
#include "ExtraTerrestre.h"

class Terminators : public ExtraTerrestre
{

public:
	bool jiggle;
	int cpt = 0;


	Terminators(int, int);
	void jiggleTerminators();
};
