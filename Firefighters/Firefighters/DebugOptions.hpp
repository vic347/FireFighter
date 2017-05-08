//|||||||||||||||||||||||||||||||||||||||||||||||

#ifndef __DebugOptions_hpp_
#define __DebugOptions_hpp_

//|||||||||||||||||||||||||||||||||||||||||||||||
#include "AdvancedOgreFramework.hpp"
#include "AdvancedCamera.hpp"


//|||||||||||||||||||||||||||||||||||||||||||||||
class DebugOptions : public Ogre::Singleton<DebugOptions>
{
public:
	DebugOptions();
	~DebugOptions(void);


	void buildGUI();
	void debugUpdate(AdvancedCamera gameCamera);

	OgreBites::ParamsPanel* pDetailsPanel;
};


//|||||||||||||||||||||||||||||||||||||||||||||||

#endif

//|||||||||||||||||||||||||||||||||||||||||||||||
