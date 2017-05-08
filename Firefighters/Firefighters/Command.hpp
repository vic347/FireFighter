//|||||||||||||||||||||||||||||||||||||||||||||||

#ifndef COMMAND_HPP
#define COMMAND_HPP

//|||||||||||||||||||||||||||||||||||||||||||||||

#include "GameObject.hpp"

//|||||||||||||||||||||||||||||||||||||||||||||||

/** Abstract class command
 * 
 */
class Command
{
public:
	virtual ~Command()
	{
	}

	virtual void execute() = 0;
protected:
private:
};

//|||||||||||||||||||||||||||||||||||||||||||||||

#endif

//|||||||||||||||||||||||||||||||||||||||||||||||
