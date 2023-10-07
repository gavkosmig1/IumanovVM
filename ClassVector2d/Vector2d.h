#include <iostream>

class Vector2d {
public:
	int a = 0, b = 0;
	double x{ 0 }, y{ 0 };
	Vector2d() = default;
	Vector2d(double xx, double yy)
		:x{ xx }, y{ yy } {}

	double& operator[] (unsigned int index);

	Vector2d& operator+= (const Vector2d& v) {
		x += v.x;
		y += v.y;
		return *this;
	}
	Vector2d& operator-= (const Vector2d& v) {
		x -= v.x;
		y -= v.y;
		return *this;
	}
	Vector2d& operator*= (double k) {
		x *= k;
		y *= k;
		return *this;
	}
	Vector2d& operator/= (double k) {
		x /= k;
		y /= k;
		return *this;
	}
};
Vector2d operator+ (Vector2d v1, const Vector2d& v2);
Vector2d operator- (Vector2d v1, const Vector2d& v2);
Vector2d operator* (Vector2d v1, double k);
Vector2d operator/ (Vector2d v1, double k);
double dot(const Vector2d& v1, const Vector2d& v2);
double cross(const Vector2d& v1, const Vector2d& v2);
double length(const Vector2d& v);