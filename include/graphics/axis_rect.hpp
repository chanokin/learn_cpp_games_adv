#ifndef SHAPE_AXIS_RECT_HPP
#define SHAPE_AXIS_RECT_HPP
#include "shape.hpp"
#include "v2d.hpp"

using namespace std;

//Axis-aligned rectangle
class AxisRect : public Shape{
    public:
        AxisRect();
        AxisRect(const Vec2D& topLeft, const float& width, const float& height);
        AxisRect(const Vec2D& topLeft, const Vec2D& bottomRight);

        inline void setTopLeft(const Vec2D& tl){_points[0] = tl;}
        inline void setBottomRight(const Vec2D& br){_points[1] = br;}
        inline Vec2D topLeft()const {return _points[0];}
        inline Vec2D bottomRight()const {return _points[1];}
        float width()const;
        float height()const;
        void moveTo(const Vec2D& position);
        virtual Vec2D center() const override;
        bool intersects(const AxisRect& rhs);
        bool contains(const Vec2D& p);
        static AxisRect inset(const AxisRect rect, Vec2D& insets);
        virtual vector<Vec2D> points() const override;
};

#endif