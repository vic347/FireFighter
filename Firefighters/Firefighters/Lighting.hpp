#include "AppState.hpp"
#include "AdvancedOgreFramework.hpp"

class Lighting
{
public:
	Lighting();
	~Lighting();


	void CreateRoomLight(Ogre::Vector3 position);
	void CreateLampLight(Ogre::Vector3 position);
	void CreateDaylight();
	void CreateNightlight();


private:
	int lightNumber; //!< A counter so that every light has a unique name. 
protected:
	Ogre::SceneManager* m_pSceneMgr; //!< Scene Manager is required to create Ogre lights. 
};
