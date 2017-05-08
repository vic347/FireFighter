#include "ActionTurnHandler.hpp"
#include <windows.h>

ActionTurnHandler::ActionTurnHandler(int playerTurnorder, int flameTurnorder, int npcTurnorder)
{
	turnCounter = 0; //first turn is zero
	endTurn = false;
	//determine size turnorder
	nTurnsOrder = 0;
	if (playerTurnorder != -1) { nTurnsOrder++; }
	if (flameTurnorder != -1) { nTurnsOrder++; }
	if (npcTurnorder != -1) { nTurnsOrder++;}

	turnOrder.resize(nTurnsOrder); //sets correct size

	//determine turnorder
	//code assumes that turnorder starts at 0 and increment until the end
	if (playerTurnorder != -1) { turnOrder[playerTurnorder] = kPlayer; }
	if (flameTurnorder != -1) { turnOrder[flameTurnorder] = kFlame; }
	if (npcTurnorder != -1) { turnOrder[npcTurnorder] = kNpc; }
}//end of initialization

ActionTurnHandler::~ActionTurnHandler()
{
	delete &turnCounter;
	delete &turnOrder;
	delete &nTurnsOrder;
}


//function returns the next line
int ActionTurnHandler::nextTurn()
{
	//increment next turn
	turnCounter ++;
	inputHandler->resetEndTurn();

	return NULL;
} //end of nextTurn()

/** Calculates whose turn it is
 * 
 * \return integer representing whose turn it is
 */
int ActionTurnHandler::currentTurn()
{
	if (turnOrder[turnCounter % nTurnsOrder] == kPlayer)
	{
		return kPlayer;
	}

	if (turnOrder[turnCounter % nTurnsOrder] == kFlame)
	{
		return kFlame;
	}

	if (turnOrder[turnCounter % nTurnsOrder] == kNpc)
	{
		return kNpc;
	}
	//add additional turn objects here written like above
	return NULL;
}

/** Handles the input for firefighters (user)
 * 
 * \return bool endTurn
 */
bool ActionTurnHandler::handleFireFighterTurn()
{
	if (!endTurn)
	{
		// Handles FireFighter input
		inputHandler->handleUserInput();
	}
	else
	{
		// Move the FireFighters when player ends turn
		// Then call next turn
		nextTurn();
		return true;
	}
	return endTurn;
}

/** Handles the Fire input (AI)
 * 
 * \return bool endTurn
 */
bool ActionTurnHandler::handleFireTurn()
{
	if (!endTurn)
	{
		inputHandler->handleCompInput();
	}
	else
	{
		nextTurn();
		return true;
	}
	return endTurn;
}

/** Handles the Survivors inpot
 * 
 * \return endTurn
 */
bool ActionTurnHandler::handleNPCTurn()
{
	if (!endTurn)
	{
		inputHandler->handleNPCInput();
	}
	else
	{
		nextTurn();
		return true;
	}
	return endTurn;
}

/** Handles all the turns
 * 
 */
void ActionTurnHandler::handleAllTurns()
{
	endTurn = inputHandler->endTurn();
	switch (currentTurn())
	{
		// Handle FireFighter turn
	case kPlayer:
		handleFireFighterTurn();
		break;
		// Handle Fire turn
	case kFlame:
		handleFireTurn();
		break;
		// Handle NPC turn
	case kNpc:
		handleNPCTurn();
		break;
	default:
		break;
	}
}
