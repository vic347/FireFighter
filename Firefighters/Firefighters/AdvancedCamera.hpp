//|||||||||||||||||||||||||||||||||||||||||||||||

#ifndef __AdvancedCamera_hpp_
#define __AdvancedCamera_hpp_

//|||||||||||||||||||||||||||||||||||||||||||||||

#include "AdvancedOgreFramework.hpp"
#include "AppStateManager.hpp"


//|||||||||||||||||||||||||||||||||||||||||||||||

class AdvancedCamera
{
public:
	AdvancedCamera();
	~AdvancedCamera();

	virtual void createCamera(Ogre::SceneManager* mgr);
	virtual void createViewports();

	void zoomCameraOut();
	void zoomCameraIn();

	void turnCameraLeft(double timeSinceLastFrame);
	void turnCameraRight(double timeSinceLastFrame);

	void cameraUpdate();

	void moveCamera(std::string direction, double timesinceLastFrame);

	Ogre::Camera* playerCamera;
	Ogre::FrameEvent m_FrameEvent;
	Ogre::RenderWindow* mWindow;


private:
	AppStateManager* m_pAppStateManager;

	int zoomLevel;
	int maxZoomLevel;
	int minZoomLevel;

	float cameraMoveSpeed;
	float cameraZoomSpeed;
	float cameraRotateSpeed;
	Ogre::Vector3 rotation;
	Ogre::Vector3 cameraTranslateVector;
	Ogre::SceneNode* worldPositionNode;
	Ogre::SceneNode* cameraNode;
};

//|||||||||||||||||||||||||||||||||||||||||||||||

#endif

//|||||||||||||||||||||||||||||||||||||||||||||||
