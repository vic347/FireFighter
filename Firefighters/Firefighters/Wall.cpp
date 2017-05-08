//|||||||||||||||||||||||||||||||||||||||||||||||

#include "Wall.hpp"
#include "IGridObject.hpp"
#include "SelectSystem.hpp"
#include "GameObject.hpp"
#include "ObjectManagement.hpp"

//|||||||||||||||||||||||||||||||||||||||||||||||

/** Default constructor for Wall
 * 
 * \param position 
 */
Wall::Wall(Ogre::Vector3 position, Ogre::Vector2 gridPosition)
	: GameObject("CubePlaceholder.mesh", "Wall", position, gridPosition)
{
	tag = "Wall";
	SetCost(COST_INFINITE);
	gameObjectEntity->setQueryFlags(IGNORE_QUERY_FLAG);
	gameObjectEntity->setCastShadows(true);
}

/** Update method for Wall
 * 
 * \param timeSinceLastFrame 
 */
void Wall::update(double timeSinceLastFrame)
{
	// update base
	//GameObject::update(timeSinceLastFrame);
}

/** Draw method of Wall
 * 
 */
void Wall::draw()
{
	// draw base
	GameObject::draw();
}

/** Get the Ogre::SceneNode Pointer from the Wall
 * 
 * \return gameObjectNode
 */
Ogre::SceneNode* Wall::GetSceneNodePtr()
{
	return gameObjectNode;
}

Wall::~Wall()
{
	GameObject::~GameObject();
	IGridObject::~IGridObject();
}

//|||||||||||||||||||||||||||||||||||||||||||||||
