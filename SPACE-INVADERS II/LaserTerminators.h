#pragma once
#include "Laser.h"

#include "Coord.h"

class LaserTerminators : public Laser
{
public:
	bool isAlive;
	Coord coord;

	void startLaserTer(int);
	void putLaserTer();
	virtual void moveLaser();
	void removeLaser(int x, int y);
	void killLaser();
};

