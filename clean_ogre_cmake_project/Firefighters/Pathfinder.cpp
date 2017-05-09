#include "Pathfinder.hpp"
#include "Grid.hpp"

template <>
Pathfinder* Ogre::Singleton<Pathfinder>::msSingleton = 0;

Pathfinder::Pathfinder()
{
	//init();
}


Pathfinder::~Pathfinder(void)
{
}

void Pathfinder::init()
{
}

/** A method that returns a path to another gridcell.
* 
*	This method currently uses breath-first search with early exit
*
* @param GridCell* start A pointer to the GridCell you are pathing from.
* @param GridCell* goal A pointer to the GridCell you are pathing to.
*
* @return A vector containing the Grid Coordinates that make up the path.
*/
std::vector<Ogre::Vector2> Pathfinder::FindPath(GridCell* start, GridCell* goal)
{
	std::queue<Ogre::Vector2> frontier;
	bool foundGoal = false;
	Ogre::Vector2 startPosition = start->GetGridPosition();
	Ogre::Vector2 goalPosition = goal->GetGridPosition();

	frontier.push(startPosition);
	std::unordered_map<Ogre::Vector2, Ogre::Vector2> cameFrom;
	cameFrom[startPosition] = startPosition;

	while (!frontier.empty())
	{
		auto current = frontier.front();
		frontier.pop();

		if (current == goalPosition)
		{
			OutputDebugStringW(L"Found Goal!\n");
			foundGoal = true;
			break;
		}

		for (auto next : getNeighbours(current))
		{
			if (!cameFrom.count(next))
			{
				frontier.push(next);
				cameFrom[next] = current;
			}
		}
	}
	if (!foundGoal)
	{
		std::vector<Ogre::Vector2> path;
		return path;
	}
	return reconstructPath(cameFrom, start->GetGridPosition(), goal->GetGridPosition());
}

/** Get the Neigbours of a certain GridCell
*
* @param GridCell* position The gridcell you want the neighbors of
* 
* @return A std::vector of neigboring coordinates as Ogre::Vector2
*/
std::vector<Ogre::Vector2> Pathfinder::getNeighbours(GridCell* gridCell)
{
	return getNeighbours(gridCell->GetGridPosition());
}

/** Get the Neigbours of a certain GridCell
*
* @param Vector2 position The grid position of the gridcell.
* 
* @return A std::vector of neigboring coordinates as Ogre::Vector2
*/
std::vector<Ogre::Vector2> Pathfinder::getNeighbours(Ogre::Vector2 position)
{
	// Constant with the 4 directions.
	const std::array<Ogre::Vector2, 4> DIRS =
	{Ogre::Vector2(0, -1), // Up
		Ogre::Vector2(1, 0), // Right
		Ogre::Vector2(0, 1), // Down
		Ogre::Vector2(-1, 0)}; // Left;

	int x, y, dx, dy;
	x = position.x;
	y = position.y;
	std::vector<Ogre::Vector2> results;

	// Check each direction and check if it's passable
	for (auto dir : DIRS)
	{
		dx = dir.x;
		dy = dir.y;
		Ogre::Vector2 next(x + dx, y + dy);
		if (Grid::getSingletonPtr()->inBounds(next) &&
			Grid::getSingletonPtr()->isPassable(next))
		{
			results.push_back(next);
		}
	}

	if ((x + y) % 2 == 0)
	{
		// aesthetic improvement on square grids
		std::reverse(results.begin(), results.end());
	}

	return results;
}

/** Reconstruct the path that was found during pathfinding.
*	
* @param std::unordered_map<Ogre::Vector2, Ogre::Vector2> cameFrom
* @param Ogre::Vector2 start The start of the path
* @param Ogre::Vector2 goal  The end of the path
*
* @return A std::vector describing the path with each set of coordinates represented as an Ogre::Vector2.
*/
std::vector<Ogre::Vector2> Pathfinder::reconstructPath(std::unordered_map<Ogre::Vector2, Ogre::Vector2> cameFrom, Ogre::Vector2 start, Ogre::Vector2 goal)
{
	std::vector<Ogre::Vector2> path;
	Ogre::Vector2 current = goal;
	path.push_back(current);
	while (current != start)
	{
		current = cameFrom[current];
		path.push_back(current);
	}
	std::reverse(path.begin(), path.end());

	return path;
}
