#pragma once
#include "Coord.h"
#include "UtmCoord.h"

struct AStarNode {
	double G_Cost = -1;
	int H_Cost = 0;
	double F_Cost = -1;
	double Depth = 1;
	int Distance = 2;
	Coord Position = { -1, -1 };
	UtmCoord UtmPosition = { -1, -1 };
	AStarNode* ParentNode = nullptr;
	bool Visited = false;
};