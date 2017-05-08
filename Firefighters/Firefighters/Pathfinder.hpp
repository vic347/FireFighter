#ifndef __Pathfinder_hpp_
#define __Pathfinder_hpp_

#include "GridCell.hpp"

/** This class is used for pathfinding of Players and NPCs.
*
*	For now we are implementing breath-first search for our pathfinding needs.
*
*	source: http://www.redblobgames.com/pathfinding/a-star/introduction.html
*/
class Pathfinder : public Ogre::Singleton<Pathfinder>
{
public:
	//Constructors/Destructor
	Pathfinder(void);
	~Pathfinder(void);

	//Member Functions
	std::vector<Ogre::Vector2> FindPath(GridCell* start, GridCell* goal);

private:
	// Constants
	static const std::array<Ogre::Vector2, 4> DIRS;

	// Member Vars
	std::unordered_map<Ogre::Vector2, Ogre::Vector2> visited; /** The GridCells we have visisted */

	// Member Functions
	std::vector<Ogre::Vector2> getNeighbours(Ogre::Vector2 position);
	std::vector<Ogre::Vector2> getNeighbours(GridCell* gridCell);
	std::vector<Ogre::Vector2> reconstructPath(std::unordered_map<Ogre::Vector2, Ogre::Vector2> cameFrom, Ogre::Vector2 start, Ogre::Vector2 goal);
	void init();
};


#endif
