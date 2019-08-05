#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "v2d.hpp"
#include <vector>

using namespace std;
class Shape{
    public:
        virtual Vec2D center() const = 0;
        inline virtual vector<Vec2D> points() const {return _points;}
        void move(const Vec2D& step);
        virtual void moveTo(const Vec2D& dest) = 0;
    protected:
        vector<Vec2D> _points;
};

#endif