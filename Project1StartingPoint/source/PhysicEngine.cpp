#include "PhysicEngine.h"
#include <stdlib.h>

PhysicEngine::PhysicEngine()
{
	//Pos.set_X(0.f);
	//Pos.set_Y(0.f);
	//Pos.set_Z(0.f);

	Pos = vector3(0, 0, 0);
	Velocity = vector3(0, 0, 0);
	Acc = vector3(0, GFORCE, 0);
	FireDirection = vector3(0, 0, 0);

	mass = 0;
	isFire = false;
}

PhysicEngine::~PhysicEngine()
{
}

void PhysicEngine::RandPos()
{
	Pos.set_X((float)(rand() % 40 - 20));
	Pos.set_Y(0.f);
	Pos.set_Z((float)(rand() % 40 - 20));
}
float PhysicEngine::TrajectoryCal()
{
	return 0.0f;
}
//
//
//int Position::Get_XPos()
//{
//	return x;
//}
//
//int Position::Get_ZPos()
//{
//	return z;
//}
