#ifndef LINE2D_HPP
#define LINE2D_HPP
#include <iostream>
#include "v2d.hpp"
#include "math_utils.hpp"
#include <math.h>

class Line2D{
    public:
        Line2D():_start(0.0f,0.0f), _end(0.0f,0.0f), _m(0.0f), _b(0.0f), _l(0.0f){}
        Line2D(const float& x0, const float& y0, const float& x1, const float& y1);
        Line2D(const Vec2D& s, const Vec2D& e);
        // void to_pixels();

        inline const Vec2D& start()const {return _start;}
        inline const Vec2D& end()const {return _end;}
        inline void setStart(const Vec2D& s){_start = s;}
        inline void setStart(const float& x, const float& y){
            _start.setX(x); _start.setY(y);
        }
        inline void setEnd(const Vec2D& e){_end = e;}
        inline void setEnd(const float& x, const float& y){
            _end.setX(x); _end.setY(y);
        }

        bool operator==(const Line2D& rhs) const;

        // friend ostream& operator<<(ostream& out, const Line2D& line){
        //         return out << line._start << "->" << line._end;
        // }

        float minDistance(const Vec2D& p, bool limitToSegment=false) const;
        Vec2D closestPoint(const Vec2D& p, bool limitToSegment=false) const;
        float slope() const;
        float length() const;
        Vec2D middle() const;

    private:
        Vec2D _start, _end;
        float _m, _b, _l;

        inline void _compute_mb(){
            float dx = _end.x() - _start.x();
            if (eq_float(fabs(dx), 0.0f)){
                _b = _start.y();
                _m = INF;
                _l = _end.distance(_start);

                return;
            }

            float dy = _end.y() - _start.y();
            if (eq_float(dy, 0.0f)){
                _b = _start.y();
                _m = 0.0;
            } else {
                _m = dy / dx;
                _b = _start.y() - _m * _start.x();
            }
            _l = _end.distance(_start);
        }

        
};

#endif