#include "rectangle.h"

Rectangle::Rectangle(double width, double height)
: Shape("Rectangle"), m_width(width), m_height(height) {}

double Rectangle::area() const {
    return m_width * m_height;
}