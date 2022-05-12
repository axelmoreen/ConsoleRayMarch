#pragma once
#include "Math.h"
#include "Vec3.h"



Vec3 RotX(Vec3 vec, float theta) {
	Vec3 out(
		vec.x, 
		cos(theta) * vec.y -sin(theta) * vec.z,
		sin(theta) * vec.y + cos(theta) * vec.z
	);

	return out;
}

Vec3 RotY(Vec3 vec, float theta) {
	Vec3 out(
		cos(theta) * vec.x + sin(theta) * vec.z,
		vec.y,
		-sin(theta) * vec.x + cos(theta) * vec.z
	);
	return out;
}

Vec3 RotZ(Vec3 vec, float theta) {
	Vec3 out(
		cos(theta) * vec.x - sin(theta) * vec.y,
		sin(theta) * vec.x + cos(theta) * vec.y,
		vec.z
	);
	return out;
}

float length(float v1, float v2) {
	return sqrt(pow(v1, 2) + pow(v2, 2));
}


float sdfSphere(Vec3 p, Vec3 c, float r) {
	return (p - c).Mag() - r;
}

float sdfCube(Vec3 p, Vec3 b, Vec3 offset, float rotX, float rotY, float rotZ) {
	Vec3 q = p - offset;
	q = RotX(q, rotX);
	q = RotY(q, rotY);
	q = RotZ(q, rotZ);
	q.Abs();
	Vec3 d = q - b;
	return min(max(d.x, max(d.y, d.z)), 0.0 + max(d.Mag(),0.0));
}

float sdfTorus(Vec3 p, float tX, float tY, float rotX, float rotY, float rotZ) {
	p = RotX(p, rotX);
	p = RotY(p, rotY);
	p = RotZ(p, rotZ);
	float qX = length(p.x, p.z) - tX;
	float qY = p.y;
	return length(qX, qY) - tY;
}
