#ifndef __Grid_hpp_
#define __Grid_hpp_

//|||||||||||||||||||||||||||||||||||||||||||||||

#include "AdvancedOgreFramework.hpp"
#include "GridCell.hpp"

/** A Class to represent the game's grid.
*  
*	The game is grid-based with the firefighters moving along said grid. This Class is a representation of the grid. We use {@Link GridCell} to store
*	information about every square in the grid.
*	
*	The game is based on a 2D grid. To represent each grid, we use a class called GridCell. We use a 2D array to store these objects. 
*	Each GridCell has a list of IGridObjects attached to its grid. In order for an object to be attached to one of these GridCells they must implement the interface. 
*	This implementation can be used to iterate through a grid cell's objects. This is useful for calculating pathing cost.
*	The Grid has been made into a singleton since our game only needs one grid. This also makes the grid globally accessable.
*/
class Grid : public Ogre::Singleton<Grid>
{
public:
	// Constructors/Destructor
	Grid(int& sizeX, int& sizeZ, Ogre::SceneManager* pSceneManager);
	~Grid(void);

	// Public member vars
	GridCell** grid; /** 2D array to represent our grid */
	int getRows();
	int getColumns();

	// Public member functions
	std::unordered_set<GridCell*> GetInpassables(); /** Get all impassable GridCells */
	bool inBounds(GridCell* cell);
	bool inBounds(Ogre::Vector2 cellPos);
	bool isPassable(GridCell* cell);
	bool isPassable(Ogre::Vector2 cellPos);
	void updatePassables();

protected:


private:
	// Member variables
	int m_sizeX, m_sizeZ; /** The dimentions of our Grid */
	float m_worldPosX, m_worldPosZ; /** The middle of a GridCell (Used for creation)*/
	std::unordered_set<Ogre::Vector2> inpassables; /** A set containing all GridCells that are inpassable */
};

//|||||||||||||||||||||||||||||||||||||||||||||||

#endif

//|||||||||||||||||||||||||||||||||||||||||||||||
