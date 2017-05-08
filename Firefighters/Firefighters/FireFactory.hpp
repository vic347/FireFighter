#pragma once

#include "AdvancedOgreFramework.hpp"
#include "Grid.hpp"

class FireFactory
{
public:
	FireFactory();
	~FireFactory();

	Ogre::Vector2 getLowestCostOfNeighbourPosition(Ogre::Vector2 currentPosition);
	void setFire(Ogre::Vector2 currentPosition);
	bool noFireDetected(Ogre::Vector2 nextPosition);
	bool playerDetected(Ogre::Vector2 currenPosition);
	void burnPlayer(int value);
protected:
	int intensity;

private:
	//int *moveNumberStart;
	bool FireFactory::burnAble(int spreadChance);
	int FireFactory::calculateSpreadChance(Ogre::Vector2 currentPosition);

	struct Pos
	{
		int x;
		int y;
	};
};
