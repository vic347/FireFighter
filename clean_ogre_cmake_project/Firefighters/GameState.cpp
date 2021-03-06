//|||||||||||||||||||||||||||||||||||||||||||||||

#include "GameState.hpp"
#include "SelectSystem.hpp"
#include "InputHandler.hpp"
#include "Grid.hpp"
#include "LevelGenerator.hpp"
#include "FireFactory.hpp" //DELETE THIS LATER
#include "FireTruck.hpp"
#include "ObjectManagement.hpp"
#include <fstream>


//|||||||||||||||||||||||||||||||||||||||||||||||

using namespace Ogre;
using namespace std;

//|||||||||||||||||||||||||||||||||||||||||||||||


GameState::GameState()
{
	//leftMouseDown       = false;
	//rightMouseDown       = false;


	m_bQuit = false;
	debugMode = false;


	m_characterSelect = new SelectSystem();
	inputHandler = new InputHandler();
	m_characterSelect->setInputHandler(inputHandler);

	// init advanced camera
	gameCamera = new AdvancedCamera();

	objectManagement = new ObjectManagement();
	pActionTurnHandler = new ActionTurnHandler(0, 1, 2); //player first, fire second, npc third
	pActionTurnHandler->setInputHandler(inputHandler);
}

GameState::~GameState()
{
	delete m_characterSelect;
	delete gameCamera;
	delete objectManagement;
}

SelectSystem::SelectSystem()
{
	leftMouseDown = false;
	rightMouseDown = false;
	raySceneQuery = nullptr;
	firstSelectedEntity = nullptr;
	firstSelectedSceneNode = nullptr;
	firstSelectedGameObject = nullptr;
	secondSelectedGameObject = nullptr;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void GameState::enter()
{
	OgreFramework::getSingletonPtr()->m_pLog->logMessage("Entering GameState...");

	m_pSceneMgr = OgreFramework::getSingletonPtr()->m_pRoot->createSceneManager(ST_GENERIC, "GameSceneMgr");

	//m_pSceneMgr->setAmbientLight(Ogre::ColourValue(1.000, 0.980, 0.804));
	m_pSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);


	OgreFramework::getSingletonPtr()->m_pViewport->setBackgroundColour(Ogre::ColourValue(.0f, .0f, .0f));

	m_pSceneMgr->addRenderQueueListener(OgreFramework::getSingletonPtr()->m_pOverlaySystem);

	m_characterSelect->initRaySceneQuery();

	gameCamera->createCamera(m_pSceneMgr);
	gameCamera->createViewports();

	m_pCurrentObject = 0;

	//buildGUI();
	showDebugOptions();
	hideDebugOptions();

	createScene();
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool GameState::pause()
{
	OgreFramework::getSingletonPtr()->m_pLog->logMessage("Pausing GameState...");

	return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void GameState::resume()
{
	OgreFramework::getSingletonPtr()->m_pLog->logMessage("Resuming GameState...");

	buildGUI();

	gameCamera->createViewports();

	m_bQuit = false;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void GameState::exit()
{
	OgreFramework::getSingletonPtr()->m_pLog->logMessage("Leaving GameState...");

	m_pSceneMgr->destroyCamera(gameCamera->playerCamera);

	m_pSceneMgr->destroyQuery(m_characterSelect->getRSQ());
	if (m_pSceneMgr)
		OgreFramework::getSingletonPtr()->m_pRoot->destroySceneManager(m_pSceneMgr);
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void GameState::createScene()
{
	//Ogre::Light* light = m_pSceneMgr->createLight("MainLight");
	//light->setPosition(0, 500, 0);

	MapGridSizeCalc();

	//OgreFramework::getSingletonPtr()->m_pLog->logMessage(to_string(sizeX));
	//OgreFramework::getSingletonPtr()->m_pLog->logMessage(to_string(sizeZ));

	Grid* pGrid = new Grid(sizeX, sizeZ, m_pSceneMgr);

	LevelGenerator* pLevelGen = new LevelGenerator(sizeX, sizeZ, "media/levels/level2.txt");


	Grid::getSingletonPtr()->updatePassables();
	//TODO: DELETE THIS LATER
	fireFactoryEntity = new FireFactory();

	//ParticleSystem* smokeParticle = m_pSceneMgr->createParticleSystem("Smoke", "Extinguisher/Foam");
	//SceneNode* particleNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("Particle");
	//particleNode->attachObject(smokeParticle);

	ParticleSystem* smokeParticle = m_pSceneMgr->createParticleSystem("Smoke", "Smoke");
	SceneNode* particleNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("Particle");
	particleNode->attachObject(smokeParticle);
	particleNode->setPosition(Grid::getSingletonPtr()->grid[3][3].GetWorldPosition());
}

//functie voor ophalen grid size
void GameState::MapGridSizeCalc()
{
	ifstream txtFile;
	string line;
	int numberOfLines = 0;
	int previousSizeX = 0;
	int nextSizeX = 0;

	txtFile.open("media/levels/level2.txt");
	if (txtFile.is_open())
	{
		while (!txtFile.eof())
		{
			//cout<< line << endl;
			getline(txtFile, line);
			numberOfLines++;
			nextSizeX = line.length();
			if (nextSizeX > previousSizeX)
			{
				sizeX = nextSizeX;
				previousSizeX = sizeX;
			}
		}

		txtFile.close();
	}
	sizeZ = numberOfLines;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool GameState::keyPressed(const OIS::KeyEvent& keyEventRef)
{
	if (OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_TAB))
	{
		debugMode = !debugMode;
		OgreFramework::getSingletonPtr()->keyPressed(keyEventRef);

		if (!debugMode)
		{
			hideDebugOptions();
		}
		else if (debugMode)
		{
			showDebugOptions();
		}
		return true;
	}

	if (OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_ESCAPE))
	{
		pushAppState(findByName("PauseState"));
		return true;
	}


	return true;
}

void GameState::nextTurn()
{
	//DEBUG TURN HANDLER AND FIRE
	//PRESS F TO PROGRESS TO THE NEXT TURN
	//DELETE THIS WHEN IMPLEMENTED!!!
	GridCell** grid;
	grid = Grid::getSingletonPtr()->grid;
	int nRows = Grid::getSingletonPtr()->getRows();
	int nColumns = Grid::getSingletonPtr()->getColumns();

	pActionTurnHandler->nextTurn();
	int a = pActionTurnHandler->currentTurn();
	if (a == 0)
	{ //0 == player
		OutputDebugStringW(L"Players turn\n");
	}
	if (a == 1)
	{ //1 == fire
		OutputDebugStringW(L"Fires turn\n");
		//check every grid cell if there is fire
		//if true then let it set thing on fire
		//	OgreFramework::getSingletonPtr()->m_pLog->logMessage("Grid has a length of: " + std::to_string(sizeof(grid)/sizeof(grid[0])));
		for (int i = 0; i < nRows; i++)
		{
			for (int j = 0; j < nColumns; j++)
			{
				//grab everything from the array
				std::vector<IGridObject*> objectList = grid[i][j].GetGridObjectList();
				//check if it has a fire
				for (int p = 0; p < objectList.size(); p++)
				{
					Fire* fire = dynamic_cast<Fire*>(objectList[p]);
					if (fire) //if there is a fire light stuff on fire
					{
						if (fire->getStamina() > 0)
						{
							fire->burnStuff(Ogre::Vector2(i, j));
						}
						else
						{
							fire->setStamina(1);
						}
					} //end dynamic cast
				} //end check if it has fire
			} //end j loop
		} //end i loop
	} //end if fire turn
	//END DEBUG TURN HANDLER AND FIRE
	//END DELETE THIS WHEN IMPLEMENTED!!!
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool GameState::keyReleased(const OIS::KeyEvent& keyEventRef)
{
	OgreFramework::getSingletonPtr()->keyPressed(keyEventRef);
	return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool GameState::mouseMoved(const OIS::MouseEvent& evt)
{
	if (OgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseMove(evt)) return true;

	return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool GameState::mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id)
{
	if (OgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseDown(evt, id)) return true;

	if (id == OIS::MB_Left)
	{
		m_characterSelect->onLeftPressed(evt, gameCamera->playerCamera, m_pSceneMgr);
		m_characterSelect->setLMouse(true);
	}
	else if (id == OIS::MB_Right)
	{
		m_characterSelect->setRMouse(true);
		m_characterSelect->setInteraction(false);

		m_characterSelect->deSelectFireFighter();
		m_characterSelect->deSelectOtherObject();
		m_characterSelect->removeActionButton();
	}

	return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool GameState::mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id)
{
	if (OgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseUp(evt, id)) return true;

	if (id == OIS::MB_Left)
	{
		m_characterSelect->setLMouse(false);
	}
	else if (id == OIS::MB_Right)
	{
		m_characterSelect->setRMouse(false);
	}

	return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||


//|||||||||||||||||||||||||||||||||||||||||||||||

void GameState::getInput(double timeSinceLastFrame)
{
	if (OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_A))
		gameCamera->moveCamera("left", timeSinceLastFrame);

	else if (OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_D))
		gameCamera->moveCamera("right", timeSinceLastFrame);

	else if (OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_W))
		gameCamera->moveCamera("up", timeSinceLastFrame);

	else if (OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_S))
		gameCamera->moveCamera("down", timeSinceLastFrame);
	else
		gameCamera->moveCamera("", timeSinceLastFrame);

	if (OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_Z))
		gameCamera->zoomCameraIn();

	if (OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_X))
		gameCamera->zoomCameraOut();

	if (OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_Q))
		gameCamera->turnCameraLeft(timeSinceLastFrame);

	if (OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_E))
		gameCamera->turnCameraRight(timeSinceLastFrame);
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void GameState::update(double timeSinceLastFrame)
{
	m_FrameEvent.timeSinceLastFrame = timeSinceLastFrame;
	OgreFramework::getSingletonPtr()->m_pTrayMgr->frameRenderingQueued(m_FrameEvent);

	if (m_bQuit == true)
	{
		popAppState();
		return;
	}

	debugUpdate();

	// Handles the turns
	pActionTurnHandler->handleAllTurns();

	// Update camera
	gameCamera->cameraUpdate();
	getInput(timeSinceLastFrame);

	// Update objects in scene TODO uncomment
	//fireFighterEntity->update(timeSinceLastFrame);
	//fireEntity->update(timeSinceLastFrame);
	objectManagement->updateObjects(timeSinceLastFrame);
}

// PLAYER UI
void GameState::buildGUI()
{
}

/*	Debugging options

*	by Erik Oegema 27-03-2017

*	Call showDebugOptions when entering the GameState. 

*	Call hideDebugOptions right after that.

*	Call the debugUpdate in the update. 

*	Create new buttons e.d. in the showDebugOptions method. Hide them in hideDebugOptions, look at the code how to.

*	Create button functions in buttonHit, look at the code how to. 

*	The options shown and hidden when pressing the TAB key. Check out keyPressed() for that. 

*	@Param debugMode is a boolean that is set true when the debugMode is shown. Initially it it set false in the constructor. 

*/

/*	debugUpdate();

*	This is used to determane the data for the position of the camera which you can read out in when the Debug Options are enabled. 

*/
void GameState::debugUpdate()
{
	if (debugMode && !OgreFramework::getSingletonPtr()->m_pTrayMgr->isDialogVisible())
	{
		if (m_pDetailsPanel->isVisible())
		{
			m_pDetailsPanel->setParamValue(0, Ogre::StringConverter::toString(gameCamera->playerCamera->getDerivedPosition().x));
			m_pDetailsPanel->setParamValue(1, Ogre::StringConverter::toString(gameCamera->playerCamera->getDerivedPosition().y));
			m_pDetailsPanel->setParamValue(2, Ogre::StringConverter::toString(gameCamera->playerCamera->getDerivedPosition().z));
			m_pDetailsPanel->setParamValue(3, Ogre::StringConverter::toString(gameCamera->playerCamera->getDerivedOrientation().w));
			m_pDetailsPanel->setParamValue(4, Ogre::StringConverter::toString(gameCamera->playerCamera->getDerivedOrientation().x));
			m_pDetailsPanel->setParamValue(5, Ogre::StringConverter::toString(gameCamera->playerCamera->getDerivedOrientation().y));
			m_pDetailsPanel->setParamValue(6, Ogre::StringConverter::toString(gameCamera->playerCamera->getDerivedOrientation().z));
		}
	}
}

/*	hideDebugOptions();

*	This is used to hide all the panels in

*/
void GameState::hideDebugOptions()
{
	OgreFramework::getSingletonPtr()->m_pTrayMgr->destroyWidget("InfoPanel");
	OgreFramework::getSingletonPtr()->m_pTrayMgr->destroyWidget("GameLbl");
	OgreFramework::getSingletonPtr()->m_pTrayMgr->destroyWidget("DisplayModeSelMenu");
	OgreFramework::getSingletonPtr()->m_pTrayMgr->destroyWidget("DetailsPanel");
	OgreFramework::getSingletonPtr()->m_pTrayMgr->destroyWidget("SkipTurn");
	OgreFramework::getSingletonPtr()->m_pTrayMgr->destroyWidget("SpawnFireFighter");
	OgreFramework::getSingletonPtr()->m_pTrayMgr->hideFrameStats();
	OgreFramework::getSingletonPtr()->m_pTrayMgr->hideLoadingBar();
}

/*	showDebugOptions();

*	This is used to create all the panels in

*/
void GameState::showDebugOptions()
{
	// Cam Positions
	Ogre::StringVector items;
	items.push_back("cam.pX");
	items.push_back("cam.pY");
	items.push_back("cam.pZ");
	items.push_back("cam.oW");
	items.push_back("cam.oX");
	items.push_back("cam.oY");
	items.push_back("cam.oZ");
	items.push_back("Mode");

	m_pDetailsPanel = OgreFramework::getSingletonPtr()->m_pTrayMgr->createParamsPanel(OgreBites::TL_BOTTOMLEFT, "DetailsPanel", 200, items);
	m_pDetailsPanel->show();


	OgreFramework::getSingletonPtr()->m_pTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
	OgreFramework::getSingletonPtr()->m_pTrayMgr->createLabel(OgreBites::TL_TOP, "GameLbl", "Debug Options", 250);
	OgreFramework::getSingletonPtr()->m_pTrayMgr->showCursor();


	Ogre::String infoText = "Controls \n\n[TAB] - Show/hide Debug Options\n\n[W] - Forward \n[S] - Backwards \n[A] - Left\n";
	infoText.append("[D] - Right\n [Q][E] - Rotate Left/Right  \n [Z][X] - Zoom in/out \n\n");
	infoText.append("[Print] - Take screenshot\n\n[ESC] - Exit");
	OgreFramework::getSingletonPtr()->m_pTrayMgr->createTextBox(OgreBites::TL_TOPRIGHT, "InfoPanel", infoText, 300, 300);

	Ogre::StringVector displayModes;
	displayModes.push_back("Solid mode");
	displayModes.push_back("Wireframe mode");
	displayModes.push_back("Point mode");
	OgreFramework::getSingletonPtr()->m_pTrayMgr->createLongSelectMenu(OgreBites::TL_TOPLEFT, "DisplayModeSelMenu", "Display Mode", 200, 3, displayModes);

	// Create Buttons Here
	OgreFramework::getSingletonPtr()->m_pTrayMgr->createButton(OgreBites::TL_TOPLEFT, "SkipTurn", "Skip Turn", 280);
	OgreFramework::getSingletonPtr()->m_pTrayMgr->createButton(OgreBites::TL_TOPLEFT, "SpawnFireFighter", "Spawn firefighter", 280);
}

/*	buttonHit();

*	This is used to give funtions to all buttons in the scene.

*/
void GameState::buttonHit(OgreBites::Button* button)
{
	//m_characterSelect->moveCommand(button);

	if (button->getName() == "SkipTurn")
	{
		nextTurn();
		return;
	}
	if (button->getName() == "SpawnFireFighter")
	{
		// SPAWN FIRE FIGHTER
	}
	m_characterSelect->command(button);
}

/*	itemSelected();

*	This is used to create a selection menu in the Debug Options. 
*/
void GameState::itemSelected(OgreBites::SelectMenu* menu)
{
	switch (menu->getSelectionIndex())
	{
	case 0:
		gameCamera->playerCamera->setPolygonMode(Ogre::PM_SOLID);
		break;
	case 1:
		gameCamera->playerCamera->setPolygonMode(Ogre::PM_WIREFRAME);
		break;
	case 2:
		gameCamera->playerCamera->setPolygonMode(Ogre::PM_POINTS);
		break;
	}
}


// EVERYTHING DOWN HERE IS NOT USED ANYMORE


//|||||||||||||||||||||||||||||||||||||||||||||||

//void GameState::onLeftPressed(const OIS::MouseEvent &evt)
//{
//    //if(firstSelectedSceneNode)
//    //{
//    //    firstSelectedSceneNode->showBoundingBox(false);
//    //    firstSelectedEntity->getSubEntity(1)->setMaterial(m_pOgreHeadMat);
//    //}
//
//    //Ogre::Ray mouseRay = m_pCamera->getCameraToViewportRay(OgreFramework::getSingletonPtr()->m_pMouse->getMouseState().X.abs / float(evt.state.width),
//    //    OgreFramework::getSingletonPtr()->m_pMouse->getMouseState().Y.abs / float(evt.state.height));
//    //raySceneQuery->setRay(mouseRay);
//    //raySceneQuery->setSortByDistance(true);
//
//    //Ogre::RaySceneQueryResult &result = raySceneQuery->execute();
//    //Ogre::RaySceneQueryResult::iterator itr;
//
//    //for(itr = result.begin(); itr != result.end(); itr++)
//    //{
//    //    if(itr->movable)
//    //    {
//    //        OgreFramework::getSingletonPtr()->m_pLog->logMessage("MovableName: " + itr->movable->getName());
//    //        firstSelectedSceneNode = m_pSceneMgr->getEntity(itr->movable->getName())->getParentSceneNode();
//    //        OgreFramework::getSingletonPtr()->m_pLog->logMessage("ObjName " + firstSelectedSceneNode->getName());
//    //        firstSelectedSceneNode->showBoundingBox(true);
//    //        firstSelectedEntity = m_pSceneMgr->getEntity(itr->movable->getName());
//    //        firstSelectedEntity->getSubEntity(1)->setMaterial(m_pOgreHeadMatHigh);
//    //        break;
//    //    }
//    //}
//}
