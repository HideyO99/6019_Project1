#include "PhysicEngine.h"
#include <stdlib.h>

PhysicEngine::PhysicEngine()
{

	Pos = vector3(0, 0, 0);
	Velocity = vector3(0, 0, 0);
	Acc = vector3(0, GFORCE, 0);
	FireDirection = vector3(0, 0, 0);

	ProjectileType = 1;
	isFire = false;
	isHitGround = false;
	VelecityXYZ = 0;
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
void PhysicEngine::TrajectoryCal()
{
	float YPos = this->Pos.get_Y();
	if (YPos >= 0.f)
	{
		this->Pos += (this->FireDirection / 100);
		// v=u+at
		this->Velocity = this->Velocity + this->Acc / 100;
		this->Pos.set_Y(YPos + this->Velocity.get_Y() / 100);
	}
	else {
		this->isFire = false;
		this->isHitGround = true;
		this->Pos.set_Y(0.f);
	}

}

bool PhysicEngine::isHitTarget()
{
	return false;
}

