#include "FireFactory.hpp"
#include "Fire.hpp"
#include "Wall.hpp"
#include "PlayerPathing.hpp"
#include "random"
#include <time.h>
#include <stdlib.h>

FireFactory::FireFactory()
{
}

/** Spawn fire
 * @param currentPosition require a posible vector2 of the grid position
 */
void FireFactory::setFire(Ogre::Vector2 currentPosition)
{
	Ogre::Vector2 newPosition = FireFactory::getLowestCostOfNeighbourPosition(currentPosition);
	if (newPosition != Ogre::Vector2(-1, -1))
	{
		//Fire* fire = new Fire(Ogre::Vector3(0,0,0), newPosition);
		int spreadChance = 100; //calculateSpreadChance(newPosition);
		if (burnAble(spreadChance))
		{
			Fire* fire = new Fire(Ogre::Vector3(0, 0, 0), currentPosition);
			fire->setStamina(0);
			Grid::getSingletonPtr()->grid[(int)newPosition.x][(int)newPosition.y].AddObject(fire);
		}
	}
}

/** Get the neighbours with the lowest cost
 * @param currentPosition require the current position of the gridcell of the fire 
 * @return the position of a neighbouring gridcell
 */
Ogre::Vector2 FireFactory::getLowestCostOfNeighbourPosition(Ogre::Vector2 currentPosition)
{
	int moveNumberStart = 0;
	GridCell** grid;
	grid = Grid::getSingletonPtr()->grid;
	int nRows = Grid::getSingletonPtr()->getRows();
	int nColumns = Grid::getSingletonPtr()->getColumns();
	const int numberOfPossibleDirections = 4;
	Ogre::Vector2 nextMove;
	Pos direction[numberOfPossibleDirections] = {{0,-1},{0,1},{1,0},{-1,0}};
	int a, b, finalPositionX, finalPositionY;
	b = 9999;
	a = b;
	finalPositionX = -1;
	finalPositionY = -1;

	for (moveNumberStart; moveNumberStart < numberOfPossibleDirections; moveNumberStart++)
	{
		nextMove.x = currentPosition.x + direction[moveNumberStart].x; //new x pos
		nextMove.y = currentPosition.y + direction[moveNumberStart].y; //new y pos

		if (nextMove.x < 0 || nextMove.x > nRows - 1 || nextMove.y < 0 || nextMove.y > nColumns - 1)
		{
			continue;
		}

		if (!noFireDetected(nextMove))
		{
			continue;
		}

		b = Grid::getSingletonPtr()->grid[(int)nextMove.x][(int)nextMove.y].GetPathCostFire();

		if (a > b)
		{
			a = b;
			finalPositionX = nextMove.x;
			finalPositionY = nextMove.y;
		}
	}

	if (finalPositionX >= 0 || finalPositionY >= 0)
	{
		return Ogre::Vector2(finalPositionX, finalPositionY);
	}
	else
	{
		return Ogre::Vector2(-1, -1); //return something proper
	}
}

/** calculate the chance to spread fire
 * @param newPosition use this to get the pathcost for fire
 * @return the spreadchance for the current spread
 */
int FireFactory::calculateSpreadChance(Ogre::Vector2 newPosition)
{
	int pathCost = Grid::getSingletonPtr()->grid[(int)newPosition.x][(int)newPosition.y].GetPathCostFire();
	int chance = 100 / pathCost;

	return chance;
}

/** Check if fre is able to spread
 * @param spreadChance a check for the chance to spread
 * @return if fire can spread after the randomchance
 */
bool FireFactory::burnAble(int spreadChance)
{
	int randomNumber = Ogre::Math::RangeRandom(0, 100);
	OgreFramework::getSingletonPtr()->m_pLog->logMessage("Random Number is: " + std::to_string(randomNumber));

	if (randomNumber <= spreadChance)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/** A check of availability
 * \param nextPosition use this to check around you
 * \return dirty check if the gridcell next is an able spot to burn, Unable cases are fire and wall
 */
bool FireFactory::noFireDetected(Ogre::Vector2 nextPosition)
{
	std::vector<IGridObject*> k = Grid::getSingletonPtr()->grid[(int)nextPosition.x][(int)nextPosition.y].GetGridObjectList();
	bool noFireDetected = true;

	for (int i = 0; i < k.size(); i++)
	{
		Fire* fire = dynamic_cast<Fire*>(k[i]);
		if (fire)
		{
			noFireDetected = false;
		}
		Wall* wall = dynamic_cast<Wall*>(k[i]);
		if (wall)
		{
			noFireDetected = false;
		}
	}
	if (noFireDetected) return true;
	else return false;
}

bool playerDetected(Ogre::Vector2 currenPosition)
{
	return true;
}

void burnPlayer(int value)
{
}
