#ifndef Vec3_H
#define Vec3_H
#include <math.h>

class Vec3
{
public:
	Vec3() : x(0), y(0), z(0) {};
	Vec3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {};

	void Add(Vec3 b);

	void Subtract(Vec3 b);

	void ScalarMultiply(float s);

	float Mag();

	Vec3 Normalize();

	float Dot(Vec3 b);

	void Abs();

	Vec3 operator+(const Vec3& other);
	Vec3 operator-(const Vec3& other);

	float x;
	float y;
	float z;
};



#endif