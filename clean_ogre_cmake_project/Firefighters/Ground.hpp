//|||||||||||||||||||||||||||||||||||||||||||||||

#ifndef GROUND_HPP
#define GROUND_HPP

//|||||||||||||||||||||||||||||||||||||||||||||||

#include "GameObject.hpp"
#include "IGridObject.hpp"

//|||||||||||||||||||||||||||||||||||||||||||||||

/** Ground GameObject class
 * 
 */
class Ground : public GameObject, public IGridObject
{
public:
	Ground(Ogre::Vector3 position, Ogre::Vector2 gridPosition);
	~Ground();
	virtual void update(double timeSinceLastFrame);
	void draw() override;
	Ogre::SceneNode* GetSceneNodePtr() override;
protected:

private:
};

//|||||||||||||||||||||||||||||||||||||||||||||||

#endif

//|||||||||||||||||||||||||||||||||||||||||||||||
