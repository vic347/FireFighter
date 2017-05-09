#ifndef __LevelGenerator_hpp_
#define __LevelGenerator_hpp_

//|||||||||||||||||||||||||||||||||||||||||||||||

#include "AdvancedOgreFramework.hpp"
#include "FireFighter.hpp"
#include "FireTruck.hpp"
#include "Ground.hpp"
#include "Fire.hpp"
#include "Wall.hpp"
#include "Grid.hpp"
#include "Door.hpp"
#include "Lighting.hpp"

/** Level Generation class
*  
*	This class is used to read a txt file and generate a level based
*	on the characters in that txt file.
*/
class LevelGenerator : public Ogre::Singleton<LevelGenerator>
{
public:
	// Constructors/Destructor
	LevelGenerator(int SizeX, int SizeZ, Ogre::String levelFile);
	~LevelGenerator(void);

	void SaveFile();
	void LoadFile(Ogre::String levelFile, char** level);
	void GenerateLevel(char** level);

protected:


private:
	int sizeX, sizeZ;
};

//|||||||||||||||||||||||||||||||||||||||||||||||

#endif

//|||||||||||||||||||||||||||||||||||||||||||||||
