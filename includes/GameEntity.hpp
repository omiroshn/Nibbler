#ifndef _GAMEENTITY_HPP
#define _GAMEENTITY_HPP
#include "MathHelper.hpp"
#include <memory>

//**************************************************************************************************
//	GameEntity
//--------------------------------------------------------------------------------------------------
class GameEntity
{

public:
	GameEntity(float x = 0.0f, float y = 0.0f);
	virtual ~GameEntity();

	void			Pos(Vector2 pos);
	Vector2			Pos();

	void			setRotation(float rot);
	float			getRotation();

	void			setActive(bool active);
	bool			getActive();

	virtual void	Translate(Vector2 vec);

	void			setScale(Vector2 scale);
	Vector2			getScale();

	Vector2			Direction()						{ return mDirection;		}
	void			Direction(Vector2 dir)			{ mDirection = dir;			}

	void			Update();
	void			Render();

protected:

	bool		mActive;
	float		mRadius;
	float		mRotation;
	Vector2		mDirection;
	Vector2		mPos;
	Vector2		mScale;

};

#endif