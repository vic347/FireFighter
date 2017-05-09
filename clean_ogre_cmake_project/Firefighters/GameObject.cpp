//|||||||||||||||||||||||||||||||||||||||||||||||

#include "GameObject.hpp"
#include "ObjectManagement.hpp"

//|||||||||||||||||||||||||||||||||||||||||||||||

using namespace Ogre;

//|||||||||||||||||||||||||||||||||||||||||||||||

/** Default constructor for GameObject
 * 
 * \param mesh 
 * \param materialName 
 * \param position 
 */
GameObject::GameObject(std::string mesh, std::string materialName, Ogre::Vector3 position, Ogre::Vector2 gridPosition)
{
	m_pSceneMgr = OgreFramework::getSingletonPtr()->m_pRoot->getSceneManager("GameSceneMgr");
	gameObjectEntity = m_pSceneMgr->createEntity(mesh);

	if (materialName == "RockWall")
	{
		gameObjectNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode();
	}
	else if (materialName == "FireFighter")
	{
		gameObjectNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode();
	}
	else
	{
		gameObjectNode = m_pSceneMgr->createSceneNode();
	}
	gameObjectNode->setPosition(position);
	gameObjectNode->setUserAny(Ogre::Any(this)); // Attach GameObject on the node
	gameObjectEntity->setUserAny(Ogre::Any(this));
	if (materialName == "Fire")
		gameObjectNode->setScale(0.5, 0.5, 0.5);

	gameObjectNode->attachObject(gameObjectEntity);
	gameObjectEntity->setMaterialName(materialName);
	setGridPosition(gridPosition);
	ObjectManagement::getSingletonPtr()->addObject(this);
}

GameObject::GameObject(std::string mesh, std::string materialName, Ogre::Vector3 position, float startingRotation, Vector2 gridPosition)
{
	m_pSceneMgr = OgreFramework::getSingletonPtr()->m_pRoot->getSceneManager("GameSceneMgr");
	if (materialName == "RockWall")
	{
		gameObjectNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode();
	}
	else if (materialName == "FireFighter")
	{
		gameObjectNode = m_pSceneMgr->getRootSceneNode();
	}
	else
	{
		gameObjectNode = m_pSceneMgr->createSceneNode();
	}
	gameObjectEntity = m_pSceneMgr->createEntity(mesh);
	//gameObjectNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode();
	gameObjectNode->setPosition(position);
	gameObjectNode->setUserAny(Ogre::Any(this)); // Attach GameObject on the node
	gameObjectEntity->setUserAny(Ogre::Any(this));
	if (materialName == "Fire")
		gameObjectNode->setScale(0.5, 0.5, 0.5);
	gameObjectNode->attachObject(gameObjectEntity);
	gameObjectEntity->setMaterialName(materialName);
	setGridPosition(gridPosition);
	gameObjectNode->rotate(Ogre::Vector3::NEGATIVE_UNIT_Y, Ogre::Degree(startingRotation));
	ObjectManagement::getSingletonPtr()->addObject(this);
}

GameObject::GameObject()
{
	m_pSceneMgr = OgreFramework::getSingletonPtr()->m_pRoot->getSceneManager("GameSceneMgr");
	gameObjectEntity = nullptr;
	gameObjectNode = nullptr;
}

//void GameObject::update()
//{
//}

void GameObject::draw()
{
}

std::string GameObject::getTag()
{
	return tag;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

GameObject::~GameObject()
{
	ObjectManagement::getSingletonPtr()->deleteObject(this);
	//delete m_pSceneMgr;
}

//|||||||||||||||||||||||||||||||||||||||||||||||
/**
*	Setter for @Param gridPosition
*/
void GameObject::setGridPosition(Ogre::Vector2 newGridPosition)
{
	gridPosition = newGridPosition;
}

/**
*	Getter for @Param gridPosition
*/
Ogre::Vector2 GameObject::getGridPosition()
{
	return gridPosition;
}
