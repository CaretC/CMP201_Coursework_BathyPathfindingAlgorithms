/*
	Lee
	===
	Author: Joseph Lee (1903399)
	E-mail: 1903399@uad.ac.uk
	Decription: Finds the path between start point and end point using the Lee pathfinding algorithm
	Date: 29/12/2020
	Usage: This code is written for sumbission for academic assessment at Abertay University
		   for module CMP201, it should not be shared or distibuted for any other purpose
		   without conscent from author.
*/

// =============================================================================================
// Includes
// ========
#include "Lee.h"
// =============================================================================================

// =============================================================================================
// Public Functions
// ================
std::vector<UtmCoord> Lee::LeePath(const std::vector<std::vector<DataNode>> &grid, const Coord &startPoint, const Coord &endpoint)
{
	// Create Lee Grid for use with algorithm
	std::vector<std::vector<LeeNode>> leeGrid;

	// Initialize Grid
	initializeGrid(grid, leeGrid);

	// Set StartNode Distance to 0
	leeGrid[startPoint.X][startPoint.Y].Distance = 0;
	leeGrid[startPoint.X][startPoint.Y].WeightedDistance = 0;

	// Flood
	flood(startPoint, endpoint, leeGrid);

	// BackTrack
	std::vector<UtmCoord> path;
	backTrack(leeGrid, endpoint, path);

	return path;
}
// =============================================================================================


// =============================================================================================
// Private Functions
// =================
void Lee::initializeGrid(const std::vector<std::vector<DataNode>> &grid, std::vector<std::vector<LeeNode>> &leeGrid)
{
	// Get Loaded Data Grid Dimensions
	int xWidth = grid.size();
	int yHeight = grid[0].size();

	// Resize leeGrid to match grid
	leeGrid.resize(xWidth, std::vector<LeeNode>(yHeight));

	// Initialize leeGrid Data
	for (int y = 0; y < yHeight; y++) {
		for (int x = 0; x < xWidth; x++) {
			leeGrid[x][y].Position = { x, y };
			leeGrid[x][y].UtmPosition = { grid[x][y].UTM_Easting, grid[x][y].UTM_Northing };
			leeGrid[x][y].Depth = grid[x][y].Depth;
		}
	}
}

void Lee::flood(const Coord &startPoint, const Coord &endpoint, std::vector<std::vector<LeeNode>>& leeGrid)
{
	int distFromStart = 0;
	bool endFound = false;

	// While the endNode has not been found
	while (!endFound) {
		// Seach Grid for next value
		for (int y = 0; y < leeGrid[0].size(); y++) {
			for (int x = 0; x < leeGrid.size(); x++) {
				if (leeGrid[x][y].Distance == (double)distFromStart)
				{
					// Set Neighbour Nodes
					endFound = setNeighbours(leeGrid, Coord{ x, y }, endpoint);

					distFromStart++;

					// If end is found exit while loop
					if (endFound)
					{
						setNodeDist(leeGrid, endpoint, { (x - 1), y }, (double)distFromStart, endpoint);
						goto end;
					}
				}
			}
		}
	}

	end:;
}

bool Lee::setNeighbours(std::vector<std::vector<LeeNode>>& leeGrid, const Coord& currentPosition, const Coord& endPoint)
{
	bool endFound = false;

	Coord up = { currentPosition.X, currentPosition.Y - 1 };
	Coord down = { currentPosition.X, currentPosition.Y + 1 };
	Coord left = { currentPosition.X - 1, currentPosition.Y };
	Coord right = { currentPosition.X + 1, currentPosition.Y };

	for (int pos = 0; pos < 4; pos++) {
		switch (pos)
		{
			// Up
		case 0:
			endFound = setNodeDist(leeGrid, up, currentPosition, (leeGrid[currentPosition.X][currentPosition.Y].Distance + 1), endPoint);
			break;

			// Down
		case 1:
			endFound = setNodeDist(leeGrid, down, currentPosition, (leeGrid[currentPosition.X][currentPosition.Y].Distance + 1), endPoint);
			break;

			// Left
		case 2:
			endFound = setNodeDist(leeGrid, left, currentPosition, (leeGrid[currentPosition.X][currentPosition.Y].Distance + 1), endPoint);
			break;

			// Right
		case 3:
			endFound = setNodeDist(leeGrid, right, currentPosition, (leeGrid[currentPosition.X][currentPosition.Y].Distance + 1), endPoint);
			break;

		}
	}

	return endFound;
}

bool Lee::setNodeDist(std::vector<std::vector<LeeNode>>& leeGrid, const Coord& position, const Coord& previous, double dist, const Coord& endPos)
{
	if (isValidPos(position, leeGrid.size(), leeGrid[0].size()))
	{
		if (position.X == endPos.X && position.Y == endPos.Y)
		{
			leeGrid[endPos.X][endPos.Y].Distance = dist + 1;
			leeGrid[endPos.X][endPos.Y].WeightedDistance = dist + depthDifference(leeGrid, previous, position);
			return true;
		}

		if (leeGrid[position.X][position.Y].Distance == -1)
		{
			leeGrid[position.X][position.Y].Distance = dist;
			leeGrid[position.X][position.Y].WeightedDistance = dist + depthDifference(leeGrid, previous, position);
		}

		return false;
	}

	return false;
}

bool Lee::isValidPos(Coord position, int xMax, int yMax)
{
	if (position.X >= 0 && position.Y >= 0 && position.X < xMax && position.Y < yMax)
	{
		return true;
	}

	return false;
}

void Lee::backTrack(std::vector<std::vector<LeeNode>>& leeGrid, const Coord& pos, std::vector<UtmCoord>& path)
{
	if (leeGrid[pos.X][pos.Y].Distance == 0)
	{
		int test = 0;
	}
	else
	{
		path.push_back(leeGrid[pos.X][pos.Y].UtmPosition);
		Coord nextPos = lowestNeighbour(leeGrid, pos);
		backTrack(leeGrid, nextPos, path);
	}
}

Coord Lee::lowestNeighbour(const std::vector<std::vector<LeeNode>>& leeGrid, const Coord& position)
{
	Coord lowestNeighbour;

	Coord up = { position.X, position.Y - 1 };
	Coord down = { position.X, position.Y + 1 };
	Coord left = { position.X - 1, position.Y };
	Coord right = { position.X + 1, position.Y };

	for (int dir = 0; dir < 4; dir++) {
		switch (dir)
		{
			// Up
			case 0:
				lowestNeighbour = compareNodeDistance(leeGrid, position, up);
			break;

			// Down
			case 1:
				lowestNeighbour = compareNodeDistance(leeGrid, lowestNeighbour, down);
			break;

			// Left
			case 2:
				lowestNeighbour = compareNodeDistance(leeGrid, lowestNeighbour, left);
			break;

			// Right
			case 3:
				lowestNeighbour = compareNodeDistance(leeGrid, lowestNeighbour, right);
			break;

		}
	}

	return lowestNeighbour;
}

Coord Lee::compareNodeDistance(const std::vector<std::vector<LeeNode>>& leeGrid, const Coord& currentNode, const Coord& compareNode)
{
	if (isValidPos(currentNode, leeGrid.size(), leeGrid[0].size()) && isValidPos(compareNode, leeGrid.size(), leeGrid[0].size()))
	{
		if ((leeGrid[currentNode.X][currentNode.Y].WeightedDistance > leeGrid[compareNode.X][compareNode.Y].WeightedDistance) && leeGrid[compareNode.X][compareNode.Y].WeightedDistance != -1)
		{
			return compareNode;
		}
	}

	return currentNode;
}
double Lee::depthDifference(const std::vector<std::vector<LeeNode>>& leeGrid, const Coord& currentNode, const Coord& compareNode)
{
	if (isValidPos(currentNode, leeGrid.size(), leeGrid[0].size()) && isValidPos(compareNode, leeGrid.size(), leeGrid[0].size()))
	{
		return abs(leeGrid[currentNode.X][currentNode.Y].Depth - leeGrid[compareNode.X][compareNode.Y].Depth);
	}
	else
	{
		return 0;
	}
}


// =============================================================================================


