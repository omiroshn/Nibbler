#include "Food.hpp"
#include "Graphics.hpp"
#include <random>
#include <ctime>

//=================================================================================================
//	Food
//-------------------------------------------------------------------------------------------------
Food::Food(const std::string& filePath, Vector2 _position, int32_t _x, int32_t _y, int32_t _width, int32_t _heigh)
: eInherited(static_cast<float>(_width / 2), FOOD)
{
	foodTexture		= new Texture(filePath, _x, _y, _width, _heigh);
	mPos			= _position;
	foodTexture->Pos(mPos);
}
//=================================================================================================
//	~Food
//-------------------------------------------------------------------------------------------------
Food::~Food()
{
	if(foodTexture)
	{
		delete foodTexture;
		foodTexture = nullptr;
	}
}
//=================================================================================================
// Update
//-------------------------------------------------------------------------------------------------
void Food::Update()
{
	foodTexture->Pos(mPos);
	foodTexture->Update();
}
//=================================================================================================
// Render
//-------------------------------------------------------------------------------------------------
void Food::Render()
{
	foodTexture->Render();
}
//=================================================================================================
// ReSpawn
//-------------------------------------------------------------------------------------------------
void Food::ReSpawn()
{
	// 32 -> wall texture size
	srand(time(0));
	// $todo: use parameters from level data for width and heigh of the level
	// $todo: find max width and height which is multiple times 32 (% 32 == 0)
	// $todo: check if square is empty

	int32_t x = 32 + (32 * rand()) % Graphics::WIDTH;
	int32_t y = 32 + (32 * rand()) % Graphics::HEIGHT;

	//like this
	//int32_t x = 32 + (32 * rand()) % 416;
	//int32_t y = 32 + (32 * rand()) % 416;
	Pos(Vector2(static_cast<float>(x), static_cast<float>(y)));
}