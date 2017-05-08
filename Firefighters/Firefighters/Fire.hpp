//|||||||||||||||||||||||||||||||||||||||||||||||

#ifndef FIRE_HPP
#define FIRE_HPP

//|||||||||||||||||||||||||||||||||||||||||||||||

#include "AdvancedOgreFramework.hpp"
#include "GameObject.hpp"
#include "IGridObject.hpp"
#include "InputComponent.hpp"
#include "FireFactory.hpp"


//|||||||||||||||||||||||||||||||||||||||||||||||

/** Fire GameObject class
 *
 *	Implements from gameObject and IGridObject
 * 
 */
class Fire : public GameObject, public IGridObject
{
public:
	// Constructors/Destructor
	Fire(Ogre::Vector3 position, Ogre::Vector2 gridPosition);
	~Fire();

	// Constants
	static const int FIRE_COST = 5;

	// Overrides
	virtual void update(double timeSinceLastFrame);
	void draw() override;
	Ogre::SceneNode* GetSceneNodePtr() override;

	// Member functions
	int getStamina();
	void setStamina(int value);
	void setInputComponent(InputComponent* input);
	void burnStuff(Ogre::Vector2 currentPosition);
	void changeIntensity(float changeValue);
	void setFireFactory(FireFactory* fireFactory);

	void destroyFire(double timeToDestroy)
	{
		destroyTime = timeToDestroy;
		isActive = false;
	};

	//void setGridPosition(Ogre::Vector2 newGridPosition);
	//Ogre::Vector2 getGridPosition();

protected:
	bool isActive;
	int stamina;
	float intensity;
	float destroyTimer;
	double destroyTime;
	// Hook an inputcomponent
	InputComponent* _input;
	FireFactory* fireFactory;
	void init();

private:

	//Ogre::Vector2 gridPosition;
};

//|||||||||||||||||||||||||||||||||||||||||||||||

#endif

//|||||||||||||||||||||||||||||||||||||||||||||||
