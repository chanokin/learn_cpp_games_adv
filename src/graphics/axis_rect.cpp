#include "axis_rect.hpp"
#define TL 0
#define BR 1

AxisRect::AxisRect(): AxisRect(Vec2D::ZERO, Vec2D::ZERO){
}

AxisRect::AxisRect(const Vec2D& topLeft, const float& width, const float& height){
    _points.reserve(2);
    _points[TL] = topLeft;
    _points[BR] = Vec2D(topLeft.x() + width - 1, topLeft.y() + height - 1);
}

AxisRect::AxisRect(const Vec2D& topLeft, const Vec2D& bottomRight){
    _points.reserve(2);
    _points[TL] = topLeft;
    _points[BR] = bottomRight;
}

float AxisRect::width()const{
    return _points[BR].x() - _points[TL].x() + 1;
}

float AxisRect::height()const{
    return _points[BR].y() - _points[TL].y() + 1;
}


void AxisRect::moveTo(const Vec2D& position){
    float w = width();
    float h = height();
    _points[TL] = position;
    _points[BR] = Vec2D(position.x() + w - 1, position.y() + h - 1);
}

Vec2D AxisRect::center() const{
    return Vec2D((_points[TL].x()+_points[BR].x())/2.0f,
                 (_points[TL].y()+_points[BR].y())/2.0f);
}

bool AxisRect::intersects(const AxisRect& rhs){
    bool left = rhs.bottomRight().x() < topLeft().x();
    bool right = rhs.topLeft().x() > bottomRight().x();
    bool up = rhs.bottomRight().y() < topLeft().y();
    bool down = rhs.topLeft().y() > bottomRight().y(); 
    return !(left || right || up || down);
}

bool AxisRect::contains(const Vec2D& p){
    bool inRangeX = _points[TL].x() <= p.x() && p.x() <= _points[BR].x();
    bool inRangeY = _points[TL].y() <= p.y() && p.y() <= _points[BR].y();
    return inRangeX && inRangeY;
}

AxisRect AxisRect::inset(const AxisRect rect, Vec2D& insets){
    return AxisRect(rect.topLeft() + insets, 
                    rect.width() - (2.0f * insets.x()),
                    rect.height() - (2.0f * insets.y()) );
}

vector<Vec2D> AxisRect::points() const{
    vector<Vec2D> p;
    p.push_back(_points[TL]);
    p.push_back(Vec2D(_points[BR].x(), _points[TL].y()));
    p.push_back(_points[BR]);
    p.push_back(Vec2D(_points[TL].x(), _points[BR].y()));

    return p;
}