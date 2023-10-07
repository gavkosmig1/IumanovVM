#include <Vector2d.h>
#include <cmath>
double& Vector2d::operator[](unsigned int index)
{
	switch (index) {
	case 0: return x;
	case 1: return y;
	default: throw std::out_of_range{ "Vector2d:index>1" };
	}
};
Vector2d operator+ (Vector2d v1, const Vector2d& v2) {
	return v1 += v2;
}
Vector2d operator- (Vector2d v1, const Vector2d& v2) {
	return v1 -= v2;
}
Vector2d operator* (Vector2d v1, double k) {
	return v1 *= k;
}
Vector2d operator/ (Vector2d v1, double k) {
	return v1 /= k;
}
double dot(const Vector2d& v1, const Vector2d& v2) {
	return v1.x * v2.x + v1.y * v2.y;
}
double cross(const Vector2d& v1, const Vector2d& v2) {
	return v1.x * v2.y - v1.y * v2.x;
}
double length(const Vector2d& v) {
	return pow(dot(v, v), 0.5);
}