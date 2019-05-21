#ifndef LINE2D_HPP
#define LINE2D_HPP
#include <iostream>
#include "v2d.hpp"
#include "math_utils.hpp"

class Line2D{
    public:
        Line2D();
        Line2D(const float x0, const float y0, const float x1, const float y1);
        Line2D(const Vec2D& s, const Vec2D& e);
        // void to_pixels();

        inline const Vec2D& start()const {return _start;}
        inline const Vec2D& end()const {return _end;}
        inline void setStart(const Vec2D& s){_start = s;}
        inline void setEnd(const Vec2D& e){_end = e;}

        bool operator==(const Line2D& rhs) const;

        friend ostream& operator<<(ostream& out, const Line2D& line);

    private:
        Vec2D _start, _end;
        float _m, _b, _l;

        inline void _compute_mb(){
            float dy = _end.y() - _start.y();
            float dx = _end.x() - _start.x();

            if (eq_float(dy, 0.0f)){
                _b = 0.0;
                _m = INF;
            } else {
                _m = dy / dx;
                _b = _start.y() - _s * _start.x();
            }

            _l = _end.distance(_start);
        }

        
};

#endif