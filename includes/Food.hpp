#ifndef FOOD_HPP
#define FOOD_HPP

#include "Collider.hpp"
#include "Texture.hpp"

// $todo: make a diffent type of food. inherit from foodBase class (maybe)

//**************************************************************************************************
//	Food
//--------------------------------------------------------------------------------------------------
class Food : public Collider
{
	using eInherited = Collider;
public:
	Food(const std::string& filePath, Vector2 position, int32_t _x, int32_t _y, int32_t _width, int32_t _heigh);
	~Food();

	void			SetRespawnDementions(int32_t width, int32_t height);
	int32_t			FoodValue() const { return foodValue; }

	void			Update();
	void			Render();
	
	void			ReSpawn();
protected:

	int32_t						foodValue;
	int32_t						mWidth;
	int32_t						mHeight;
	std::unique_ptr<Texture>	foodTexture;
};

#endif