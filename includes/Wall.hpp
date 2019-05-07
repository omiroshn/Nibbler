#ifndef WALL_HPP
#define WALL_HPP

#include "Collider.hpp"
#include "Texture.hpp"

//**************************************************************************************************
//	Wall
//--------------------------------------------------------------------------------------------------
class Wall : public Collider
{
	using eInherited = Collider;
public:
	Wall(const std::string& filePath, Vector2 position, int32_t _x, int32_t _y, int32_t _width, int32_t _heigh);
	virtual			~Wall();

	void			Update();
	void			Render();
protected:
	Texture*		wallTexture; 
};

#endif