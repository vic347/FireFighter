#include "LevelGenerator.hpp"
#include <fstream>

template <>
LevelGenerator* Ogre::Singleton<LevelGenerator>::msSingleton = 0;
using namespace std;

/** Constructor for the level generator
*
*	The constructor makes an 2D-array and then goes to LoadFile function which reads the text file
*	
*	@param SizeX The grid size on the X-axis
*	@param SizeZ The grid size on the Z-axis
*	@param levelFile The string which defines the txt file
*/
LevelGenerator::LevelGenerator(int SizeX, int SizeZ, Ogre::String levelFile)
{
	sizeX = SizeX;
	sizeZ = SizeZ;

	// Open the textfile and allocate the array
	char** level = new char*[sizeX];
	for (int iSize = 0; iSize < sizeX; iSize++)
		level[iSize] = new char[sizeZ];

	// Use the array
	LoadFile(levelFile, level);

	// Deallocate the array and close txtFile
	for (int iSize = 0; iSize < sizeX; iSize++)
		delete[] level[iSize];
	delete[] level;
}

LevelGenerator::~LevelGenerator()
{
}

//void LevelGenerator::SaveFile()
//{
//    for (unsigned jSize = 0; jSize < sizeZ; ++jSize)
//        for (unsigned iSize = 0; iSize < sizeX; ++iSize)
//            txtFile << Data[iSize][jSize] << " "; 
//}

/** LoadFile function in LevelGenerator
*
*	This function loads the file and puts the data into the array
*	
*	@param levelFile The string which defines the txt file
*	@param **level The 2D-array to hold the text file
*/
void LevelGenerator::LoadFile(Ogre::String levelFile, char** level)
{
	ifstream txtFile;
	txtFile.open(levelFile);
	if (txtFile.is_open())
	{
		for (int jSize = 0; jSize < sizeZ; ++jSize)
		{
			for (int iSize = 0; iSize < sizeX; ++iSize)
			{
				txtFile >> level[iSize][jSize];
			}
		}
	}
	GenerateLevel(level);
	txtFile.close();
}

/** GenerateLevel function in LevelGenerator
*
*	This function loops through the array and creates objects based on the character
*	
*	@param **level The 2D-array to hold the text file
*/
void LevelGenerator::GenerateLevel(char** level)
{
	for (int iSize = 0; iSize < sizeX; iSize++)
	{
		for (int jSize = 0; jSize < sizeZ; jSize++)
		{
			char object = level[iSize][jSize];

			switch (object)
			{
			case 'W': // Wall
				Grid::getSingletonPtr()->grid[iSize][jSize].AddObject(new Wall(Ogre::Vector3(0, 0, 0), Ogre::Vector2(iSize, jSize)));
				break;
			case 'P': // Player
				Grid::getSingletonPtr()->grid[iSize][jSize].AddObject(new Ground(Ogre::Vector3(0, 0, 0), Ogre::Vector2(iSize, jSize)));
				//Grid::getSingletonPtr()->grid[iSize][jSize].AddObject(new FireFighter(Ogre::Vector3(0,0,0), Ogre::Vector2(iSize, jSize)));
				new FireFighter(Grid::getSingletonPtr()->grid[iSize][jSize].GetWorldPosition(), Ogre::Vector2(iSize, jSize));
				break;
			case 'F': // Fire
				Grid::getSingletonPtr()->grid[iSize][jSize].AddObject(new Ground(Ogre::Vector3(0, 0, 0), Ogre::Vector2(iSize, jSize)));
				Grid::getSingletonPtr()->grid[iSize][jSize].AddObject(new Fire(Ogre::Vector3(0, 0, 0), Ogre::Vector2(iSize, jSize)));
				break;
			case 'H': // FireTruck, horizontal
				Grid::getSingletonPtr()->grid[iSize][jSize].AddObject(new FireTruck(Ogre::Vector3(0, 64, 0), Ogre::Vector2(iSize, jSize), 0.0f));
				break;
			case 'V': // FireTruck, Vertical
				Grid::getSingletonPtr()->grid[iSize][jSize].AddObject(new FireTruck(Ogre::Vector3(0, 64, 0), Ogre::Vector2(iSize, jSize), 90.0f));
				break;
			case 'R': // Door, Right side of gridcell
				Grid::getSingletonPtr()->grid[iSize][jSize].AddObject(new Ground(Ogre::Vector3(0, 0, 0), Ogre::Vector2(iSize, jSize)));
				Grid::getSingletonPtr()->grid[iSize][jSize].AddObject(new Door(Ogre::Vector3(64, 0, 0), Ogre::Vector2(iSize, jSize), false, 0, 1));
				break;
			case 'L': // Door, Left side of gridcell
				Grid::getSingletonPtr()->grid[iSize][jSize].AddObject(new Ground(Ogre::Vector3(0, 0, 0), Ogre::Vector2(iSize, jSize)));
				Grid::getSingletonPtr()->grid[iSize][jSize].AddObject(new Door(Ogre::Vector3(-64, 0, 0), Ogre::Vector2(iSize, jSize), false, 0, 2));
				break;
			case 'B': // Door, Bottom side of gridcell
				Grid::getSingletonPtr()->grid[iSize][jSize].AddObject(new Ground(Ogre::Vector3(0, 0, 0), Ogre::Vector2(iSize, jSize)));
				Grid::getSingletonPtr()->grid[iSize][jSize].AddObject(new Door(Ogre::Vector3(0, 0, 64), Ogre::Vector2(iSize, jSize), false, 90, 3));
				break;
			case 'T': // Door, Top side of gridcell
				Grid::getSingletonPtr()->grid[iSize][jSize].AddObject(new Ground(Ogre::Vector3(0, 0, 0), Ogre::Vector2(iSize, jSize)));
				Grid::getSingletonPtr()->grid[iSize][jSize].AddObject(new Door(Ogre::Vector3(0, 0, -64), Ogre::Vector2(iSize, jSize), false, 90, 4));
				break;
			case 'S': // Smoke particles
				Grid::getSingletonPtr()->grid[iSize][jSize].AddObject(new Ground(Ogre::Vector3(0, 0, 0), Ogre::Vector2(iSize, jSize)));
				// Add logic
				break;
			case '-': // Nothing
				Grid::getSingletonPtr()->grid[iSize][jSize].AddObject(new Ground(Ogre::Vector3(0, 0, 0), Ogre::Vector2(iSize, jSize)));
				break;
			default:
				break;
			}
		}
	}

	Ogre::Vector3 roomLightPos1 = Grid::getSingletonPtr()->grid[5][5].GetWorldPosition();
	Ogre::Vector3 roomLightPos2 = Grid::getSingletonPtr()->grid[5][9].GetWorldPosition();

	Lighting* lights = new Lighting();
	lights->CreateRoomLight(roomLightPos1);
	lights->CreateRoomLight(roomLightPos2);
	lights->CreateDaylight();
	//lights->CreateNightlight();
}
