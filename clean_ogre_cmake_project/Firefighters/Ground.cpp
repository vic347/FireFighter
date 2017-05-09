//|||||||||||||||||||||||||||||||||||||||||||||||

#include "Ground.hpp"
#include "SelectSystem.hpp"

//|||||||||||||||||||||||||||||||||||||||||||||||

/** Ground constructor
 * 
 * \param position 
 */
Ground::Ground(Ogre::Vector3 position, Ogre::Vector2 gridPosition)
	: GameObject("ground", "Rockwall", position, gridPosition)
{
	// Add extensibility
	GameObject::gameObjectEntity->setCastShadows(false);
	gameObjectEntity->setQueryFlags(GROUND_MASK);
}

/** Update method for ground
 * 
 * \param timeSinceLastFrame 
 */
void Ground::update(double timeSinceLastFrame)
{
	// update base
	//GameObject::update(timeSinceLastFrame);
}

void Ground::draw()
{
	// draw base
	GameObject::draw();
}

//|||||||||||||||||||||||||||||||||||||||||||||||

// destructor
Ground::~Ground()
{
	GameObject::~GameObject();
}

/** Get the Ogre::SceneNode Pointer from the Wall
*
* \return gameObjectNode
*/
Ogre::SceneNode* Ground::GetSceneNodePtr()
{
	return gameObjectNode;
}

//|||||||||||||||||||||||||||||||||||||||||||||||
