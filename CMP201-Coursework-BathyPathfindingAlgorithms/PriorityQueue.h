/*
	Priority Queue
	==============
	Author: Joseph Lee (1903399)
	E-mail: 1903399@uad.ac.uk
	Decription: Custom implementation of a priority queue, ordered by node F_Cost for use with
				the A* pathfinding algorithm.
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

#include"AStarNode.h"
// =============================================================================================

// =============================================================================================
class PriorityQueue
{
	// -----------------------------------------------------------------------------------------
	// Public
	// ------
	public:
		// Push node to the list. Nodes are added to the Prioirty Queue in order of F-Cost
		void Push(AStarNode* node);

		// Pop the Node from the front of the queue, this will be the node with the current lowest F-Cost
		void Pop();

		// Returns pointer to the node with the lowest F-Cost
		AStarNode* Lowest();

		// Returns the current length of the priority queue.
		int Size();

		// Returns true when the priorty queue is empty.
		bool IsEmpty();

		// Returns true if the node is in the queue
		bool In(AStarNode* node);
	// -----------------------------------------------------------------------------------------

	// -----------------------------------------------------------------------------------------
	// Private
	// -------
	private:
		// Stores the ordered queue
		std::vector<AStarNode*> orderedQueue;

		// Sotres the current queue length
		int queueLength = 0;
	// -----------------------------------------------------------------------------------------
};
// =============================================================================================

