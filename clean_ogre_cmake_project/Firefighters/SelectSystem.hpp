//|||||||||||||||||||||||||||||||||||||||||||||||

#ifndef CHARACTER_SELECT_HPP
#define CHARACTER_SELECT_HPP

//|||||||||||||||||||||||||||||||||||||||||||||||

#include "AppState.hpp"
#include "SdkTrays.h"
#include "GameObject.hpp"
#include "InputHandler.hpp"

//|||||||||||||||||||||||||||||||||||||||||||||||

enum QueryFlags
{
	FIREFIGHTER_MASK = 1 << 1,
	IGNORE_QUERY_FLAG = 1 << 0,
	FIRE_MASK = 1 << 2,
	GROUND_MASK = 1 << 3,
	DOOR_MASK = 1 << 4,
	FIRETRUCK_MASK = 1 << 5
};

//|||||||||||||||||||||||||||||||||||||||||||||||

/** This class will handle selecting objects and creating/deleting action buttons.
*
*/
class SelectSystem
{
public:
	SelectSystem();

	void initRaySceneQuery();

	void onLeftPressed(const OIS::MouseEvent& mouseEvent, Ogre::Camera* camera, Ogre::SceneManager* sceneManager);
	void deSelectOtherObject();
	void deSelectFireFighter();

	bool canExtinguish();
	bool canOpenOrCloseDoor();
	bool isNextToAFireTruck();

	//DO TO
	//MOVE TO ANOTHER CLASS
	/////////////////////////////////////
	void createActionButton(); //test
	void removeActionButton(); // test
	void command(OgreBites::Button* button);
	//////////////////////////////////////


	bool& getRMouse() { return rightMouseDown; }
	void setRMouse(bool b) { rightMouseDown = b; }

	bool& getLMouse() { return leftMouseDown; }
	void setLMouse(bool b) { leftMouseDown = b; }

	bool& getInteraction() { return interactable; }
	void setInteraction(bool b) { interactable = b; }

	bool& getFireFighterSelected() { return fireFighterSelected; }
	void setFireFighteSelected(bool b) { fireFighterSelected = b; }

	Ogre::SceneNode* getFirstSceneNode() { return firstSelectedSceneNode; }
	//void setSceneNode(Ogre::SceneNode* b) { firstSelectedSceneNode = b; }
	Ogre::SceneNode* getSecondSceneNode() { return secondSelectedSceneNode; }

	GameObject* getFirstGameObject() { return firstSelectedGameObject; }

	GameObject* getSecondGameObject() { return secondSelectedGameObject; }

	Ogre::RaySceneQuery* getRSQ() { return raySceneQuery; }

	void setInputHandler(InputHandler* input) { inputHandler = input; }

private:

	Ogre::RaySceneQuery* raySceneQuery;
	Ogre::SceneNode* firstSelectedSceneNode;
	Ogre::SceneNode* secondSelectedSceneNode;
	GameObject* firstSelectedGameObject;
	GameObject* secondSelectedGameObject;
	InputHandler* inputHandler;
	UINT secondSelectedSceneNodeFlags;
	Ogre::Entity* firstSelectedEntity;
	bool leftMouseDown, rightMouseDown;
	bool interactable;
	bool fireFighterSelected;
	bool actionButtonIsVisible;
};

//|||||||||||||||||||||||||||||||||||||||||||||||

#endif

//|||||||||||||||||||||||||||||||||||||||||||||||#pragma once
