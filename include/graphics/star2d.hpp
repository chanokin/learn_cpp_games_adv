#ifndef STAR2D_HPP
#define STAR2D_HPP
#include <iostream>
#include "v2d.hpp"
#include "graphics/line2d.hpp"

class Star2D{
    public:
        Star2D():_n_lines(0), _center(0.0f, 0.0f), _lines(nullptr){}
        Star2D(const Vec2D& center, float width=5.0f);
        void rotateAround(const float& angle, const Vec2D& p);
        inline const int numLines() const{return _n_lines;}
        inline const Line2D& line(const int index) const{
            if(_lines != nullptr){
                return _lines[index];
            }
            return Line2D();
        }
    private:
        int _n_lines;
        Vec2D _center;
        Line2D* _lines;
};

#endif /* !STAR2D_HPP */
