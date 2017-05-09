//|||||||||||||||||||||||||||||||||||||||||||||||

#include "InputHandler.hpp"
#include "AdvancedOgreFramework.hpp"
#include "FireFighterCommands.hpp"
#include "FireFighter.hpp"
#include "GameObject.hpp"
#include "Door.hpp"

//|||||||||||||||||||||||||||||||||||||||||||||||

InputHandler::InputHandler()
{
	// TODO
	// - Delete test variable
	testPos = new Ogre::Vector2(100, 100);
	isTurnFinished = false;
}

InputHandler::~InputHandler()
{
	delete testPos;
	delete testGameObject;
	delete button_W;
}

/** Update user input
*
*	This function checks if certain user input is triggered each frame
*	TODO
*	Seperate user turn input from user input so that player can still use certain input
*	even when it's not the players turn
*	
*/
void InputHandler::handleUserInput()
{
	// fighter and newPos are both temporary. The real values are being retrieved from:
	// fighter from SelectSystem
	// newPos from somwhere.....Grid or SelectSystem?
	//FireFighter* fighter = new FireFighter(Ogre::Vector3(0,0,0));
	//Ogre::Vector2* newPos = new Ogre::Vector2(1,1);
	//_selectedObject = _charSelect->getFirstGameObject();
	//_targetObject = _charSelect->getSecondGameObject();

	//TEST
	initTestInput();
	//if (OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_W)) button_W->execute();
	// if (OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_A)) button_A->execute();
	// if (OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_S)) button_S->execute();
	// if (OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_D)) button_D->execute();

	if (OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_1)) isTurnFinished = true;
	//if (OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_1)) button_1->execute();
	//if (OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_2)) button_2->execute();
	//if (OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_3)) button_3->execute();
	//if (OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_4)) button_4->execute();
}

/** Update computer input
*
*	Call this when it's the computers turn to play.
*	This function updates the computer input.
*
*/
void InputHandler::handleCompInput()
{
	if (OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_1)) isTurnFinished = true;
	// Beeb Boop Boop.
	// Put AI Code here
}


/** Update npc input
 * 
 *	Call this when it's the survivors turn to play.
 *	This function updates the survivors input.
 */
void InputHandler::handleNPCInput()
{
	if (OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_1)) isTurnFinished = true;
	// Put survivors code here
}

/** Initialize test input
*
*	Initializes the test input for quick testing.
*	Might be converted to debug options in the game
*
*/
void InputHandler::initTestInput()
{
	//GameObject* gameObject;
	//Ogre::Vector2* targetPos;
	//try{
	//	if (_charSelect->getFirstSceneNode() != nullptr 
	//		&& _charSelect->getSecondSceneNode() != nullptr)
	//	{
	//		// Cannot cast selectedobject to typeof gameobject
	//		//gameObject = dynamic_cast<GameObject*>(_selectedObject);
	//		//targetPos = new Ogre::Vector2(_targetObject->getPosition().x, _targetObject->getPosition().z);
	//		button_W = new FireFighterMoveCommand( _selectedObject, _targetObject);
	//	}
	//}
	//catch(const std::exception &e )
	//{
	//}
}

void InputHandler::moveFireFighter(GameObject* actor, GameObject* target)
{
	moveFireFighterCommand = new FireFighterMoveCommand(actor, target);
}

void InputHandler::objectDeleteObject(GameObject* actor, GameObject* target)
{
	objectDeleteObjectCommand = new FireFighterExtinguishFireCommand(actor, target);
	objectDeleteObjectCommand->execute();
}


///** Sets the InputHandler needed to handle player input
// * 
// * \param charSelect 
// */
//void InputHandler::setCharSelect(SelectSystem* charSelect)
//{
//	_charSelect = charSelect;
//}


//|||||||||||||||||||||||||||||||||||||||||||||||

//|||||||||||||||||||||||||||||||||||||||||||||||
