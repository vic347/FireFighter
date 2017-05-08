#include "AdvancedOgreFramework.hpp"
#include "InputHandler.hpp"

//#include <OgreSingleton.h>


//This class keeps track of all the action phases in the level
class ActionTurnHandler //: public Ogre::Singleton<ActionTurnHandler>
{
public:
	ActionTurnHandler(int playerTurnorder, int flameTurnorder, int NpcTurnorder); //set the priority of who goes first, with 0 going first and increment until last, -1 if not applicable in level
	~ActionTurnHandler();
	//int actionPhase(); //not used
	int nextTurn();
	int currentTurn();
	//bool isTurnFinished(); //not used

	// Call these methods in the update loop when it's their turn
	bool handleFireFighterTurn();
	bool handleFireTurn();
	bool handleNPCTurn();
	void handleAllTurns();
	void setInputHandler(InputHandler* input) { inputHandler = input; }

private:
	int turnCounter; //keeps track of how many turn passed
	//int currentTurn; //keeps track of whose turn it is
	//int countDownTimer;
	std::vector<int> turnOrder;
	int nTurnsOrder;
	InputHandler* inputHandler;
	bool endTurn;

	static const int kPlayer = 0;
	static const int kFlame = 1;
	static const int kNpc = 2;
};
