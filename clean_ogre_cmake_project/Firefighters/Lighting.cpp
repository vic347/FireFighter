#include "Lighting.hpp"

/**	
 *	@brief Creates different kind of lights: @params CreateRoomLight(); @params CreateDayLight(); @params CreateNightLight();  
 *	
 *	@author
 *	Created by Erik Oegema
 *	03-05-2017
 *	
 *	Add lighting in the Level Generator. 
 *	Only one light variable should be used. 
 *	Get the position for the light using grid position the following way: 
 *	@code Ogre::Vector3 roomLightPos1 = Grid::getSingletonPtr()->grid[5][5].GetWorldPosition();
 *	 
 */

/** Design Choises
 *	
 *	To apply lights in the scenes I chose to make use of a class because:
 *		- You will use the same lights over and over, because of consistancy
 *		- You want to be able to create a light on the fly when creating a level
 *		
 *	Because the ambient light, also known as sunlight, is also created here, the skyboxes are also applied in this class. For different ambient/wheather
 *	you may want a different mood. The programmer can easily create a new method that matches that mood including a skybox. 
 *	
 *	------------------------------------------------------------------------------------------------------------------------------------------------------
 *	This is not a Sinleton yet, but is should be. You always want light in a scene, and you don't want different light object intervering with each other.
 *	Ogre requires lights to have a unique name. With only one light object that creates all the lights, you can assure that. 
 *
 */


Lighting::Lighting()
{
	m_pSceneMgr = OgreFramework::getSingletonPtr()->m_pRoot->getSceneManager("GameSceneMgr");
	lightNumber = 0;
}

Lighting::~Lighting()
{
}

/** Create a light for inside a room. 	
 */
void Lighting::CreateRoomLight(Ogre::Vector3 position)
{
	lightNumber += 1;
	position.y += 64;
	Ogre::Light* roomLight = m_pSceneMgr->createLight("PointLight" + std::to_string(lightNumber));
	roomLight->setDiffuseColour(0.980, 0.980, 0.824);
	roomLight->setSpecularColour(1, 1, 1);
	roomLight->setType(Ogre::Light::LT_POINT);
	roomLight->setPosition(position);
}

/** Create a light for inside a lampmodel
*
*	Does nothing atm.
*/
void Lighting::CreateLampLight(Ogre::Vector3 position)
{
}

/** Create a ambient light for night levels.
*
*	Adds also a skybox in the scene.
*/
void Lighting::CreateNightlight()
{
	m_pSceneMgr->setAmbientLight(Ogre::ColourValue(0.863, 0.863, 0.863));
	m_pSceneMgr->setSkyBox(true, "NightSky");
}

/** Create a ambient light for day levels.
*
*	Adds also a skybox in the scene.
*/
void Lighting::CreateDaylight()
{
	m_pSceneMgr->setAmbientLight(Ogre::ColourValue(1.000, 0.980, 0.804));
	m_pSceneMgr->setSkyBox(true, "DaySky");
}
