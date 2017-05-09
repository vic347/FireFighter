//|||||||||||||||||||||||||||||||||||||||||||||||

#include "FirefighterApp.hpp"

#include "MenuState.hpp"
#include "GameState.hpp"
#include "PauseState.hpp"

//|||||||||||||||||||||||||||||||||||||||||||||||

FirefighterApp::FirefighterApp()
{
	m_pAppStateManager = 0;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

FirefighterApp::~FirefighterApp()
{
	delete m_pAppStateManager;
	delete OgreFramework::getSingletonPtr();
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void FirefighterApp::startApp()
{
	new OgreFramework();
	if (!OgreFramework::getSingletonPtr()->initOgre("Firefighters", 0, 0))
		return;

	OgreFramework::getSingletonPtr()->m_pLog->logMessage("Launching game...");

	m_pAppStateManager = new AppStateManager();

	MenuState::create(m_pAppStateManager, "MenuState");
	GameState::create(m_pAppStateManager, "GameState");
	PauseState::create(m_pAppStateManager, "PauseState");

	m_pAppStateManager->start(m_pAppStateManager->findByName("MenuState"));
}

//|||||||||||||||||||||||||||||||||||||||||||||||
