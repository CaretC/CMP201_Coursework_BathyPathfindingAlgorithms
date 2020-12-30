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
#include "PriorityQueue.h"
// =============================================================================================



// =============================================================================================
// Public Functions
// ================
// Push node to the list. Nodes are added to the Prioirty Queue in order of F-Cost
void PriorityQueue::Push(AStarNode* node)
{
    if (IsEmpty())
    {
        orderedQueue.push_back(node);
        queueLength++;
    }
    else
    {
        for (int pos = 0; pos < queueLength; pos++) {
            if (orderedQueue.at(pos)->F_Cost > node->F_Cost)
            {
                orderedQueue.insert((orderedQueue.begin() + pos), node);
                queueLength++;
                goto inserted;
            }
            else if (pos == (queueLength - 1)) {
                orderedQueue.push_back(node);
                queueLength++;
                goto inserted;
            }
        }
    inserted:;

    }
}

// Pop
// ---
// Pop the Node from the front of the queue, this will be the node with the current lowest F-Cost
void PriorityQueue::Pop()
{
    orderedQueue.erase(orderedQueue.begin());
    queueLength--;
}

// Lowest
// ------
// Returns pointer to the node with the lowest F-Cost
AStarNode* PriorityQueue::Lowest()
{
    if (!IsEmpty())
    {
        return orderedQueue.front();
    }
    else
    {
        return nullptr;
    }
}

// Size
// ----
// Returns the current length of the priority queue.
int PriorityQueue::Size()
{
    return queueLength;
}

// IsEmpty
// -------
// Returns true when the priorty queue is empty.
bool PriorityQueue::IsEmpty()
{
    if (queueLength > 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

// In
// --
// Returns true if the node is in the queue
bool PriorityQueue::In(AStarNode* node)
{
    for (AStarNode* queueNode : orderedQueue) {
        if (queueNode == node)
        {
            return true;
        }
    }

    return false;
}
// =============================================================================================

