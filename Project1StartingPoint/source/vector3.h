#pragma once
class vector3
{
public:
	vector3();
	~vector3();

	vector3(float x, float y, float z);
	vector3(float value);

	float get_X();
	float get_Y();
	float get_Z();

	void set_X(float value);
	void set_Y(float value);
	void set_Z(float value);
	vector3& operator=(const vector3& RHS);
	vector3 operator+(const vector3& RHS);
	vector3 operator-(const vector3& RHS);
	vector3 operator*(const float RHS);
	vector3 operator/(const float RHS);
	void operator+=(const vector3& RHS);
	void operator-=(const vector3& RHS);
	void operator*=(const float RHS);
	void operator/=(const float RHS);


private:
	float x;
	float y;
	float z;
};

