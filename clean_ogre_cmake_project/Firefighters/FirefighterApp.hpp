//|||||||||||||||||||||||||||||||||||||||||||||||

#ifndef __FirefighterApp_hpp_
#define __FirefighterApp_hpp_

//|||||||||||||||||||||||||||||||||||||||||||||||

#include "AdvancedOgreFramework.hpp"
#include "AppStateManager.hpp"

//|||||||||||||||||||||||||||||||||||||||||||||||

class FirefighterApp
{
public:
	FirefighterApp(void);
	~FirefighterApp(void);

	void startApp();

private:
	AppStateManager* m_pAppStateManager;
};

//|||||||||||||||||||||||||||||||||||||||||||||||

#endif

//|||||||||||||||||||||||||||||||||||||||||||||||
