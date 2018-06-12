#pragma once
#include <iostream>
#include "UIKit.h"

using namespace std;



class Col {
public:
	static bool testerCollision(int x1, int y1, int x2, int y2);

	static bool testerCollisionPlaf(int y);

	static bool testerCollisionColo(int x);
};