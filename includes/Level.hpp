#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "MathHelper.hpp"
#include <iostream>
#include <vector>

//**************************************************************************************************
//	Level
//--------------------------------------------------------------------------------------------------
class Level
{
public:
	Level();
	virtual ~Level();

	bool						ParseLevel();
	bool						LoadLevel(const std::string& fileName);
	Vector2						PlayerPosition()	const;
	std::vector<Vector2>		WallsPosition()		const;
	int32_t						LevelWidth()		const;
	int32_t						LevelHeight()		const;

protected:
	Vector2						playerPosition;
	std::vector<Vector2>		wallsPosition;
	std::vector<std::string>	levelMap;
};

#endif