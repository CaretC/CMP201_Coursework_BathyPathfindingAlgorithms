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
#pragma once
#include<vector>

#include"DataNode.h"
#include"LeeNode.h"
#include"Coord.h"
#include"UtmCoord.h"
#include"CsvWriter.h"

// =============================================================================================

// =============================================================================================
class Lee
{
	// -----------------------------------------------------------------------------------------
	// Public
	// ------
	public:
		// Finds the path between start pointand end point using the Lee pathfinding algorithm
		std::vector<UtmCoord> LeePath(const std::vector<std::vector<DataNode>>& grid, const Coord& startPoint, const Coord& endpoint, bool saveVisited);
	// -----------------------------------------------------------------------------------------

	// -----------------------------------------------------------------------------------------
	// Private
	// -------
	private:
		// Initializes the leeGrid ready for use with algorithm, it requires the loaded grid data
		void initializeGrid(const std::vector<std::vector<DataNode>>& grid, std::vector<std::vector<LeeNode>> &leeGrid);

		// Conduct the flood phase of the lee algorithm working through the entire grid and marking the distance from start node
		void flood(const Coord& startPoint, const Coord& endpoint, std::vector<std::vector<LeeNode>> &leeGrid);

		// Sets the neighbour nodes with the distance to start, returns true if the node is the end node
		bool setNeighbours(std::vector<std::vector<LeeNode>>& leeGrid, const Coord& CurrentPosition, const Coord& endPoint);

		// Sets the neighbour node distance, returns true if the node is the end node
		bool setNodeDist(std::vector<std::vector<LeeNode>>& leeGrid, const Coord& currentpositon, const Coord& previous, double dist, const Coord& endPos);

		//  Returns true id Coord is a valid position
		bool isValidPos(Coord position, int xMax, int yMax);

		// Return shortest path fron the endnode to the start node after the flood phase
		void backTrack(std::vector<std::vector<LeeNode>>& leeGrid, const Coord& currentPos, const Coord& lastPos, std::vector<UtmCoord>& path);

		// Return the neighbour node with the lowest distance value.
		Coord lowestNeighbour(const std::vector<std::vector<LeeNode>>& leeGrid, const Coord& position);

		// Returns the coord of the lowest distance node
		Coord compareNodeDistance(const std::vector<std::vector<LeeNode>>& leeGrid, const Coord& currentNode, const Coord& compareNode);

		// Returns the absolute difference in depth between the currentNode and the compareNode
		double depthDifference(const std::vector<std::vector<LeeNode>>& leeGrid, const Coord& currentNode, const Coord& copareNode);

	// -----------------------------------------------------------------------------------------
};
// =============================================================================================
