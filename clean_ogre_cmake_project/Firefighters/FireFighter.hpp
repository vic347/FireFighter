//|||||||||||||||||||||||||||||||||||||||||||||||

#ifndef FIRE_FIGHTER_HPP
#define FIRE_FIGHTER_HPP

//|||||||||||||||||||||||||||||||||||||||||||||||

#include "AdvancedOgreFramework.hpp"
#include "GameObject.hpp"
#include "IGridObject.hpp"
#include "InputComponent.hpp"
#include "GridCell.hpp"
#include "IMovableObject.hpp"


//|||||||||||||||||||||||||||||||||||||||||||||||

/** FireFighter GameObject class
 *
 *	Implements from GameObject and IGridObject
 * 
 */
class FireFighter : public GameObject, public IMovableObject
{
public:
	FireFighter(Ogre::Vector3 position, Ogre::Vector2 gridPosition);
	~FireFighter();
	virtual void update(double timeSinceLastFrame);
	void draw() override;

	int getStamina();
	void setStamina(int value);

	int getHealth();
	void setHealth(int value);

	int getActionPoints();
	void setActionPoints(int value);

	void setActionPointsToBase();
	void setStaminaToBase();

	int getExtinguisherFoam();
	int getMaxiumumCapacityOfExtinguisherFoam();
	void setExtinguisherFoam(int value); // extinguisher foam can't exceed maxium kBaseAmountExtinguisherFoam
	void addExtinguisherFoam(int value); // adds extinguisher foam to amountExtinguisherFoam, can't exceed maxium kBaseAmountExtinguisherFoam
	void subtractExtinguisherFoam(int value); // reduces amountExtinguisherFoam

	void setInputComponent(InputComponent* input);

	void emitFoamParticle() { foamParticle->setEmitting(true); };

	Ogre::SceneNode* FireFighter::GetSceneNodePtr();

	//void setGridPosition(Ogre::Vector2 newGridPosition);
	//Ogre::Vector2 getGridPosition();

	Ogre::Vector3* _goToPosition;


	// Vector2 or GridCell
	//bool moveTo(Ogre::Vector2 *movPosition);
	//bool moveTo(Ogre::Vector3 *movPosition);
	//bool moveTo(GridCell *gridCell);

protected:
	static const int kBaseHealth = 100; // Base health amount
	static const int kBaseStamina = 5; // Base stamina amount
	static const int kBaseActionPoints = 1; // Base action points amount
	static const int kBaseAmountExtinguisherFoam = 100; // Base foam amount
	int health; // The amount of health points for the firefighter
	int stamina; // The amount of stamina points for the firefighter
	int actionPoints; // The amount of action points for the firefighter
	int amountExtinguisherFoam;
	int maximumCappacityOfExtinguisherFoam;

	// Hook an inputcomponent
	InputComponent* _input;

private:
	/** Movement speed of the FireFighter
	 * 
	 * TODO:
	 * change int to float
	 * 
	 */
	int speed;
	//Ogre::Vector2 gridPosition;
	/** Movement speed of the FireFighter represented as a Vector3
	 * 
	 */

	Ogre::Vector3* movSpeed;
	Ogre::ParticleSystem* foamParticle;
	Ogre::SceneNode* foamParticleNode;

	float foamParticleTimer;
	float foamParticleDuration;

	int pathStep;
};

//|||||||||||||||||||||||||||||||||||||||||||||||

#endif

//|||||||||||||||||||||||||||||||||||||||||||||||
