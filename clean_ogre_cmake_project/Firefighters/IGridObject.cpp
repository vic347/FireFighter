//|||||||||||||||||||||||||||||||||||||||||||||||

#include "IGridObject.hpp"

/** Default constructor, sets cost to 0 */
IGridObject::IGridObject()
{
	m_Cost = 0;
	m_CostFire = 0;
}

/** Default Destructor C*/
IGridObject::~IGridObject()
{
	//delete m_pAppStateManager;
}

/** Getter for the Pathfinding cost this object adds to a GridCell */
int IGridObject::GetCost()
{
	return m_Cost;
}

int IGridObject::GetCostFire()
{
	return m_CostFire;
}

/** Setter for the Pathfinding cost this object will add to a GridCell
* 
* @param value int value to set the cost to.
*/
void IGridObject::SetCost(int value)
{
	m_Cost = value;
}

void IGridObject::SetCostFire(int value)
{
	m_CostFire = value;
}


//|||||||||||||||||||||||||||||||||||||||||||||||
