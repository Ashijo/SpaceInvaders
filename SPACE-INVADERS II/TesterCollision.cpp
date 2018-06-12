
#include <iostream>
#include "UIKit.h"
#include "TesterCollision.h"

using namespace std;


bool Col::testerCollision(int x1, int y1, int x2, int y2) {
	bool reponse=false;
	if (x1 == x2&&y1 == y2) reponse = true;
	return reponse;
};

bool Col::testerCollisionPlaf(int y) {
	bool reponse = false;
	if (y == 3) reponse = true;

	return reponse;
};

bool Col::testerCollisionColo(int x) {
	bool reponse = false;
	if (x == 5 || x == 100) reponse = true;

	return reponse;
};



