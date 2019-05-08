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
	foodValue		= 10;
	mWidth			= 0;
	mHeight			= 0;
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
// SetRespawnDementions
//-------------------------------------------------------------------------------------------------
void Food::SetRespawnDementions(int32_t _width, int32_t _height)
{
	// 32 -> wall texture size
	while (mWidth < _width - 64)
	{
		mWidth += 32;
	}
	while (mHeight < _height - 64)
	{
		mHeight += 32;
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
	// $todo: check if square is empty

	int32_t x = 32 + (32 * rand()) % mWidth;
	int32_t y = 32 + (32 * rand()) % mHeight;

	Pos(Vector2(static_cast<float>(x), static_cast<float>(y)));
}