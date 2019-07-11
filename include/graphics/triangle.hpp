#ifndef SHAPE_TRIANGLE_HPP
#define SHAPE_TRIANGLE_HPP

#include "shape.hpp"

class Triangle : public Shape{
    public:
        Triangle();
        Triangle(const Vec2D& p0, const Vec2D& p1, const Vec2D& p2);
        inline void setP0(const Vec2D& p){_points[0] = p;}
        inline void setP1(const Vec2D& p){_points[1] = p;}
        inline void setP2(const Vec2D& p){_points[2] = p;}
        inline Vec2D p0() const {return _points[0];}
        inline Vec2D p1() const {return _points[1];}
        inline Vec2D p2() const {return _points[2];}

        virtual Vec2D getCenter() const override;
        float area() const;
        bool contains(const Vec2D& p) const;
    private:
        float area(const Vec2D& p0, const Vec2D& p1, const Vec2D& p2);
}

#endif