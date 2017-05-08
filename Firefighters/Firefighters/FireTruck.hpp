//|||||||||||||||||||||||||||||||||||||||||||||||

#ifndef FireTruck_HPP
#define FireTruck_HPP

//|||||||||||||||||||||||||||||||||||||||||||||||

#include "AdvancedOgreFramework.hpp"
#include "GameObject.hpp"
#include "IGridObject.hpp"


//|||||||||||||||||||||||||||||||||||||||||||||||

class FireTruck : public GameObject, public IGridObject
{
public:
	FireTruck(Ogre::Vector3 position, Ogre::Vector2 gridPosition, float startingRotation);
	~FireTruck();

	// Overrides
	virtual void update(double timeSinceLastFrame);
	void draw() override;
	Ogre::SceneNode* GetSceneNodePtr() override;

	void setGridPosition(Ogre::Vector2 newGridPosition);
	Ogre::Vector2 getGridPosition();

protected:

private:
	Ogre::Vector2 gridPosition;
};

//|||||||||||||||||||||||||||||||||||||||||||||||

#endif

//|||||||||||||||||||||||||||||||||||||||||||||||
