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
#pragma once
#include<vector>
#include<unordered_set>

#include"UtmCoord.h"
#include"DataNode.h"
#include"Coord.h"
#include"AStarNode.h"
#include"PriorityQueue.h"
// =============================================================================================

// =============================================================================================
class AStar
{
	// -----------------------------------------------------------------------------------------
	// Public
	// ------
	public:
		// Finds the path between start pointand end point using the A* pathfinding algorithm
		std::vector<UtmCoord> AStarPath(const std::vector<std::vector<DataNode>> &grid, const Coord &startPoint, const Coord &endpoint);

	// -----------------------------------------------------------------------------------------

	// -----------------------------------------------------------------------------------------
	// Private
	// -------
	private:
		std::vector<std::vector<AStarNode>> CreateAStarGrid(const std::vector<std::vector<DataNode>> &grid);

		double CalaculateGradientCost(const AStarNode& currentNode, const AStarNode& newNode);

		AStarNode* CheckNeighbour(std::vector<std::vector<AStarNode>> &grid, Coord position);

		void CalculateGCost();

		int CalculateHCost(const AStarNode& node, const AStarNode& endNode);

		void CalaculateFCost();

		void BackTrack(std::vector<std::vector<AStarNode>>& grid, AStarNode* node, std::vector<UtmCoord> &path);

		bool IsValidPos(Coord position, int xMax, int yMax);

	// -----------------------------------------------------------------------------------------
};
// =============================================================================================
