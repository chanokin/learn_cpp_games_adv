#include "circle.hpp"

Circle::Circle(): Circle(Vec2D::ZERO, 0.0f){
}

Circle::Circle(const Vec2D& center, const float& radius){
    _points.reserve(1);
    _poinst[0] = center;
    _radius = radius;
}

bool Circle::intersects(const Circle& c){
    return _points[0].distance(c.center()) < (_radius + c.radius())
}

bool Circle::contains(const Vec2D p){
    return leq_float(_points[0].distance(p) < _radius);
}
