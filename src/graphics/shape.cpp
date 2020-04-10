#include "shape.hpp"
#include <iostream>

void Shape::move(const Vec2D& step){
    for(Vec2D& p : _points){
        p += step;
    }
}

