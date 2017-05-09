//|||||||||||||||||||||||||||||||||||||||||||||||

#ifndef I_GRID_OBJECT_HPP
#define I_GRID_OBJECT_HPP

//|||||||||||||||||||||||||||||||||||||||||||||||

#include "AdvancedOgreFramework.hpp"
#include "AppStateManager.hpp"

/* An interface which is implemented in all grid-based objects.
*
*	This interface will enable us to simply add game objects to a grid by using it's virtual method
*	We have opted to use this interface to simply add and track objects that are attached to the grid. And to have an easy way to add
*	this functionality to new objects.
*/
class IGridObject
{
public:
	// Constants
	static const int COST_INFINITE = -1;

	// Constructors/Destructors
	IGridObject();
	virtual ~IGridObject();

	// Virtual member fucntions
	virtual Ogre::SceneNode* GetSceneNodePtr() = 0;

	// Getters/Setters
	int GetCost();
	void SetCost(int value);
	int GetCostFire();
	void SetCostFire(int value);

protected:
	AppStateManager* m_pAppStateManager;

private:
	Ogre::Vector3 m_LocalPosition; /** An Ogre::Vector3 to store the object's position in local space. The center of the grid it's connected to is seen as (0,0) */
	Ogre::Vector2 m_GridPosition; /** An Ogre::Vector2 to store the object's position in the grid. */
	int m_Cost; /** The pathfinding cost that this object will add to the cell */
	int m_CostFire;
};

//|||||||||||||||||||||||||||||||||||||||||||||||


#endif

//|||||||||||||||||||||||||||||||||||||||||||||||
