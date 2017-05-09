#include "AdvancedCamera.hpp";

/** Advanced Camera Class description

*	By Erik Oegema, 19-03-2017

*	This class creates a camera in a level. 

*	When making a gameState, call the funtions createCamera(); and createViewports();.

*	To move in the level around, call the move functions in this class in the GameState with a getInput method. 

*/


/** Constructor

*	@param zoomLevel is the initial zoom level when entering the level.

*	@param minZoomLevel and @param mazZoomLevel are the maximum and minimum zoom levels.

*	@param cameraMoveSpeed is the move speed on the X and Z axis of the camera. 

*	@param cameraZoomSpeed is the zoom speed of the of the camera

*/
AdvancedCamera::AdvancedCamera()
{
	zoomLevel = 1400;
	minZoomLevel = 2000;
	maxZoomLevel = 350;

	cameraMoveSpeed = 1;
	cameraZoomSpeed = 2;
}

AdvancedCamera::~AdvancedCamera()
{
	delete OgreFramework::getSingletonPtr();
}

/** createCamera

*	This funtion creates the camera. 

*	It gives the camera all the initial values and adds nodes to the scene and to the camera. 

*/
void AdvancedCamera::createCamera(Ogre::SceneManager* arg)
{
	// Create Camera
	playerCamera = arg->createCamera("PlayerCam");
	playerCamera->setPosition(Ogre::Vector3(500, 500, 500));
	playerCamera->lookAt(0, 0, 0);
	playerCamera->setNearClipDistance(5);

	// Create nodes
	worldPositionNode = arg->getRootSceneNode()->createChildSceneNode();

	cameraNode = worldPositionNode->createChildSceneNode();
	cameraNode->setPosition(playerCamera->getPosition());
	cameraNode->attachObject(playerCamera);

	// Make camera ortographic	
	playerCamera->setProjectionType(Ogre::PT_ORTHOGRAPHIC);
	playerCamera->setOrthoWindowHeight(zoomLevel);
}

/** createViewports

*	This funtion creates the viewports. 

*/
void AdvancedCamera::createViewports()
{
	OgreFramework::getSingletonPtr()->m_pViewport->setCamera(playerCamera);
	OgreFramework::getSingletonPtr()->m_pViewport->setBackgroundColour(Ogre::ColourValue(0.5, 0.5, 0.5));

	playerCamera->setAspectRatio(
		Ogre::Real(OgreFramework::getSingletonPtr()->m_pViewport->getActualWidth()) /
		Ogre::Real(OgreFramework::getSingletonPtr()->m_pViewport->getActualHeight()));
}

/** zoomCameraOut / zoomCameraIn

*	Checks if you are allowed to zoom out/in and if you are, 

*	with the setOrthoWindowHeight we can fake a zoom since you don't have a actual zoom with a orthographic camera.

*/
void AdvancedCamera::zoomCameraOut()
{
	if (zoomLevel != minZoomLevel)
	{
		playerCamera->setOrthoWindowHeight(zoomLevel += cameraZoomSpeed);
		playerCamera->pitch(Ogre::Degree(-0.05f));
	}
}

void AdvancedCamera::zoomCameraIn()
{
	if (zoomLevel != maxZoomLevel)
	{
		playerCamera->setOrthoWindowHeight(zoomLevel -= cameraZoomSpeed);
		playerCamera->pitch(Ogre::Degree(0.05f));
	}
}

/** turnCameraLeft / turnCameraRight

*	We turn around the worldPositionNode and not around the camera axis itself.  

*/
void AdvancedCamera::turnCameraLeft(double timeSinceLastFrame)
{
	worldPositionNode->yaw(Ogre::Degree(0.1f * timeSinceLastFrame));
}

void AdvancedCamera::turnCameraRight(double timeSinceLastFrame)
{
	worldPositionNode->yaw(Ogre::Degree(-0.1f * timeSinceLastFrame));
}

/** moveCamera

*	With this funtion, the player can move the camera on the X and Z axis in the level. 

*	To call the method, put in a String with the direction (up, down, left, right) you want.

*/
void AdvancedCamera::moveCamera(std::string direction, double timeSinceLastFrame)
{
	if (direction == "up")
	{
		worldPositionNode->translate(Ogre::Real(-cameraMoveSpeed * timeSinceLastFrame), Ogre::Real(0), Ogre::Real(-cameraMoveSpeed * timeSinceLastFrame), Ogre::Node::TS_LOCAL);
	}

	if (direction == "down")
	{
		worldPositionNode->translate(Ogre::Real(cameraMoveSpeed * timeSinceLastFrame), Ogre::Real(0), Ogre::Real(cameraMoveSpeed * timeSinceLastFrame), Ogre::Node::TS_LOCAL);
	}

	if (direction == "left")
	{
		worldPositionNode->translate(Ogre::Real(-cameraMoveSpeed * timeSinceLastFrame), Ogre::Real(0), Ogre::Real(cameraMoveSpeed * timeSinceLastFrame), Ogre::Node::TS_LOCAL);
	}

	if (direction == "right")
	{
		worldPositionNode->translate(Ogre::Real(cameraMoveSpeed * timeSinceLastFrame), Ogre::Real(0), Ogre::Real(-cameraMoveSpeed * timeSinceLastFrame), Ogre::Node::TS_LOCAL);
	}
}

void AdvancedCamera::cameraUpdate()
{
}
