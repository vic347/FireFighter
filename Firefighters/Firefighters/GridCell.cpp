#include "GridCell.hpp"
#include "SelectSystem.hpp"
#include <iostream>
#include <vector>
#include "Ground.hpp"

/** Default Constructor */
GridCell::GridCell()
//: GameObject()
{
}

/** Constructor for grid cell.
*
*	The grid cell generates a node with a plane connected. objects 
*	
*	@param &gridPosX A reference to an interger describing the X position of the cell on the grid.
*	@param &gridPosY A reference to an interger describing the Y position of the cell on the grid
*	@param &worldPosX A reference to an float describing the position of the cell in world coordinates.
*	@param &worldPosX A reference to an float describing the position of the cell in world coordinates.
*  
*
*/
GridCell::GridCell(int& gridPosX, int& gridPosY, float& worldPosX, float& worldPosZ, Ogre::SceneManager* pSceneManager)
//: GameObject()
{
	// initialize some variables
	walkable = true;

	//TODO move to ow
	// Create a plane the size of the grid
	Ogre::Plane ground(Ogre::Vector3::UNIT_Y, 0);
	Ogre::MeshManager::getSingleton().createPlane(
		"ground",
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		ground,
		GRID_CELL_SIZE, GRID_CELL_SIZE,
		GRID_CELL_SEGMENTS, GRID_CELL_SEGMENTS,
		true,
		1, 1, 1,
		Ogre::Vector3::UNIT_Z);

	// Create a node.
	Ogre::SceneNode* pGroundNode = pSceneManager->getRootSceneNode()->createChildSceneNode();
	pGroundNode->setPosition(worldPosX, 0, worldPosZ);


	// Set the node.
	m_pNode = pGroundNode;

	// Set position in variables
	gridPosition = Ogre::Vector2(gridPosX, gridPosY);

	fScore = 0;
	gScore = 0;
	hScore = 0;
}

/** Default Destructor */
GridCell::~GridCell()
{
	//delete m_pAppStateManager;
	//delete OgreFramework::getSingletonPtr();
}

/** This Method adds an IGridObject to the grid Cell.
* 
*	@param objPtr A pointer to the IGridObject that has to be added to the GridCell
*/
void GridCell::AddObject(IGridObject* objPtr)
{
	GetSceneNodePtr()->addChild(objPtr->GetSceneNodePtr());
	m_pGridObjects.push_back(objPtr);
	if (objPtr->GetCost() == IGridObject::COST_INFINITE)
	{
		//setPassable(false);
	}
}

std::vector<IGridObject*> GridCell::GetGridObjectList()
{
	return m_pGridObjects;
}

/* Getter for the pathfinding cost of the GridCell
*
*	@return an int representing the pathfinding cost for this GridCell
*/
int GridCell::GetPathCost()
{
	int totalCost = 1;

	for (IGridObject* & obj : m_pGridObjects)
	{
		int cost = obj->GetCost();


		// if the pathing cost is -1 it means you cannot access the Grid Cell
		if (cost < 0)
		{
			return IGridObject::COST_INFINITE;
		}
		else
		{
			m_PathingCost += cost;
		}
	}

	return totalCost;
}

int GridCell::GetPathCostFire()
{
	int totalCost = 5;

	for (IGridObject* & obj : m_pGridObjects)
	{
		int cost = obj->GetCostFire();


		// if the pathing cost is -1 it means you cannot access the Grid Cell
		if (cost < 0)
		{
			return IGridObject::COST_INFINITE;
		}
		else
		{
			pathingCostFire += cost;
		}
	}

	return totalCost;
}

/* Setter for the pathfinding cost of the GridCell
*
*	@param an int representing the pathfinding cost for this GridCell
*/
void GridCell::SetPathCost(int value)
{
	m_PathingCost = value;
}

void GridCell::SetPathCostFire(int value)
{
	pathingCostFire = value;
}

/* Getter for the position in the Grid
*
* @return an Ogre::Vector2 representing the position
*
*/
Ogre::Vector2 GridCell::GetGridPosition()
{
	return gridPosition;
}

/* Getter for getting the fScore
* 
* @return an int representing the fScore
*
*/
int GridCell::getFScore()
{
	return fScore;
}

/* Getter for getting the gScore
* 
* @return an int representing the gScore
*
*/
int GridCell::getGScore()
{
	return gScore;
}

int GridCell::getGScore(GridCell gridCell)
{
	return gridCell.getGScore();
}

/* Getter for getting the hScore
* 
* @return an int representing the hScore
*
*/
int GridCell::getHScore()
{
	return hScore;
}

/* Getter for getting the open value
*
* @return an bool representing the open state of the gridcell
*
*/
bool GridCell::getOpen()
{
	return open;
}

/* Setter for the bool open
*
* @param value The value to set open
*
*/
void GridCell::setOpen(bool value)
{
	open = value;
}

/* Getter for the closed bool
*
* @return closed value
*
*/
bool GridCell::getClosed()
{
	return closed;
}

/* Setter for setting the closed value
*
* @param value the value to set closed
*
*/
void GridCell::setClosed(bool value)
{
	closed = value;
}

/* Getter for the walkable bool
*
* @return the walkable variable
*
*/
bool GridCell::getPassable()
{
	return (GetPathCost() >= 0);
}

/* The setter for the walkable value
*
* @param value The value to set walkable
*
*/
void GridCell::setPassable(bool value)
{
	walkable = value;
}

/* Getter for pointer to scene node 
* 
*	@return A pointer to the Node associated with the Grid point.
*/
Ogre::SceneNode* GridCell::GetSceneNodePtr()
{
	return m_pNode;
}

/* Get the position of the grid node in world space
*
* @return an Ogre::Vector3 object containing the coordinates of the Node in world space
*/
Ogre::Vector3 GridCell::GetWorldPosition()
{
	return m_pNode->getPosition();
}
