//|||||||||||||||||||||||||||||||||||||||||||||||

#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

//|||||||||||||||||||||||||||||||||||||||||||||||

#include "AppState.hpp"
#include "AdvancedOgreFramework.hpp"
//#include "ObjectManagement.hpp"

#include <OgreSubEntity.h>
#include <OgreMaterialManager.h>


/** A generic class for objects in the Scene
 * 
 */
class GameObject : public Ogre::Any
{
public:
	GameObject();
	GameObject(std::string mesh, std::string materialName, Ogre::Vector3 position, Ogre::Vector2 gridPosition);
	GameObject(std::string mesh, std::string materialName, Ogre::Vector3 position, float startingRotation, Ogre::Vector2 gridPosition);
	virtual ~GameObject();
	virtual void update(double timeSinceLastFrame) = 0;
	virtual void draw();
	Ogre::Vector3 worldPosition;
	Ogre::SceneNode* gameObjectNode;
	std::string getTag();

	void setGridPosition(Ogre::Vector2 newGridPosition);
	Ogre::Vector2 getGridPosition();
protected:
	// TODO: ADD
	// OGRE MESH MODEL
	Ogre::Entity* gameObjectEntity;
	std::string tag; // Tag to track object
	Ogre::SceneManager* m_pSceneMgr;
private:
	Ogre::Vector2 gridPosition;
};

//|||||||||||||||||||||||||||||||||||||||||||||||

#endif

//|||||||||||||||||||||||||||||||||||||||||||||||
