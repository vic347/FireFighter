#ifndef __ObjectManagement_hpp_
#define __ObjectManagement_hpp_

#include "GameObject.hpp"
#include "AdvancedOgreFramework.hpp"
#include <algorithm>

class ObjectManagement : public Ogre::Singleton<ObjectManagement>
{
public:
	ObjectManagement();
	~ObjectManagement();
	void addObject(GameObject* gameObject);
	void updateObjects(double timeSinceLastFrame);
	void deleteObject(GameObject* gameObject);
	std::vector<GameObject*> getGameObjects(std::string tag);
private:
	std::vector<GameObject*> gameObjects;
	std::vector<GameObject*> gameObjectsToDelete;
};
#endif
