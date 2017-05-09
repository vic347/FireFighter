//|||||||||||||||||||||||||||||||||||||||||||||||

#ifndef FIRE_FIGHTER_INPUT_COMPONENT_HPP
#define FIRE_FIGHTER_INPUT_COMPONENT_HPP

//|||||||||||||||||||||||||||||||||||||||||||||||

#include "InputComponent.hpp"
#include "FireFighter.hpp"

//|||||||||||||||||||||||||||||||||||||||||||||||

/** Component for direct input for the firefighter
 *
 *	This might not be needed eventually, but usefull for testing purposes
 *	Reacts to direct input instead of commands.
 *	http://gameprogrammingpatterns.com/component.html
 */
class FireFighterInputComponent : public InputComponent
{
public:
	~FireFighterInputComponent();
	void update(FireFighter& fireFighter);
protected:

private:
};

//|||||||||||||||||||||||||||||||||||||||||||||||

#endif

//|||||||||||||||||||||||||||||||||||||||||||||||
