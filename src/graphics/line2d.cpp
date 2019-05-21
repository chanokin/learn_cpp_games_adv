#include "line2d.hpp"

friend ostream& operator<<(ostream& out, const Line2D& line){
    return out << line.start() << "->" << line.end();
}

Line2D::Line2D();
Line2D::Line2D(const float x0, const float y0, const float x1, const float y1);
Line2D::Line2D(const Vec2D& s, const Vec2D& e);
