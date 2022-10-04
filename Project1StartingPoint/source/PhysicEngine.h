#pragma once

#include "vector3.h"

#define GFORCE 9.8f
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
	float TrajectoryCal();

	float mass;
	bool isFire;

//	int Get_XPos();
//	int Get_ZPos();
//private:
//	int x;
//	int y;
//	int z;
};

