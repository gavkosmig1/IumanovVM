#ifndef SHAPE_H
#define SHAPE_H

#include <string>

class Shape {
public:
    explicit Shape(const std::string& name) : m_name(name) {}
    virtual double area() const = 0;
protected:
    std::string m_name;

};

#endif //SHAPE_H