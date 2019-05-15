#include "Collider.hpp"
#include <iostream>

//=================================================================================================
//	Collider
//-------------------------------------------------------------------------------------------------
Collider::Collider(float _radius, CollideType _type)
: mRadius(_radius)
, mColliderType(_type)
{}
//=================================================================================================
//	~Collider
//-------------------------------------------------------------------------------------------------
Collider::~Collider()
{}
//=================================================================================================
// CheckCircleCollision
//-------------------------------------------------------------------------------------------------
bool Collider::CheckCircleCollision(Collider& _ent1, Collider& _ent2)
{
	return (_ent1.Pos() - _ent2.Pos()).Magnitude() < (_ent1.Radius() + _ent2.Radius());
}
//=================================================================================================
// CheckCircleCollision
//-------------------------------------------------------------------------------------------------
bool Collider::CheckCircleCollision(const Vector2& _vec1, const Vector2& _vec2, float _firstEntityRadius, float _secondEntityRadius)
{
	return (_vec1 - _vec2).Magnitude() < (_firstEntityRadius + _secondEntityRadius);
}