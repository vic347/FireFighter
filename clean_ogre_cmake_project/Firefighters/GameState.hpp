//|||||||||||||||||||||||||||||||||||||||||||||||

#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

//|||||||||||||||||||||||||||||||||||||||||||||||

#include "AppState.hpp"
#include "SelectSystem.hpp"
#include "DotSceneLoader.hpp"
#include "FireFighter.hpp"
#include "Ground.hpp"
#include "Fire.hpp"
#include "Wall.hpp"
#include "Door.hpp"
#include "FireFighterInputComponent.hpp"
#include "InputHandler.hpp"
#include "AdvancedCamera.hpp";
#include "ActionTurnHandler.hpp"

#include <OgreSubEntity.h>
#include <OgreMaterialManager.h>
#include "ObjectManagement.hpp"
#include <vld.h>

//|||||||||||||||||||||||||||||||||||||||||||||||

class GameState : public AppState
{
public:
	GameState();
	~GameState();

	DECLARE_APPSTATE_CLASS(GameState)

	void enter();
	void createScene();
	void exit();
	bool pause();
	void resume();

	//void moveCamera();
	void getInput(double timeSinceLastFrame);


	bool keyPressed(const OIS::KeyEvent& keyEventRef);
	bool keyReleased(const OIS::KeyEvent& keyEventRef);

	bool mouseMoved(const OIS::MouseEvent& arg);
	bool mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id);

	//void onLeftPressed(const OIS::MouseEvent &evt);
	void itemSelected(OgreBites::SelectMenu* menu);
	void buttonHit(OgreBites::Button* button);

	void update(double timeSinceLastFrame);

	AdvancedCamera* gameCamera;

	OgreBites::ParamsPanel* m_pDetailsPanel;

	void buildGUI();
	void showDebugOptions();
	void hideDebugOptions();
	void debugUpdate();

	void nextTurn();
	//Functie voor het ophalen van map grid size
	void GameState::MapGridSizeCalc();


	Fire* fireEntity;
	FireFighter* fireFighterEntity;

private:
	Ogre::SceneNode* m_pOgreHeadNode;
	Ogre::Entity* m_pOgreHeadEntity;
	Ogre::MaterialPtr m_pOgreHeadMat;
	Ogre::MaterialPtr m_pOgreHeadMatHigh;


	bool m_bQuit;

	/*Ogre::Vector3				m_TranslateVector;
	Ogre::Real					m_MoveSpeed;
	Ogre::Degree				m_RotateSpeed;
	float						m_MoveScale;
	Ogre::Degree				m_RotScale;*/


	Ogre::RaySceneQuery* m_pRSQ;
	Ogre::SceneNode* m_pCurrentObject;
	bool debugMode;
	bool m_bLMouseDown, m_bRMouseDown;
	InputHandler* inputHandler;

	ActionTurnHandler* pActionTurnHandler;
	SelectSystem* m_characterSelect;
	FireFactory* fireFactoryEntity;
	ObjectManagement* objectManagement;

	int sizeX, sizeZ;

	double timeSinceLastFrame;
};

//|||||||||||||||||||||||||||||||||||||||||||||||

#endif

//|||||||||||||||||||||||||||||||||||||||||||||||
