//|||||||||||||||||||||||||||||||||||||||||||||||

#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

//|||||||||||||||||||||||||||||||||||||||||||||||

#include "Command.hpp"
//#include "SelectSystem.hpp"
#include "GameObject.hpp"

//|||||||||||||||||||||||||||||||||||||||||||||||

/** Handles all the input
*
*	Handles all the input (user and computer).
*	Uses Commands to handle and map the input to the functionality
*	http://gameprogrammingpatterns.com/command.html
*	See book "Design Patters" written by the Gang of Four
*
*/
class InputHandler
{
public:
	InputHandler();
	~InputHandler();


	// Handles input from the user
	void handleUserInput();

	// handles input from the computer
	void handleCompInput();

	// handles input frm the npc
	void handleNPCInput();

	// Initialize the input commands
	void initTestInput();

	//void setCharSelect(SelectSystem* charSelect);
	bool endTurn() { return isTurnFinished; };
	void resetEndTurn() { isTurnFinished = false; }
	void moveFireFighter(GameObject* actor, GameObject* target);
	void objectDeleteObject(GameObject* actor, GameObject* target);

	GameObject* testGameObject;
	Ogre::Vector2* testPos;
private:
	Command* button_W;
	Command* button_A;
	Command* button_S;
	Command* button_D;

	Command* button_1;
	Command* button_2;
	Command* button_3;
	Command* button_4;

	Command* moveFireFighterCommand;
	Command* objectDeleteObjectCommand;

	GameObject* _selectedObject;
	GameObject* _targetObject;
	//SelectSystem* _charSelect;
	bool isTurnFinished;
};

//|||||||||||||||||||||||||||||||||||||||||||||||


#endif

//|||||||||||||||||||||||||||||||||||||||||||||||
