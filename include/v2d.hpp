#ifndef V2D_HPP
#define V2D_HPP

#include <iostream>
#include <algorithm>
using namespace std;

class Vec2D{
    public:
    Vec2D(void):_x(0.0f), _y(0.0f){}
    Vec2D(const float& x, const float& y):_x(x), _y(y){}
    inline float x() const{return _x;}
    inline float y() const{return _y;}
    inline void setX(float x){_x = x;}
    inline void setY(float y){_y = y;}

    static const Vec2D ZERO;
    static const Vec2D UP;

    friend ostream& operator<<(ostream out, const Vec2D& v2d);

    float norm2() const;
    float norm() const;
    float dot(const Vec2D& v2d) const;
    Vec2D& normalize();
    Vec2D getUnitVec() const;
    float distance(const Vec2D& v2d) const;
    Vec2D project(const Vec2D& v2d) const;
    float angle(const Vec2D& v2d) const;
    Vec2D reflect(const Vec2D& normal) const;
    void rotate(const float angle, const Vec2D around_v);
    Vec2D rotateSafe(const float angle, const Vec2D around_v) const;

    bool operator==(const Vec2D& v2d) const;
    bool operator!=(const Vec2D& v2d) const;
    bool operator<=(const Vec2D& v2d) const;
    bool operator>=(const Vec2D& v2d) const;
    bool operator<(const Vec2D& v2d) const;
    bool operator>(const Vec2D& v2d) const;
    
    Vec2D operator-() const;
    
    Vec2D operator*(float m) const;
    Vec2D operator/(float m) const;
    Vec2D& operator*=(float m);
    Vec2D& operator/=(float m);

    friend Vec2D operator*(float m, const Vec2D& v2d);

    Vec2D operator+(const Vec2D& v2d) const;
    Vec2D operator-(const Vec2D& v2d) const;
    Vec2D& operator+=(const Vec2D& v2d);
    Vec2D& operator-=(const Vec2D& v2d);

    

    private:
    float _x, _y;
};


#endif
