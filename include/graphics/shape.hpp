#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "v2d.hpp"
#include <vector>

using namespace std;
class Shape{
    public:
        virtual Vec2D getCenter() const = 0;
        inline virtual vector<Vec2D> getPoints() const {return _points;}
        void move(const Vec2D& step);
    protected:
        vector<Vec2D> _points;
}

#endif