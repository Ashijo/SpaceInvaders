#include "LaserTerminators.h"
#include "Laser.h"
#include <iostream>
#include "UIKit.h"
using namespace std;

void LaserTerminators::startLaserTer(int x)
{
	coord.setPositionX(x);
	coord.setPositionY(16);
	putLaserTer();
	isAlive = true;
}


void LaserTerminators::putLaserTer()
{
	UIKit::color(11);
	coord.gotoXY(coord.getPositionX(), coord.getPositionY());
	cout << "|";
}

void LaserTerminators::removeLaser(int x, int y) {
	coord.gotoXY(x, y);
	cout << " ";
}

void LaserTerminators::moveLaser()
{
	removeLaser(coord.getPositionX(),coord.getPositionY());
	if (coord.getPositionY()<44)
	{
		LaserTerminators::coord.setPositionY(LaserTerminators::coord.getPositionY() + 1);
		putLaserTer();
	}
	else
		isAlive = false;
	if (coord.getPositionY() == 44) {
		removeLaser(coord.getPositionX(), coord.getPositionY());
	}

}


void LaserTerminators::killLaser()
{
	removeLaser(coord.getPositionX(), coord.getPositionY());
	isAlive = false;
}