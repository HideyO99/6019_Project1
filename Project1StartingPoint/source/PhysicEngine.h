#pragma once

#include "vector3.h"

#define GFORCE -9.8f
//enum BulletVelocity
//{
//
//
//};
class PhysicEngine
{
public:
	PhysicEngine();
	~PhysicEngine();

	void RandPos();
	vector3 Pos;
	vector3 Velocity;
	vector3 Acc;
	vector3 FireDirection;
	void TrajectoryCal();

	//float mass;
	bool isFire;
	float ProjectileType;
	bool isHitGround;
	bool isHitTarget();

};

