#include "GameEntity.hpp"

//**************************************************************************************************
//	GameEntity::GameEntity
//--------------------------------------------------------------------------------------------------
GameEntity::GameEntity(float x, float y)
{
	mPos.x				= x;
	mPos.y				= y;
	mDirection			= Vector2(0.0f, 0.0f);
	mRotation			= 0.0f;
	mActive				= true;
}
//==================================================================================================
//	GameEntity::~GameEntity
//--------------------------------------------------------------------------------------------------
GameEntity::~GameEntity()
{
}
//==================================================================================================
//	GameEntity::Pos
//--------------------------------------------------------------------------------------------------
void GameEntity::Pos(Vector2 pos)
{
	mPos = pos;
}
//==================================================================================================
//	GameEntity::Pos
//--------------------------------------------------------------------------------------------------
Vector2 GameEntity::Pos()
{
	return mPos;
}
//==================================================================================================
//	GameEntity::setRotation
//--------------------------------------------------------------------------------------------------
void GameEntity::setRotation(float r)
{
	mRotation = r;

	if(mRotation > 360.0f)
	{
		float mul = mRotation / 360;
		mRotation -= 360.0f * mul;
	}
	else if(mRotation < 0.0f)
	{
		float mul = (mRotation / 360) - 1;
		mRotation -= 360.0f * mul;
	}
}
//==================================================================================================
//	GameEntity::getRotation
//--------------------------------------------------------------------------------------------------
float GameEntity::getRotation()
{
	return mRotation;
}
//==================================================================================================
//	GameEntity::setActive
//--------------------------------------------------------------------------------------------------
void GameEntity::setActive(bool active)
{
	mActive = active;
}
//==================================================================================================
//	GameEntity::getActive
//--------------------------------------------------------------------------------------------------
bool GameEntity::getActive()
{
	return mActive;
}


void GameEntity::Update()
{}

void GameEntity::Render()
{}

void GameEntity::Translate(Vector2 vec)
{
	mPos += vec;
}

void GameEntity::setScale(Vector2 scale)
{
	mScale = scale;
}
//==================================================================================================
//	GameEntity::getScale
//--------------------------------------------------------------------------------------------------
Vector2 GameEntity::getScale()
{
	return mScale;
}