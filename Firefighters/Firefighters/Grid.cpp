//|||||||||||||||||||||||||||||||||||||||||||||||

#include "Grid.hpp"
#include "GridCell.hpp"

template <>
Grid* Ogre::Singleton<Grid>::msSingleton = 0;

Grid::Grid(int& sizeX, int& sizeZ, Ogre::SceneManager* pSceneManager)
{
	m_sizeX = sizeX;
	m_sizeZ = sizeZ;

	// Give the 2D-array the appropriate size
	grid = new GridCell*[sizeX];
	for (int i = 0; i < m_sizeX; i++)
	{
		grid[i] = new GridCell[sizeZ];
	}

	// Calculate the middlepoint of the level so it's the origin (0, 0, 0)	
	if (sizeX % 2 == 0)
		m_worldPosX = 64 - ((m_sizeX / 2) * 128);
	else
		m_worldPosX = 0 - ((m_sizeX / 2) * 128);

	if (sizeZ % 2 == 0)
		m_worldPosZ = 64 - ((m_sizeZ / 2) * 128);
	else
		m_worldPosZ = 0 - ((m_sizeZ / 2) * 128);

	// Create a grid cell for each element in the 'grid' array
	for (int x = 0; x < m_sizeX; x++)
	{
		for (int y = 0; y < m_sizeZ; y++)
		{
			grid[x][y] = *new GridCell(x, y, m_worldPosX, m_worldPosZ, pSceneManager);
			m_worldPosZ += 128;
		}
		m_worldPosX += 128;

		if (sizeZ % 2 == 0)
			m_worldPosZ = 64 - ((m_sizeZ / 2) * 128);
		else
			m_worldPosZ = 0 - ((m_sizeZ / 2) * 128);
	}
}

int Grid::getRows()
{
	return m_sizeX;
}

int Grid::getColumns()
{
	return m_sizeZ;
}

/** Default Destructor */
Grid::~Grid()
{
	//delete OgreFramework::getSingletonPtr();
}


bool Grid::inBounds(GridCell* gridCell)
{
	return inBounds(gridCell->GetGridPosition());
}

bool Grid::inBounds(Ogre::Vector2 gridPos)
{
	return 0 <= gridPos.x && gridPos.x < m_sizeX && 0 <= gridPos.y && gridPos.y < m_sizeZ;
}

bool Grid::isPassable(GridCell* cell)
{
	return isPassable(cell->GetGridPosition());
}

bool Grid::isPassable(Ogre::Vector2 cellPos)
{
	return !inpassables.count(cellPos);
}

void Grid::updatePassables()
{
	inpassables.clear();
	for (int i = 0; i < m_sizeX; i++)
	{
		for (int j = 0; j < m_sizeZ; j++)
		{
			if (!grid[i][j].getPassable())
			{
				inpassables.insert(grid[i][j].GetGridPosition());
			}
		}
	}
}


//|||||||||||||||||||||||||||||||||||||||||||||||
