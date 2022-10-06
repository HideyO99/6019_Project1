#include "vector3.h"

vector3::vector3()
{
	x = 0.f;
	y = 0.f;
	z = 0.f;
}

vector3::~vector3()
{
}

vector3::vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

vector3::vector3(float value)
{
	this->x = value;
	this->y = value;
	this->z = value;
}

float vector3::get_X()
{
	return x;
}

float vector3::get_Y()
{
	return y;
}

float vector3::get_Z()
{
	return z;
}

void vector3::set_X(float value)
{
	this->x = value;
}

void vector3::set_Y(float value)
{
	this->y = value;
}

void vector3::set_Z(float value)
{
	this->z = value;
}

vector3& vector3::operator=(const vector3& RHS)
{
	x = RHS.x;
	y = RHS.y;
	z = RHS.z;
	return *this;
}

vector3 vector3::operator+(const vector3& RHS)
{
	return vector3(x + RHS.x, y + RHS.y, z + RHS.z);
}

vector3 vector3::operator-(const vector3& RHS)
{
	return vector3(x - RHS.x, y - RHS.y, z - RHS.z);
}

vector3 vector3::operator*(const float RHS)
{
	return vector3(x * RHS, y * RHS, z * RHS);
}

vector3 vector3::operator/(const float RHS)
{
	return vector3(x / RHS, y / RHS, z / RHS);
}

void vector3::operator+=(const vector3& RHS)
{
	this->x += RHS.x;
	this->y += RHS.y;
	this->z += RHS.z;
}

void vector3::operator-=(const vector3& RHS)
{
	this->x -= RHS.x;
	this->y -= RHS.y;
	this->z -= RHS.z;
}

void vector3::operator*=(const float RHS)
{
	this->x *= RHS;
	this->y *= RHS;
	this->z *= RHS;
}

void vector3::operator/=(const float RHS)
{
	this->x /= RHS;
	this->y /= RHS;
	this->z /= RHS;
}


