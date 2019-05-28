#include "graphics/line2d.hpp"
// #include "v2d.hpp"
#include <iostream>


Line2D::Line2D(const float& x0, const float& y0, const float& x1, const float& y1){
    _start = Vec2D(x0, y0);
    _end = Vec2D(x1, y1);
    _compute_mb();
}

Line2D::Line2D(const Vec2D& s, const Vec2D& e){
    _start = s;
    _end = e;
    _compute_mb();
}

bool Line2D::operator==(const Line2D& rhs) const{
    return (rhs._start == _start && rhs._end == _end);
}


float Line2D::minDistance(const Vec2D& p, bool limitToSegment) const{
    return p.distance(closestPoint(p, limitToSegment));
}
Vec2D Line2D::closestPoint(const Vec2D& p, bool limitToSegment) const{
    Vec2D v = _end - _start; //line segment (translated to 0,0)
    Vec2D u = p - _start; //from start to p (translated to 0,0)
    float m2 = v.norm2();
    if(m2 > EPSILON){
        float d = u.dot(v)/m2; // project u on line segment v
        if(limitToSegment && d > 1.0f){
            return _end;
        }
        return _start + v*d;
    }
    return _start;
    
}
float Line2D::slope() const{
    float dx = _end.x() - _start.x();
    if (eq_float(fabs(dx), 0.0f)){
        return INF;
    }

    float dy = _end.y() - _start.y();
    if (eq_float(dy, 0.0f)){
        return 0.0f;
    }
    
    return dy / dx;
}
float Line2D::length() const{
    return _end.distance(_start);
}

Vec2D Line2D::middle() const{
    float half_x = (_start.x() + _end.x()) / 2.0f;
    float half_y = (_start.y() + _end.y()) / 2.0f;
    return Vec2D(half_x, half_y);

}
