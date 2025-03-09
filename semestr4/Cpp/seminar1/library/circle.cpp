#include "circle.h"

Circle::Circle(double radius) : Shape("Circle"), m_radius(radius) {}

double Circle::area() const {
    return M_PI * m_radius * m_radius;
}