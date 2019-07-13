#ifndef SHAPE_CIRCLE_HPP
#define SHAPE_CIRCLE_HPP
#include "shape.hpp"
#include "v2d.hpp"

class Circle: public Shape{
    public:
        Circle();
        Circle(const Vec2D& center, const float& radius);
        inline virtual Vec2D center() const override {return _points[0];}
        inline float radius() const {return _radius;}
        inline void setRadius(const float& r) {_radius = r;}
        inline void moveTo(const Vec2D pos){_points[0] = pos;}

        bool intersects(const Circle& c) const;
        bool contains(const Vec2D& p) const;
    private:
        float _radius;
};

#endif