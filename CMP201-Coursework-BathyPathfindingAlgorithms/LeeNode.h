#pragma once
#include"Coord.h"
#include"UtmCoord.h"

struct LeeNode {
	Coord Position = { -1, -1 };
	UtmCoord UtmPosition = { -1, -1 };
	double Distance = -1;
	double Depth = 1;
};