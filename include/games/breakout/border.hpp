#ifndef BORDER_HPP
#define BORDER_HPP
#include "v2d.hpp"
#include "line2d.hpp"

enum BorderType{
    BOTTOM = 0,
    LEFT,
    TOP,
    RIGHT,
    NUM_BORDERS
};

static const Vec2D UP_DIR = Vec2D(0, -1);
static const Vec2D DOWN_DIR = Vec2D(0, 1);
static const Vec2D LEFT_DIR = Vec2D(-1, 0);
static const Vec2D RIGHT_DIR = Vec2D(1, 0);

struct Border{
    Vec2D normal;
    Line2D border;
};

#endif