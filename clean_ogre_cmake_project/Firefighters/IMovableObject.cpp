#include "IMovableObject.hpp"
#include "Grid.hpp"
#include "FireFighter.hpp"


IMovableObject::IMovableObject()
{
}


IMovableObject::~IMovableObject()
{
}

/* This sets the resultpath
 *
 * @param path The correct path
 */
void IMovableObject::setResultPath(std::vector<Ogre::Vector2> path)
{
	resultPath = path;
}

/* This gets the resultPath
 *
 * @return Returns the path
 */
std::vector<Ogre::Vector2> IMovableObject::getResultPath()
{
	return resultPath;
}

/* This converts the values to the right type
 * 
 * @param gameObject The object that needs to be moved
 * @param worldPositionGoal The position the object needs to move towards
 * @param movementSpeed The speed at which the object moves
 * @return bool This bool is used to check if the object has reached the correct position
*/
bool IMovableObject::moveTo(GameObject* gameObject, GridCell* gridCell, float movementSpeed)
{
	moveTo(gameObject, gameObject->gameObjectNode->convertLocalToWorldPosition(gridCell->GetWorldPosition()), movementSpeed);
	return true;
}

/* This converts the values to the right type
*
* @param gameObject The object that needs to be moved
* @param worldPositionGoal The position the object needs to move towards
* @param movementSpeed The speed at which the object moves
* @return bool This bool is used to check if the object has reached the correct position
*/
bool IMovableObject::moveTo(GameObject* gameObject, Ogre::Vector2 gridPosition, float movementSpeed)
{
	moveTo(gameObject, &Grid::getSingletonPtr()->grid[static_cast<int>(gridPosition.x)][static_cast<int>(gridPosition.y)], movementSpeed);
	return true;
}

/* This function makes the player move in the right direction
* 
* First the worldposition of the object gets calculated.
* Then the distance between the currentworldposition and the goal position is calculated
* When this distance is greater than the set distance the objects move closer
* until the distance is smaller than the set distance.
* The position then gets set to the worldposition so it is exactly in the right place.
* 
* @param gameObject The object that needs to be moved
* @param worldPositionGoal The position the object needs to move towards
* @param movementSpeed The speed at which the object moves
* @return bool This bool is used to check if the object has reached the correct position
*/
bool IMovableObject::moveTo(GameObject* gameObject, Ogre::Vector3 worldPositionGoal, float movementSpeed)
{
	Ogre::Vector3 currentWorldPosition = gameObject->gameObjectNode->convertLocalToWorldPosition(gameObject->gameObjectNode->getPosition());
	float minDistance = 4;
	float distance = currentWorldPosition.distance(worldPositionGoal);
	while (distance > minDistance)
	{
		auto currentPos = gameObject->gameObjectNode->getPosition();
		if (currentPos.x > worldPositionGoal.x)
			gameObject->gameObjectNode->translate(-movementSpeed, 0, 0);
		else if (currentPos.x < worldPositionGoal.x)
			gameObject->gameObjectNode->translate(movementSpeed, 0, 0);

		// Take z because we only need horizontal movement and not vertical movement
		else if (currentPos.z > worldPositionGoal.z)
			gameObject->gameObjectNode->translate(0, 0, -movementSpeed);
		else if (currentPos.z < worldPositionGoal.z)
			gameObject->gameObjectNode->translate(0, 0, movementSpeed);

		distance = gameObject->gameObjectNode->getPosition().distance(worldPositionGoal);
		if (distance > minDistance)
			return false;
	}

	return true;
}

/* This function makes the player move in the right direction
*
* First the worldposition of the object gets calculated.
* Then the distance between the currentworldposition and the goal position is calculated
* When this distance is greater than the set distance the objects move closer
* until the distance is smaller than the set distance.
* The position then gets set to the worldposition so it is exactly in the right place.
*
* @param gameObject The object that needs to be moved
* @param worldPositionGoal The position the object needs to move towards
* @param movementSpeed The speed at which the object moves
* @param timeSinceLastFrame The time that has passed since the last frame
* @return bool This bool is used to check if the object has reached the correct position
*/
bool IMovableObject::moveTo(GameObject* gameObject, Ogre::Vector2 gridPosition, float movementSpeed, double timeSinceLastFrame)
{
	GridCell* gridCell = &Grid::getSingletonPtr()->grid[static_cast<int>(gridPosition.x)][static_cast<int>(gridPosition.y)];
	Ogre::Vector3 worldPositionGoal = gridCell->GetWorldPosition();

	Ogre::Vector3 currentWorldPosition = gameObject->gameObjectNode->convertLocalToWorldPosition(gameObject->gameObjectNode->getPosition());
	float minDistance = 4;
	float distance = currentWorldPosition.distance(worldPositionGoal);
	while (distance > minDistance)
	{
		auto currentPos = gameObject->gameObjectNode->getPosition();
		if (currentPos.x > worldPositionGoal.x)
			gameObject->gameObjectNode->translate(-movementSpeed * timeSinceLastFrame, 0, 0);
		if (currentPos.x < worldPositionGoal.x)
			gameObject->gameObjectNode->translate(movementSpeed * timeSinceLastFrame, 0, 0);

		// Take z because we only need horizontal movement and not vertical movement
		if (currentPos.z > worldPositionGoal.z)
			gameObject->gameObjectNode->translate(0, 0, -movementSpeed * timeSinceLastFrame);
		if (currentPos.z < worldPositionGoal.z)
			gameObject->gameObjectNode->translate(0, 0, movementSpeed * timeSinceLastFrame);

		distance = gameObject->gameObjectNode->getPosition().distance(worldPositionGoal);
		if (distance > minDistance)
			return false;
		else
		{
		}
	}


	return true;
}
