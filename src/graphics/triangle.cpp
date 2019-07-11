#include "triangle.hpp"

Triangle::Triangle(): Triangle(Vec2D::ZERO, Vec2D::ZERO, Vec2D::ZERO){

}

Triangle::Triangle(const Vec2D& p0, const Vec2D& p1, const Vec2D& p2){
    _points.reserve(3);
    _points[0] = p0;
    _points[1] = p1;
    _points[2] = p2;
}

virtual Vec2D Triangle::getCenter() const{
    Vec2D half = (_points[0]+_points[1]) * 0.5f;
    Vec2D center = (half + _points[2]) * 0.666666f;
}

float Triangle::area() const{
    return area(_points[0], _points[1], _points[2]);
}

bool Triangle::contains(const Vec2D& p) const{
    float myArea = area();
    float p0Area = area(p, _points[1], _points[2]);
    float p1Area = area(_points[0], p, _points[2]);
    float p2Area = area(_points[0], _points[1], p);
    return eq_float(p0Area + p1Area + p2Area, myArea);
}

float Triangle::area(const Vec2D& p0, const Vec2D& p1, const Vec2D& p2){
    return 0.5f * (  (p1.x()*p2.y() - p2.x()*p1.y()) \
                   - (p0.x()*p2.y() - p2.x()*p0.y()) \
                   + (p0.x()*p1.y() - p1.x()*p0.y()));
    
}