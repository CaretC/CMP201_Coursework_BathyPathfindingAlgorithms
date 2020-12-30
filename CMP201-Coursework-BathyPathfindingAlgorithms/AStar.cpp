/*
	A Star
	======
	Author: Joseph Lee (1903399)
	E-mail: 1903399@uad.ac.uk
	Decription: Finds the path between start point and end point using the A* pathfinding algorithm
	Date: 29/12/2020
	Usage: This code is written for sumbission for academic assessment at Abertay University
		   for module CMP201, it should not be shared or distibuted for any other purpose
		   without conscent from author.
*/

// =============================================================================================
// Includes
// ========
#include "AStar.h"
// =============================================================================================

// =============================================================================================
// Public Functions
// ================
std::vector<UtmCoord> AStar::AStarPath(const std::vector<std::vector<DataNode>>& grid, const Coord& startPoint, const Coord& endpoint)
{
	// Placeholder for path
	std::vector<UtmCoord> path;

	// Crate Grid To Pathfind On
	std::vector<std::vector<AStarNode>> aStarGrid = CreateAStarGrid(grid);

	// Path Found
	bool pathFound = false;

	// OPEN Set
	PriorityQueue openSet;

	// Closed Set
	std::unordered_set<AStarNode*> closedSet;

	// Set start and end node pointers
	AStarNode* startNode = &aStarGrid[startPoint.X][startPoint.Y];
	AStarNode* endNode = &aStarGrid[endpoint.X][endpoint.Y];

	// Initialize StartNode Values
	startNode->F_Cost = 0;
	startNode->G_Cost = 0;
	startNode->H_Cost = CalculateHCost(*startNode, *endNode);

	// Add Start Node to the OPEN set
	openSet.Push(startNode);

	// While there are still nodes in the OPEN set
	while (!openSet.IsEmpty()) {
		// Select the node with lowest F_Cost
		AStarNode* currentNode = openSet.Lowest();

		// Place Holder For lastNode
		AStarNode* lastNode = nullptr;

		// Check the current node is not the end node
		if (!(currentNode->Position.X == endNode->Position.X && currentNode->Position.Y == endNode->Position.Y))
		{
			// Remove the current node from OPEN set and add to closed set. Set visited to true
			openSet.Pop();
			closedSet.insert(currentNode);
			currentNode->Visited = true;

			// Check All Neighbours
			AStarNode* neighbourNode = nullptr;

			Coord up = { currentNode->Position.X, currentNode->Position.Y - 1 };
			Coord down = { currentNode->Position.X, currentNode->Position.Y + 1 };
			Coord left = { currentNode->Position.X - 1, currentNode->Position.Y };
			Coord right = { currentNode->Position.X + 1, currentNode->Position.Y };

			for (int pos = 0; pos < 4; pos++) {
				switch (pos)
				{
					// Up
				case 0:
					neighbourNode = CheckNeighbour(aStarGrid, up);
					break;

					// Down
				case 1:
					neighbourNode = CheckNeighbour(aStarGrid, down);
					break;

					// Left
				case 2:
					neighbourNode = CheckNeighbour(aStarGrid, left);
					break;

					// Right
				case 3:
					neighbourNode = CheckNeighbour(aStarGrid, right);
					break;

				}


				// If neghibour node has not been added to openset and has not been seen before add to OPEN set
				if (neighbourNode != nullptr && neighbourNode->Visited != true && openSet.In(neighbourNode) != true)
				{
					// Check if this node is already in closed set
					if (closedSet.find(neighbourNode) != closedSet.end())
					{
						goto alreadyFound;
					}

					// Set nieghbour node f, g, h values
					neighbourNode->G_Cost = currentNode->G_Cost + neighbourNode->Distance + CalaculateGradientCost(*currentNode, *neighbourNode);
					neighbourNode->H_Cost = CalculateHCost(*currentNode, *endNode);
					neighbourNode->F_Cost = neighbourNode->G_Cost + neighbourNode->H_Cost;

					// Set the current node as the parent node of neighbour node
					neighbourNode->ParentNode = currentNode;

					// Push node to the open set
					openSet.Push(neighbourNode);
				}
			}
		}
		else
		{
			pathFound = true;			
			BackTrack(aStarGrid, endNode, path);
			break;
		}

		alreadyFound:;
	}

	return path;
}
// =============================================================================================

// =============================================================================================
// Private Functions
// =================
std::vector<std::vector<AStarNode>> AStar::CreateAStarGrid(const std::vector<std::vector<DataNode>> &grid)
{
	// Create Placeholder For A* Grid
	std::vector<std::vector<AStarNode>> aStarGrid;

	// Resize the aStarGrid vector to match grid
	int xWidth = grid.size();
	int yHeight = grid[0].size(); 
	aStarGrid.resize(xWidth, std::vector<AStarNode>(yHeight));

	// Populate A* Grid with the grid data
	for (int y = 0; y < yHeight; y++) {
		for (int x = 0; x < xWidth; x++) {
			aStarGrid[x][y].Position = { x, y };
			aStarGrid[x][y].UtmPosition = { grid[x][y].UTM_Easting, grid[x][y].UTM_Nothing };
			aStarGrid[x][y].Depth = grid[x][y].Depth;
		}
	}

	return aStarGrid;
}

double AStar::CalaculateGradientCost(const AStarNode& currentNode, const AStarNode& newNode)
{
	return abs(currentNode.Depth - newNode.Depth);
}

AStarNode* AStar::CheckNeighbour(std::vector<std::vector<AStarNode>>& grid, Coord position)
{
	if (IsValidPos(position, grid.size(), grid[0].size()))
	{
		if (grid[position.X][position.Y].Visited == false)
		{
			return &grid[position.X][position.Y];
		}
	}

	return nullptr;
}

int AStar::CalculateHCost(const AStarNode &node, const AStarNode &endNode)
{
	int dx = abs(node.Position.X - endNode.Position.X);
	int dy = abs(node.Position.Y - endNode.Position.Y);

	return 2 * (dx * dy);
}

void AStar::BackTrack(std::vector<std::vector<AStarNode>>& grid, AStarNode* node, std::vector<UtmCoord> &path)
{
	if (node == nullptr)
	{

	}
	else
	{
		path.push_back(node->UtmPosition);
		BackTrack(grid, node->ParentNode, path);
	}
}

bool AStar::IsValidPos(Coord position, int xMax, int yMax)
{
	if (position.X >= 0 && position.Y >= 0 && position.X < xMax && position.Y < yMax)
	{
		return true;
	}

	return false;
}

// =============================================================================================


