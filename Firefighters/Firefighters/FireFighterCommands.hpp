//|||||||||||||||||||||||||||||||||||||||||||||||

#ifndef FIRE_FIGHTER_COMMANDS_HPP
#define FIRE_FIGHTER_COMMANDS_HPP

//|||||||||||||||||||||||||||||||||||||||||||||||

#include "GameObject.hpp"
#include "FireFighter.hpp"
#include "Command.hpp"
#include "Fire.hpp"

//|||||||||||||||||||||||||||||||||||||||||||||||

// Commands for FireFighter


/** Example move command for FireFighter
 * 
 * Example move command
 */
class FireFighterMoveCommand : public Command
{
public:
	FireFighterMoveCommand(GameObject* gameObject, GameObject* targetObject)
		: gameObject(gameObject),
		  targetObject(targetObject)
	{
	}

	void execute() override
	{
		try
		{
		}
		catch (const std::exception& e)
		{
			// Object is not type of FireFighter
		}
	}

private:
	GameObject* gameObject;
	GameObject* targetObject;
};

//|||||||||||||||||||||||||||||||||||||||||||||||

/** Extinguish Fire Command for FireFighter
 * 
 * TODO: 
 * -Missing implementation
 * 
 */
class FireFighterExtinguishFireCommand : public Command
{
public:
	FireFighterExtinguishFireCommand(GameObject* actor, GameObject* target)
		: actor(actor),
		  target(target)
	{
	}

	void execute() override
	{
		FireFighter* fireFighter = dynamic_cast<FireFighter*>(actor);
		Fire* fire = dynamic_cast<Fire*>(target);

		fireFighter->emitFoamParticle();
		fire->destroyFire(2500.0f);
	}

private:
	GameObject* actor;
	GameObject* target;
};

//|||||||||||||||||||||||||||||||||||||||||||||||

#endif

//|||||||||||||||||||||||||||||||||||||||||||||||
