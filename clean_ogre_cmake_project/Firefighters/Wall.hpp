//|||||||||||||||||||||||||||||||||||||||||||||||

#ifndef Wall_HPP
#define Wall_HPP

//|||||||||||||||||||||||||||||||||||||||||||||||

#include "AdvancedOgreFramework.hpp"
#include "GameObject.hpp"
#include "IGridObject.hpp"


//|||||||||||||||||||||||||||||||||||||||||||||||

class Wall : public GameObject, public IGridObject
{
public:
	Wall(Ogre::Vector3 position, Ogre::Vector2 gridPosition);
	~Wall();
	virtual void update(double timeSinceLastFrame);
	virtual void draw();
	Ogre::SceneNode* GetSceneNodePtr() override;

protected:

private:
};

//|||||||||||||||||||||||||||||||||||||||||||||||

#endif

//|||||||||||||||||||||||||||||||||||||||||||||||
