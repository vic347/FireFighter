//|||||||||||||||||||||||||||||||||||||||||||||||

#include "Fire.hpp"
#include "SelectSystem.hpp"
#include "ObjectManagement.hpp"
//|||||||||||||||||||||||||||||||||||||||||||||||

// Insert method implementation

/** Default constructor for fire
 * 
 * \param position 
 */
Fire::Fire(Ogre::Vector3 position, Ogre::Vector2 gridPosition)
	: GameObject("CubePlaceholder.mesh", "Fire", position, gridPosition)
{
	tag = "Fire";
	// fireFactory = fireFactory;
	intensity = 1;
	stamina = 1;
	// Add extensibility
	SetCost(FIRE_COST);
	gameObjectEntity->setQueryFlags(FIRE_MASK);
	isActive = true;
	destroyTimer = 0.0f;
	destroyTime = 9999.0f;

	setGridPosition(gridPosition);
}

//void Fire::setGridPosition(Ogre::Vector2 newGridPosition)
//{
//	gridPosition = newGridPosition;
//}
//
//Ogre::Vector2 Fire::getGridPosition()
//{
//	return gridPosition; 
//}


/** Update method for fire
*
* \param timeSinceLastFrame
*/
void Fire::update(double timeSinceLastFrame)
{
	//_input->update(*this); // Update inputcomponent
	// update base
	//GameObject::update(timeSinceLastFrame);
	if (!isActive)
	{
		destroyTimer += timeSinceLastFrame;
		if (destroyTimer >= destroyTime)
		{
			delete this;
		}
	}
}

void Fire::draw()
{
	// draw base
	GameObject::draw();
}

/** Getter for a pointer to the scene node of this GameObject */
Ogre::SceneNode* Fire::GetSceneNodePtr()
{
	return gameObjectNode;
}

/** Get Stamina of Fire
 * 
 * \return stamina
 */
int Fire::getStamina()
{
	return stamina;
}

/** Set stamina of Fire
 * 
 * \param value 
 */
void Fire::setStamina(int value)
{
	stamina = value;
}

/** Setter for InputComponent (used for cheat options)
 * 
 * \param input 
 */
void Fire::setInputComponent(InputComponent* input)
{
	_input = input;
}

//this method is called during fires turn to burn stuff
void Fire::burnStuff(Ogre::Vector2 currentPosition)
{
	fireFactory->setFire(currentPosition);
	//BURN fuel on current position ();
	// changeIntensity(0.05);
}

void Fire::changeIntensity(float changeValue)
{
	intensity += changeValue;
	gameObjectNode->setScale(Ogre::Vector3(intensity, intensity, intensity));
}

void Fire::setFireFactory(FireFactory* fireFactory)
{
	fireFactory = fireFactory;
}


//|||||||||||||||||||||||||||||||||||||||||||||||

Fire::~Fire()
{
	m_pSceneMgr->destroyEntity(gameObjectEntity);
	m_pSceneMgr->destroySceneNode(gameObjectNode);
}

//|||||||||||||||||||||||||||||||||||||||||||||||
