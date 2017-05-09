#include "GridCell.hpp"
#include "Grid.hpp"

#pragma once
class PlayerPathing
{
public:
	PlayerPathing(void);
	~PlayerPathing(void);
	void calculatePath(GridCell* start, GridCell* goal);
private:
	float heuristicCostEstimate(GridCell* start, GridCell* goal);
	void getCost(GridCell gridCell);
	GridCell* chooseNode(std::vector<GridCell*> nodeList);
	std::vector<GridCell*> getAdjacentGridCells(GridCell* gridCell);
	std::vector<GridCell*> buildPath(std::vector<GridCell*> gridCell);
	std::vector<GridCell*> reachable; /** This contains the reachable grid cells */
	std::vector<GridCell*> explored; /** This contains the visited grid cells */

	GridCell* goalCell; /** This pointer refers to the goal cell */
	GridCell* currentNode; /** This pointer refers to the current cell */
	float minCost; /** This float contains the minimal cost */
	float totalCost; /** This float contains the total cost */
	float costStartToNode; /** This contains the cost from the start to the next node */
	float costNodeToGoal; /** This contains the heuristic calculation cost */
};
