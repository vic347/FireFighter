#include "ObjectManagement.hpp"

template <>
ObjectManagement* Ogre::Singleton<ObjectManagement>::msSingleton = 0;

ObjectManagement::ObjectManagement()
{
	gameObjects.clear();
}


ObjectManagement::~ObjectManagement()
{
}

/** This function adds a new gameObject to the gameObjects vector
*
* @param gameObject The gameobject that needs to be added to the list
*
*/
void ObjectManagement::addObject(GameObject* gameObject)
{
	gameObjects.push_back(gameObject);
}

/** This function updates all the gameObjects
 *
 * @param timeSinceLastFrame The time since the last frame
 * 
 */
void ObjectManagement::updateObjects(double timeSinceLastFrame)
{
	for (GameObject* game_object : gameObjects)
	{
		game_object->update(timeSinceLastFrame);
	}

	// Inside will break stuff.
	for each (GameObject* game_object in gameObjectsToDelete)
	{
		auto it = std::find(gameObjects.begin(), gameObjects.end(), game_object);
		if (it != gameObjects.end())
			gameObjects.erase(it);
	}
	gameObjectsToDelete.clear();
}

/** This function deletes the gameobject from the list
*
* The function searches for the right gameObject. 
* If this gameobject has been found it gets deleted
*
* @param gameObject The gameobject that needs to be deleted from the list
*
*/
void ObjectManagement::deleteObject(GameObject* gameObject)
{
	//auto it = std::find(gameObjects.begin(), gameObjects.end(), gameObject);
	//if (it != gameObjects.end())
	//	gameObjects.erase(it);
	gameObjectsToDelete.push_back(gameObject);
}


/** Get the objects with the corresponding tag
*
* The function gets the game objects with a certain tag.
* It searches through the list of gameObjects and adds it to the
* requestedObjects list if it has the right tag.
* The requestedObjects list is returned.
*
* @param tag The tag used for searching gameObjects 
* @return A list of all the requested gameObjects
*
*/
std::vector<GameObject*> ObjectManagement::getGameObjects(std::string tag)
{
	std::vector<GameObject*> requestedObjects;
	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (gameObjects.at(i)->getTag() == tag)
		{
			requestedObjects.push_back((gameObjects.at(i)));
		}
	}

	return requestedObjects;
}
