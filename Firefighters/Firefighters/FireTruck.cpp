//|||||||||||||||||||||||||||||||||||||||||||||||

#include "FireTruck.hpp"
#include "IGridObject.hpp"
#include "SelectSystem.hpp"
#include "GameObject.hpp"

//|||||||||||||||||||||||||||||||||||||||||||||||

/** Default constructor for Wall
*
* \param position
*/
FireTruck::FireTruck(Ogre::Vector3 position, Ogre::Vector2 gridPosition, float startingRotation)
	: GameObject("FireTruck.mesh", "FireTruck", position, startingRotation, gridPosition)
{
	SetCost(COST_INFINITE);
	gameObjectEntity->setQueryFlags(FIRETRUCK_MASK);
	gameObjectNode->setScale(Ogre::Vector3(1, 1, 1));
	setGridPosition(gridPosition);
}

/**
*	Setter for @Param gridPosition
*/
void FireTruck::setGridPosition(Ogre::Vector2 newGridPosition)
{
	gridPosition = newGridPosition;
}

/**
*	Getter for @Param gridPosition
*/
Ogre::Vector2 FireTruck::getGridPosition()
{
	return gridPosition;
}

/** Update method for FireTruck
*
* \param timeSinceLastFrame
*/
void FireTruck::update(double timeSinceLastFrame)
{
	// update base
	//GameObject::update(timeSinceLastFrame);
}

/** Draw method of FireTruck
*
*/
void FireTruck::draw()
{
	// draw base
	GameObject::draw();
}

/** Get the Ogre::SceneNode Pointer from the Wall
*
* \return gameObjectNode
*/
Ogre::SceneNode* FireTruck::GetSceneNodePtr()
{
	return gameObjectNode;
}

FireTruck::~FireTruck()
{
	GameObject::~GameObject();
	IGridObject::~IGridObject();
}


//|||||||||||||||||||||||||||||||||||||||||||||||
