#include "Level.hpp"
#include <fstream>
#include <string>

//=================================================================================================
//	Level
//-------------------------------------------------------------------------------------------------
Level::Level()
{}
//=================================================================================================
//	~Level
//-------------------------------------------------------------------------------------------------
Level::~Level()
{}
//=================================================================================================
//	LoadLevel
//-------------------------------------------------------------------------------------------------
bool Level::LoadLevel(const std::string& _fileName)
{
	std::string fullpath;
	fullpath.append("resourses/maps/" + _fileName);
	std::ifstream file;

	file.open(fullpath.c_str());
	if(file.fail())
	{
		perror(fullpath.c_str());
		return false;
	}
	std::string line;
	while(std::getline(file, line))
	{
		if(!line.empty())
		{
			levelMap.push_back(line);
		}
	}
	file.close();
	return true;
}
//=================================================================================================
//	ParseLevel
//-------------------------------------------------------------------------------------------------
bool Level::ParseLevel()
{
	// $todo remove magic numbers
	char tile;
	for(size_t y = 0; y < levelMap.size(); ++y)
	{
		for(size_t x = 0; x < levelMap[y].size(); ++x)
		{
			tile = levelMap[y][x];
			switch(tile)
			{
			case 'W':	wallsPosition.push_back(Vector2(static_cast<float>(x * 32), static_cast<float>(y * 32)));	break;
			case 'X':	playerPosition = Vector2(static_cast<float>(x * 32), static_cast<float>(y * 32));			break;
			case '.':
			case ' ':	break;
			default:
				std::cout << "Unexpected Symbol: " << tile << " at x:" << x << ", y:" << y << "\n";
			break;
			}
		}
	}
	return true;
}
//=================================================================================================
//	PlayerPosition
//-------------------------------------------------------------------------------------------------
Vector2 Level::PlayerPosition() const
{
	return playerPosition;
}
//=================================================================================================
//	WallsPosition
//-------------------------------------------------------------------------------------------------
std::vector<Vector2> Level::WallsPosition() const
{
	return wallsPosition;
}
//=================================================================================================
//	LevelWidth
//-------------------------------------------------------------------------------------------------
int32_t Level::LevelWidth() const
{
	if (!levelMap.empty())
	{
		return levelMap.front().size() * 32;
	}
	return 0;
}
//=================================================================================================
//	LevelHeight
//-------------------------------------------------------------------------------------------------
int32_t Level::LevelHeight() const
{
	if (!levelMap.empty())
	{
		return levelMap.size() * 32;
	}
	return 0;
}
