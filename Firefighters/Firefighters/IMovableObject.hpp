#pragma once

#include "AdvancedOgreFramework.hpp"
#include "GameObject.hpp"
#include "GridCell.hpp"

class IMovableObject
{
public:
	IMovableObject();
	~IMovableObject();

	std::vector<Ogre::Vector2> getResultPath();
	void setResultPath(std::vector<Ogre::Vector2> resultPath);
	bool moveTo(GameObject* gameObject, GridCell* gridCell, float movementSpeed);
	bool moveTo(GameObject* gameObject, Ogre::Vector2 gridPosition, float movementSpeed);
	bool moveTo(GameObject* gameObject, Ogre::Vector3 worldPosition, float movementSpeed);
	bool moveTo(GameObject* gameObject, Ogre::Vector2 gridPosition, float movementSpeed, double timeSinceLastFrame);
private:
	std::vector<Ogre::Vector2> resultPath; // This value contains the path the firefighter needs to walk
};
