//|||||||||||||||||||||||||||||||||||||||||||||||

#ifndef Door_HPP
#define Door_HPP

//|||||||||||||||||||||||||||||||||||||||||||||||

#include "AdvancedOgreFramework.hpp"
#include "GameObject.hpp"
#include "IGridObject.hpp"


//|||||||||||||||||||||||||||||||||||||||||||||||

class Door : public GameObject, public IGridObject
{
public:
	Door(Ogre::Vector3 position, Ogre::Vector2 gridPosition, bool isOpen, float startingRotation, int type);
	~Door();

	// Overrides
	virtual void update(double timeSinceLastFrame);
	void draw() override;
	Ogre::SceneNode* GetSceneNodePtr() override;

	bool getIsOpen();
	void setIsOpen(bool isOpen);

	void openDoor();
	void closeDoor();

	//void setGridPosition(Ogre::Vector2 newGridPosition);
	//Ogre::Vector2 getGridPosition();

protected:

	bool isOpen;
	int doorType; // 1: Right side | 2: Left side | 3: Bottom side | 4: Top side

private:

	Ogre::Vector2 gridPosition;
};

//|||||||||||||||||||||||||||||||||||||||||||||||

#endif

//|||||||||||||||||||||||||||||||||||||||||||||||
