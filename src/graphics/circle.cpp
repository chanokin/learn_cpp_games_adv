#include "circle.hpp"
#include "math_utils.hpp"

Circle::Circle(): Circle(Vec2D::ZERO, 0.0f){
}

Circle::Circle(const Vec2D& center, const float& radius){
    _points.push_back(center);
    _radius = radius;
}

bool Circle::intersects(const Circle& c) const{
    return _points[0].distance(c.center()) < (_radius + c.radius());
}

bool Circle::contains(const Vec2D& p) const{
    return leq_float(_points[0].distance(p), _radius);
}
