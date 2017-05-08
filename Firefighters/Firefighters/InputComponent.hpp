//|||||||||||||||||||||||||||||||||||||||||||||||

#ifndef INPUT_COMPONENT_HPP
#define INPUT_COMPONENT_HPP

//|||||||||||||||||||||||||||||||||||||||||||||||

#include "GameObject.hpp"

//|||||||||||||||||||||||||||||||||||||||||||||||
// http://gameprogrammingpatterns.com/component.html

/** Abstract InputComponent
 * 
 */
class InputComponent
{
public:
	virtual ~InputComponent();
	virtual void update(GameObject& gameObject);
protected:

private:
};

//|||||||||||||||||||||||||||||||||||||||||||||||

#endif

//|||||||||||||||||||||||||||||||||||||||||||||||
