#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include "GameEntity.hpp"

//=================================================================================================
//	for this project it will be only Circle-Circle collision, so we do not need enum with
//	other collider types, only a CollideType to interact with different entities
//-------------------------------------------------------------------------------------------------
class Collider : public GameEntity
{
public:
	enum	CollideType
	{
		PLAYER = 1,
		FOOD,
		WALL,

		UNKNOWN		= -1
	};
public:
	Collider(float radius, CollideType type = UNKNOWN);
	virtual			~Collider();

	float			Radius()			const			{ return mRadius;		}
	CollideType		GetCollideType()	const			{ return mColliderType;	}
	bool			CheckCircleCollision(Collider&, Collider&);
	bool			CheckCircleCollision(const Vector2&, const Vector2&, float firstEntityRadius, float secondEntityRadius);
	
protected:
	float		mRadius;
	CollideType	mColliderType;
};

#endif