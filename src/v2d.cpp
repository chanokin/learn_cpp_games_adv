#include "v2d.hpp"
#include "math_utils.hpp"
#include <cassert>
#include <cmath>

const Vec2D Vec2D::ZERO = Vec2D();
const Vec2D Vec2D::UP = Vec2D(0.0, 1.0f);

// friend methods
ostream& operator<<(ostream out, const Vec2D& v2d){
    return out << "(" << v2d._x << ", " << v2d._y << ")";
}

Vec2D operator*(float m, const Vec2D& v2d){
    return v2d * m;
}

// base methods
float Vec2D::norm2() const{
    return (_x * _x) + (_y * _y);
}
float Vec2D::norm() const{
    return sqrt(norm2());
}

float Vec2D::dot(const Vec2D& v2d) const{
    return (_x * v2d._x) + (_y * v2d._y);  
}

Vec2D& Vec2D::normalize(){
    float n = norm();
    if(fabs(n) > EPSILON){
        (*this) /= n;
    }
    return (*this);
}

Vec2D Vec2D::getUnitVec() const{
    float n = norm();
    if(fabs(n) > EPSILON){
        return (*this) / n;
    }
    return Vec2D::ZERO;
}

float Vec2D::distance(const Vec2D& v2d) const{
    return (v2d - (*this)).norm();
}

Vec2D Vec2D::project(const Vec2D& v2d) const{
    // use floats to reduce memory footprint
    float m2 = v2d.norm2();
    if(m2 > EPSILON){
        float d = dot(v2d);
        return v2d * (d / m2);
    }
    return Vec2D::ZERO;
}

float Vec2D::angle(const Vec2D& v2d) const{
    // use floats to reduce memory footprint

    float m1 = norm();
    float m2 = v2d.norm();
    if(m1 > EPSILON && m2 > EPSILON){
        return acosf(dot(v2d) / (m1 * m2));
    }
    return 0.0;
    
}

Vec2D Vec2D::reflect(const Vec2D& normal) const{
    //v2d <- normal (n) to a "surface"
    //this <- point or vector to reflect on the surface
    //v - 2(v.n)n
    return (*this) - (2 * project(normal));
}

void Vec2D::rotate(const float angle, const Vec2D around_v){
    //rotate this point around around_v
    // alter data version
    //angle is in radians
    float ca = cosf(angle);
    float sa = sinf(angle);
    Vec2D me(_x, _y);
    me -= around_v; //move coordinates to around_v to do rotation
    float xr = me._x * ca - me._y * sa;
    float yr = me._x * sa + me._y * ca;
    _x = xr + around_v._x;
    _y = yr + around_v._y;
}

Vec2D Vec2D::rotateSafe(const float angle, const Vec2D around_v) const{
    //rotate this point around around_v
    // new Vec2D version
    //angle is in radians

    float ca = cosf(angle);
    float sa = sinf(angle);
    Vec2D me(_x, _y);
    me -= around_v; //move coordinates to around_v to do rotation
    float xr = me._x * ca - me._y * sa;
    float yr = me._x * sa + me._y * ca;
    return Vec2D(xr + around_v._x, yr + around_v._y);
}

bool Vec2D::operator==(const Vec2D& v2d) const{
    return eq_float(_x, v2d._x) && eq_float(_y, v2d._y);
}
bool Vec2D::operator!=(const Vec2D& v2d) const{
    return !((*this) == v2d);
}

bool Vec2D::operator<=(const Vec2D& v2d) const{
    return leq_float(norm2(), v2d.norm2());
}

bool Vec2D::operator>=(const Vec2D& v2d) const{
    return geq_float(norm2(), v2d.norm2());
}

bool Vec2D::operator<(const Vec2D& v2d) const{
    return norm2() < v2d.norm2();
}

bool Vec2D::operator>(const Vec2D& v2d) const{
    return norm2() > v2d.norm2();
}

Vec2D Vec2D::operator-() const{
    return Vec2D(-_x, -_y);
}

Vec2D Vec2D::operator*(float m) const{
    return Vec2D(m * _x, m * _y);
}


Vec2D Vec2D::operator/(float m) const{
    assert(fabs(m) > EPSILON);
    float d = 1.0f/m;
    return Vec2D(d * _x, d * _y);
}

Vec2D& Vec2D::operator*=(float m){
    (*this) = (*this) * m;
    return (*this);
}

Vec2D& Vec2D::operator/=(float m){
    (*this) = (*this) / m;
    return (*this);
}


Vec2D Vec2D::operator+(const Vec2D& v2d) const{
    return Vec2D(_x + v2d._x, _y + v2d._y);
}

Vec2D Vec2D::operator-(const Vec2D& v2d) const{
    return (*this) + (-v2d);
}

Vec2D& Vec2D::operator+=(const Vec2D& v2d){
    (*this) = (*this) + v2d;
    return (*this);
}

Vec2D& Vec2D::operator-=(const Vec2D& v2d){
    (*this) = (*this) - v2d;
    return (*this);
}
