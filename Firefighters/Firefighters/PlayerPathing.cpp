//
//#include "PlayerPathing.hpp"
//#include <algorithm>
//
//PlayerPathing::PlayerPathing(void)
//{
//}
//
//
//PlayerPathing::~PlayerPathing(void)
//{
//}
//
///** This function calculates the path
//*
//* @param start This contains the start gridcell.
//* @param goal This contains the goal gridcell.
//*
//*/
//void PlayerPathing::calculatePath(GridCell *start, GridCell *goal)
//{
//	goalCell = goal;
//	reachable.push_back(start);
//
//	while (!reachable.empty())
//	{
//		currentNode = chooseNode(reachable);
//
//		if (currentNode == goal)
//		{
//			//return the result
//			buildPath(reachable);
//		}
//
//		reachable.pop_back();
//		explored.push_back(currentNode);
//		currentNode->setClosed(true);
//
//		std::vector<GridCell*> newReachable = getAdjacentGridCells(currentNode);
//
//		for (int i = 0; i < newReachable.size(); i++)
//		{
//			if (std::find(reachable.begin(), reachable.end(), newReachable[i]) == reachable.end())
//			{
//				reachable.push_back(newReachable[i]);
//			}
//
//			if (currentNode->GetPathCost() + 1 < newReachable[i]->GetPathCost())
//			{
//				newReachable[i - 1] = currentNode;
//				newReachable[i]->SetPathCost(currentNode->GetPathCost() + 1);
//			}
//		}
//	}
//}
//
///** This function chooses the node with the lowest cost
//*
//* The function calculates the cost of the move it wants to make.
//* At first it calculates the cost of the node itself, by getting the gScore from the gridcell.
//* After that it calculates the heuristic cost and sums these two results.
//* This way it can choose if the node is better.
//*
//* @param nodeList Contains the list of all the possible nodes.
//* @return The gridcell with the lowest cost.
//*/
//GridCell* PlayerPathing::chooseNode(std::vector<GridCell*> nodeList)
//{
//	minCost = INFINITE;
//	GridCell* bestGridCell = nullptr;
//
//	for (int i = 0; i < nodeList.size(); i++)
//	{
//		costStartToNode = nodeList[i]->getGScore();
//		costNodeToGoal = heuristicCostEstimate(nodeList[i], goalCell);
//		totalCost = costStartToNode + costNodeToGoal;
//
//		if (minCost > totalCost)
//		{
//			minCost = totalCost;
//			bestGridCell = nodeList[i];
//		}
//	}
//
//	return bestGridCell;
//}
//
///** This function calculates the heuristic cost estimate.
//*
//* @param start The starting gridcell.
//* @param goal The goal gridcell.
//*
//* @return A float of the calculated heuristic cost.
//*/
//float PlayerPathing::heuristicCostEstimate(GridCell* start, GridCell* goal)
//{
//	return abs(start->GetGridCellPositionX() - goal->GetGridCellPositionX()) + abs(start->GetGridCellPositionY() - goal->GetGridCellPositionY());
//}
//
///** This function returns the adjacent gridcells
//*
//* This function looks for the neighbours of the current gridcell.
//* It does this by looping through it and checking if it contains a gridcell and if it is explored or not
//*
//* @param gridCell Contains the current cell to check for neighbours
//*
//* @return A list with all the adjacent cells
//*/
//std::vector<GridCell*> PlayerPathing::getAdjacentGridCells(GridCell* gridCell) {
//	std::vector<GridCell*> adjacentGridCells;
//	for (int x = -1; x < 2; x++)
//	{
//		for (int y = -1; y < 2; y++)
//		{
//			if (x == 0 && y == 0)
//			{
//				continue;
//			}
//			GridCell* adjacentGridCell = &Grid::getSingletonPtr()->grid[gridCell->GetGridCellPositionX() + x][gridCell->GetGridCellPositionY() + y];
//			if ((adjacentGridCell->getClosed()) || !(adjacentGridCell->getWalkable()))
//			{
//				continue;
//			}
//
//			adjacentGridCells.push_back(adjacentGridCell);
//		}
//	}
//
//	return adjacentGridCells;
//}
//
///** This function builds the path
//* @param Gridcell List with all the gridcells
//*
//* @return The path that needs to be walked
//*/
//std::vector<GridCell*> PlayerPathing::buildPath(std::vector<GridCell*> gridCell)
//{
//	std::vector<GridCell*> path;
//	for (int i = gridCell.size(); i > -1; i--)
//	{
//		if (gridCell[i] != nullptr)
//		{
//			path.push_back(gridCell[i]);
//			gridCell[i] = gridCell[i - 1];
//		}
//	}
//	return path;
//}
//*/
