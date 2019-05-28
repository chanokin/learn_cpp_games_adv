#include "star2d.hpp"
#include <math.h>


Star2D::Star2D(const Vec2D& center, float width){
    int num_points = 5; // change this as an option!
    float a = M_PI / (float)num_points;
    float outWidth = width * ((3.0f + sqrtf(5.0f)) / 2.0f);
    _n_lines = num_points * 2;
    // _lines = (Line2D *)malloc(sizeof(Line2D) * _n_lines);
    _lines = new Line2D[_n_lines];
    if(_lines == nullptr){
        _n_lines = 0;
        return;
    }
    float ang = -M_PI_2;
    float tmp;
    float x0, y0, x1, y1;
    float xc = center.x(), yc = center.y();
    for(int i = 0; i < num_points; i++){
        x0 = xc + outWidth * cosf(ang);
        y0 = yc + outWidth * sinf(ang);
        tmp = ang + a;
        // if(tmp > 2.0*M_PI){
        //     tmp -= 2.0*M_PI;
        // }
        x1 = xc + width * cosf(tmp);
        y1 = yc + width * sinf(tmp);
        _lines[2*i] = Line2D(x0, y0, x1, y1);

        tmp = ang - a;
        // if(tmp < 0.0f){
        //     tmp += 2.0*M_PI;
        // }
        x1 = xc + width * cosf(tmp);
        y1 = yc + width * sinf(tmp);
        _lines[2*i + 1] = Line2D(x1, y1, x0, y0);

        ang += (2.0f * a);
    }
}

void Star2D::rotateAround(const float& angle, const Vec2D& p){
    for(int i = 0; i < _n_lines; i++){
        _lines[i].rotateAround(angle, p);
    }
}