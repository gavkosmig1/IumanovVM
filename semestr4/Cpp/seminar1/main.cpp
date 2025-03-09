#include <iostream>
#include <memory>
#include "rectangle.h"
#include "circle.h"
#include "triangle.h"

int main() {
    std::unique_ptr<Shape> shapes[] = {
        std::make_unique<Rectangle>(10, 20),
        std::make_unique<Circle>(3),
        std::make_unique<Triangle>(3, 4, 5)
    };

    double sum = 0.0;
    for (const std::unique_ptr<Shape>& shape : shapes) {
        sum += shape -> area();
    }
    std::cout << sum << std::endl;

    return 0;

}
