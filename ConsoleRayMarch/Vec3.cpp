#include "Vec3.h"
#include <cmath>
using namespace std;
void Vec3::Add(Vec3 b)
{
	x = x + b.x;
	y = y + b.y;
	z = z + b.z;
}

void Vec3::Subtract(Vec3 b)
{
	x = x - b.x;
	y = y - b.y;
	z = z - b.z;
}

void Vec3::ScalarMultiply(float s)
{
	x = x * s;
	y = y * s;
	z = z * s;
}

float Vec3::Mag()
{
	return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

Vec3 Vec3::Normalize()
{
	float mag = this->Mag();
	return Vec3(x / mag, y / mag, z / mag);
}

void Vec3::Abs()
{
	x = abs(x);
	y = abs(y);
	z = abs(z);
}
float Vec3::Dot(Vec3 b)
{
	return x * b.x + y * b.y + z * b.z;
}

Vec3 Vec3::operator+(const Vec3& other)
{
	Vec3 copy = Vec3(x, y, z);
	copy.Add(other);
	return copy;
}

Vec3 Vec3::operator-(const Vec3& other)
{
	Vec3 copy = Vec3(x, y, z);
	copy.Subtract(other);
	return copy;
}