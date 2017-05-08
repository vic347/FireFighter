#include "DebugOptions.hpp"

template <>
DebugOptions* Ogre::Singleton<DebugOptions>::msSingleton = 0;

DebugOptions::DebugOptions()
{
	pDetailsPanel = 0;
}

DebugOptions::~DebugOptions()
{
}

void DebugOptions::buildGUI()
{
	OgreFramework::getSingletonPtr()->m_pTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
	OgreFramework::getSingletonPtr()->m_pTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);
	OgreFramework::getSingletonPtr()->m_pTrayMgr->createLabel(OgreBites::TL_TOP, "GameLbl", "Game mode", 250);
	OgreFramework::getSingletonPtr()->m_pTrayMgr->showCursor();

	Ogre::StringVector items;
	items.push_back("cam.pX");
	items.push_back("cam.pY");
	items.push_back("cam.pZ");
	items.push_back("cam.oW");
	items.push_back("cam.oX");
	items.push_back("cam.oY");
	items.push_back("cam.oZ");
	items.push_back("Mode");

	pDetailsPanel = OgreFramework::getSingletonPtr()->m_pTrayMgr->createParamsPanel(OgreBites::TL_TOPLEFT, "DetailsPanel", 200, items);
	pDetailsPanel->show();

	Ogre::String infoText = "Controls\n[TAB] - Switch input mode\n\n[W] - Forward \n[S] - Backwards \n[A] - Left\n";
	infoText.append("[D] - Right\n [Q][E] - Rotate Left/Right  \n [Z][X] - Zoom in/out \n\n[O] - Toggle FPS / logo\n");
	infoText.append("[Print] - Take screenshot\n\n[ESC] - Exit");
	OgreFramework::getSingletonPtr()->m_pTrayMgr->createTextBox(OgreBites::TL_RIGHT, "InfoPanel", infoText, 300, 220);

	Ogre::StringVector displayModes;
	displayModes.push_back("Solid mode");
	displayModes.push_back("Wireframe mode");
	displayModes.push_back("Point mode");
	OgreFramework::getSingletonPtr()->m_pTrayMgr->createLongSelectMenu(OgreBites::TL_TOPRIGHT, "DisplayModeSelMenu", "Display Mode", 200, 3, displayModes);
}

void DebugOptions::debugUpdate(AdvancedCamera gameCamera)
{
	if (!OgreFramework::getSingletonPtr()->m_pTrayMgr->isDialogVisible())
	{
		if (pDetailsPanel->isVisible())
		{
			pDetailsPanel->setParamValue(0, Ogre::StringConverter::toString(gameCamera.playerCamera->getDerivedPosition().x));
			pDetailsPanel->setParamValue(1, Ogre::StringConverter::toString(gameCamera.playerCamera->getDerivedPosition().y));
			pDetailsPanel->setParamValue(2, Ogre::StringConverter::toString(gameCamera.playerCamera->getDerivedPosition().z));
			pDetailsPanel->setParamValue(3, Ogre::StringConverter::toString(gameCamera.playerCamera->getDerivedOrientation().w));
			pDetailsPanel->setParamValue(4, Ogre::StringConverter::toString(gameCamera.playerCamera->getDerivedOrientation().x));
			pDetailsPanel->setParamValue(5, Ogre::StringConverter::toString(gameCamera.playerCamera->getDerivedOrientation().y));
			pDetailsPanel->setParamValue(6, Ogre::StringConverter::toString(gameCamera.playerCamera->getDerivedOrientation().z));
			//         if(m_bSettingsMode)
			//{   pDetailsPanel->setParamValue(7, "Buffered Input"); }
			//         else
			//{	pDetailsPanel->setParamValue(7, "Un-Buffered Input"); }
		}
	}
}
