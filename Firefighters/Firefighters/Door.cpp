//|||||||||||||||||||||||||||||||||||||||||||||||

#include "Door.hpp"
#include "IGridObject.hpp"
#include "SelectSystem.hpp"
#include "GameObject.hpp"
#include "ObjectManagement.hpp"

//|||||||||||||||||||||||||||||||||||||||||||||||

/** Default constructor for Wall
*
* \param position
*/
Door::Door(Ogre::Vector3 position, Ogre::Vector2 gridPosition, bool isOpen, float startingRotation, int type)
	: GameObject("Door.mesh", "Door", position, startingRotation, gridPosition)
{
	//tag = "Door";
	Door::setIsOpen(isOpen);
	doorType = type;
	SetCost(COST_INFINITE);
	gameObjectEntity->setQueryFlags(DOOR_MASK);
	gameObjectNode->translate(0, 64, 0);
	gameObjectNode->setScale(Ogre::Vector3(1, 1, 1));
}

///**
//*	Setter for @Param gridPosition
//*/
//void Door::setGridPosition(Ogre::Vector2 newGridPosition)
//{
//	gridPosition = newGridPosition;
//}
//
///**
/*Getter for @Param gridPosition
*/
//Ogre::Vector2 Door::getGridPosition()
//{
//	return gridPosition;
//}

/** Update method for Wall
*
* \param timeSinceLastFrame
*/
void Door::update(double timeSinceLastFrame)
{
	// update base
	//GameObject::update(timeSinceLastFrame);
}

/** Draw method of Door
*
*/
void Door::draw()
{
	// draw base
	GameObject::draw();
}

/** Get the Ogre::SceneNode Pointer from the Wall
*
* \return gameObjectNode
*/
Ogre::SceneNode* Door::GetSceneNodePtr()
{
	return gameObjectNode;
}

Door::~Door()
{
	GameObject::~GameObject();
	IGridObject::~IGridObject();
}

/** Set the door status to open
 *  
 */
void Door::openDoor()
{
	switch (doorType)
	{
	case 1:
		gameObjectNode->rotate(Ogre::Vector3::NEGATIVE_UNIT_Y, Ogre::Degree(90));
		gameObjectNode->translate(Ogre::Vector3(-64, 0, -64));
		SetCost(0);
		break;
	case 2:
		gameObjectNode->rotate(Ogre::Vector3::NEGATIVE_UNIT_Y, Ogre::Degree(90));
		gameObjectNode->translate(Ogre::Vector3(64, 0, 64));
		SetCost(0);
		break;
	case 3:
		gameObjectNode->rotate(Ogre::Vector3::NEGATIVE_UNIT_Y, Ogre::Degree(90));
		gameObjectNode->translate(Ogre::Vector3(-64, 0, -64));
		SetCost(0);
		break;
	case 4:
		gameObjectNode->rotate(Ogre::Vector3::NEGATIVE_UNIT_Y, Ogre::Degree(90));
		gameObjectNode->translate(Ogre::Vector3(64, 0, 64));
		SetCost(0);
		break;
	default:
		break;
	}
}

/** Set the door status to close
 * 
 */
void Door::closeDoor()
{
	switch (doorType)
	{
	case 1:
		gameObjectNode->rotate(Ogre::Vector3::NEGATIVE_UNIT_Y, Ogre::Degree(-90));
		gameObjectNode->translate(Ogre::Vector3(64, 0, 64));
		SetCost(-1);
		break;
	case 2:
		gameObjectNode->rotate(Ogre::Vector3::NEGATIVE_UNIT_Y, Ogre::Degree(-90));
		gameObjectNode->translate(Ogre::Vector3(-64, 0, -64));
		SetCost(-1);
		break;
	case 3:
		gameObjectNode->rotate(Ogre::Vector3::NEGATIVE_UNIT_Y, Ogre::Degree(-90));
		gameObjectNode->translate(Ogre::Vector3(64, 0, 64));
		SetCost(-1);
		break;
	case 4:
		gameObjectNode->rotate(Ogre::Vector3::NEGATIVE_UNIT_Y, Ogre::Degree(-90));
		gameObjectNode->translate(Ogre::Vector3(-64, 0, -64));
		SetCost(-1);
		break;
	default:
		break;
	}
}


/**
 *  
 * @return get the door state
 */
bool Door::getIsOpen()
{
	return isOpen;
}

/** Set the door state
 * 
 * @param isOpen zet the door state with true or false 
 */
void Door::setIsOpen(bool isOpen)
{
	Door::isOpen = isOpen;
	if (!isOpen)
		SetCost(-1);
	else
		SetCost(0);
}


//|||||||||||||||||||||||||||||||||||||||||||||||
