//|||||||||||||||||||||||||||||||||||||||||||||||

#include "FireFighter.hpp"
#include "SelectSystem.hpp"
#include "ObjectManagement.hpp"
#include "Grid.hpp"

//|||||||||||||||||||||||||||||||||||||||||||||||

/** Constructor for FireFighter
 * 
 * @param position  
 */
FireFighter::FireFighter(Ogre::Vector3 position, Ogre::Vector2 gridPosition)
	: GameObject("FireFighter.mesh", "FireFighter", position, gridPosition)
{
	tag = "FireFighter";
	speed = 2;
	movSpeed = new Ogre::Vector3(speed, speed, speed);
	health = kBaseHealth;
	stamina = kBaseStamina;
	actionPoints = kBaseActionPoints;
	amountExtinguisherFoam = kBaseAmountExtinguisherFoam;
	maximumCappacityOfExtinguisherFoam = 100;
	setGridPosition(gridPosition);
	getResultPath().clear();
	foamParticleDuration = 2500.0f;
	foamParticleTimer = 0.0f;
	pathStep = 0;

	// Add extensibility
	//gameObjectEntity->addQueryFlags(FIREFIGHTER_MASK);
	gameObjectEntity->addQueryFlags(FIREFIGHTER_MASK);
	gameObjectEntity->setQueryFlags(FIREFIGHTER_MASK);

	std::ostringstream address;
	address << (void const *)this;
std:std::string name = address.str();
	// Firefighter extinguisher particle
	foamParticle = m_pSceneMgr->createParticleSystem("ExtinguisherFoam " + name, "Extinguisher/Foam");
	foamParticleNode = GetSceneNodePtr()->createChildSceneNode("Particle" + name);
	foamParticleNode->attachObject(foamParticle);

	// Use this to turn the particle on and off
	foamParticle->setEmitting(false);
}

/** Update method 
 * 
 * @param timeSinceLastFrame 
 */
void FireFighter::update(double timeSinceLastFrame)
{
	/* This makes the player move in the right direction */
	std::vector<Ogre::Vector2> path;
	if (!getResultPath().empty())
	{
		path = getResultPath();
		if (pathStep < path.size())
		{
			if (moveTo(this, path[pathStep], 0.2f, timeSinceLastFrame))
			{
				this->setGridPosition(path[pathStep]);
				this->gameObjectNode->setPosition(Grid::getSingletonPtr()->grid[static_cast<int>(path[pathStep].x)][static_cast<int>(path[pathStep].y)].GetWorldPosition());

				pathStep++;
			}
		}
		else
		{
			//updates some values so the firefighter can move again when a new position is selected
			path.clear();
			setResultPath(path);
			pathStep = 0;
		}
	}


	// update base
	//GameObject::update(timeSinceLastFrame);

	// TODO: Decouple foam logic.
	if (foamParticle->getEmitting())
	{
		foamParticleTimer += timeSinceLastFrame;
	}

	if (foamParticleTimer >= foamParticleDuration)
	{
		foamParticle->setEmitting(false);
		foamParticleTimer = 0.0f;
	}
}

/**
 * @brief 
 */
void FireFighter::draw()
{
	// draw base
	GameObject::draw();
}

/** Get stamina of FireFighter
 * 
 * @return stamina
 */
int FireFighter::getStamina()
{
	return stamina;
}

/** Set Stamina of FireFighter
 *
 * @param value 
 */
void FireFighter::setStamina(int value)
{
	stamina = value;
}

/** Get health of FireFighter
*
* @param value
*/
int FireFighter::getHealth()
{
	return health;
}

/** Set health of FireFighter
*
* @param value
*/
void FireFighter::setHealth(int value)
{
	health = value;
}

/** Get action points of FireFighter
*
* @param value
*/
int FireFighter::getActionPoints()
{
	return actionPoints;
}

/** Set action points of FireFighter
*
* @param value
*/
void FireFighter::setActionPoints(int value)
{
	actionPoints = value;
}

/** Set action points to the base value
*
* @param value
*/
void FireFighter::setActionPointsToBase()
{
	actionPoints = kBaseActionPoints;
}

/** Set stamina to the base value
*
* @param value
*/
void FireFighter::setStaminaToBase()
{
	stamina = kBaseStamina;
}


int FireFighter::getExtinguisherFoam()
{
	return amountExtinguisherFoam;
}

int FireFighter::getMaxiumumCapacityOfExtinguisherFoam()
{
	return maximumCappacityOfExtinguisherFoam;
}

void FireFighter::setExtinguisherFoam(int setValue)
{
	amountExtinguisherFoam = setValue;
	//OgreFramework::getSingletonPtr()->m_pLog->logMessage("Set extinguisher foam to: " + std::to_string(amountExtinguisherFoam));
}

void FireFighter::addExtinguisherFoam(int addFoamAmount)
{
	amountExtinguisherFoam += addFoamAmount;
	if (amountExtinguisherFoam > kBaseAmountExtinguisherFoam) amountExtinguisherFoam = kBaseAmountExtinguisherFoam; //if the amount is bigger then the set maximum, fill to maxium
	//OgreFramework::getSingletonPtr()->m_pLog->logMessage("Adds extinguisher foam to: " + std::to_string(amountExtinguisherFoam));
}

void FireFighter::subtractExtinguisherFoam(int subtractAmount)
{
	amountExtinguisherFoam -= subtractAmount;
	//OgreFramework::getSingletonPtr()->m_pLog->logMessage("Subtracts extinguisher foam to: " + std::to_string(amountExtinguisherFoam));
}

/** Set Input Component on object for direct input
 * 
 * @param input 
 */
void FireFighter::setInputComponent(InputComponent* input)
{
	_input = input;
}

/** Get the Pointer to the Ogre::SceneNode
*
* @return Ogre::SceneNode* gameObjectNode
*/
Ogre::SceneNode* FireFighter::GetSceneNodePtr()
{
	return gameObjectNode;
}

/*
The moveTo method should take a GridCell as parameter.
Steps:
	-Take the GridCell coordinates
	-Calculate the movement path the firefighter should take
	-Walk the path 
	-return true when reached the GridCell succesfully
	-return false when it can't
*/
/*bool FireFighter::moveTo(Ogre::Vector2* movPosition)
{
	// INSERT CODE
	// THIS IS TEST CODE
	auto currentPos = gameObjectNode-> getPosition();
	if (currentPos.x > movPosition->x)
		movSpeed->x = speed * -1;
	else 
		movSpeed->x = speed * 1;

	// Take z because we only need horizontal movement and not vertical movement
	if (currentPos.z > movPosition->y)
		movSpeed->z = speed * -1;
	else 
		movSpeed->z = speed * 1;

	currentPos.x += movSpeed->x;
	currentPos.z += movSpeed->y;
	gameObjectNode->setPosition(currentPos);

	setGridPosition(*movPosition);

	return true;
}*/

///*
//*	Setter for @Param gridPosition
//*/
//void FireFighter::setGridPosition(Ogre::Vector2 newGridPosition)
//{
//	gridPosition = newGridPosition;
//}
//
///*
//*	Getter for @Param gridPosition
//*/
//Ogre::Vector2 FireFighter::getGridPosition()
//{
//	return gridPosition; 
//}

/*
bool FireFighter::moveTo(Ogre::Vector3* movPosition)
{
	Ogre::Vector3 currentPos = gameObjectNode-> getPosition();
	if (currentPos.x > movPosition->x)
		movSpeed->x = speed * -1;
	else 
		movSpeed->x = speed * 1;

	if (currentPos.y > movPosition->y)
		movSpeed->y = speed * -1;
	else 
		movSpeed->y = speed * 1;

	if (currentPos.z > movPosition->z)
		movSpeed->z = speed * -1;
	else 
		movSpeed->z = speed * 1;

	currentPos.x += movSpeed->x;
	currentPos.y += movSpeed->y;
	currentPos.z += movSpeed->z;
	gameObjectNode->setPosition(currentPos);
	return true;
}

bool FireFighter::moveTo(GridCell *gridCell)
{
	Ogre::Vector3 moveToPosition = gridCell->GetWorldPosition();
	moveTo(&moveToPosition);
	return true;
}*/

//|||||||||||||||||||||||||||||||||||||||||||||||

// destructor
FireFighter::~FireFighter()
{
	delete _input;
	delete _goToPosition;
	delete &foamParticleDuration;
	delete &foamParticleTimer;
	delete &pathStep;
	GameObject::~GameObject();
}

//|||||||||||||||||||||||||||||||||||||||||||||||
