#include "bouncer.hpp"
#include <cmath>
#include <cassert>
#include "math_utils.hpp"
#include <iostream>
void Bouncer::init(const AxisRect& rect, bool invertNormals){
    _rect = rect;
    _invertedNormals = invertNormals;
    setupBorders();
}

bool Bouncer::collided(const AxisRect& rect) const{
    if(rect.intersects(_rect)){
        return true;
    }
    return false;
}

const Border& Bouncer::computeBorder(const AxisRect& rect) const{
    float dx, dy;
    return computeBorder(rect, dx, dy);
}

const Border& Bouncer::computeBorder(
                    const AxisRect& rect, float& _dx, float& _dy) const{
    // identify on which border did rect collide with _rect (this)
    float minY = 0.0f, maxY = 0.0f;
    float minX = 0.0f, maxX = 0.0f;
    minY = (rect.topLeft().y() <= _rect.topLeft().y()) ? 
            rect.topLeft().y() : _rect.topLeft().y();

    maxY = (rect.bottomRight().y() >= _rect.bottomRight().y()) ? 
            rect.bottomRight().y() : _rect.bottomRight().y();

    minX = (rect.topLeft().x() <= _rect.topLeft().x()) ? 
            rect.topLeft().x() : _rect.topLeft().x();

    maxX = (rect.bottomRight().x() >= _rect.bottomRight().x()) ? 
            rect.bottomRight().x() : _rect.bottomRight().x();
    
    _dy = maxY - minY;
    _dx = maxX - minX;

    // if dx is bigger than dy, it is likelier to have hit on the top
    // or bottom (a larger region to collide)
    if(_dx > _dy){
        // y coords go from 0 (top) to height (bottom)
        if(rect.center().y() > _rect.center().y()){
            return _borders[BOTTOM];
        } else {
            return _borders[TOP];
        }
    } else {
        // x coords go from 0 (left) to width (right)
        if(rect.center().x() < _rect.center().x()){
            return _borders[LEFT];
        } else {
            return _borders[RIGHT];
        }

    }

}

Vec2D Bouncer::collisionOffset(const AxisRect& rect) const{
    if(collided(rect)){
        float dx, dy;
        Border border = computeBorder(rect, dx, dy);
        // if the normal to the border has a Y=0 component, then the collision 
        // ocurred horizontally (i.e. on the left or right border)
        if( eq_float(border.normal.y(), 0.0f) ){
            return (dx + 1) *  border.normal;
        } else {
            return (dy + 1) *  border.normal;
        }
    }
    return Vec2D::ZERO;
}

void Bouncer::move(const Vec2D& dist){
    _rect.move(dist);
    setupBorders();

}
void Bouncer::moveTo(const Vec2D& point){
    _rect.moveTo(point);
    setupBorders();
}

const Border& Bouncer::getBorder(const BorderType& btype){
    assert(btype < NUM_BORDERS);
    return _borders[btype];
}
    
void Bouncer::setupBorders(){
    _borders[TOP].border = {_rect.topLeft().x(), _rect.topLeft().y(), 
                            _rect.bottomRight().x(), _rect.topLeft().y()};
    
    _borders[BOTTOM].border = {_rect.topLeft().x(), _rect.bottomRight().y(), 
                               _rect.bottomRight().x(), _rect.bottomRight().y()};

    _borders[LEFT].border = {_rect.topLeft().x(), _rect.topLeft().y(), 
                             _rect.topLeft().x(), _rect.bottomRight().y()};

    _borders[RIGHT].border = {_rect.bottomRight().x(), _rect.topLeft().y(), 
                              _rect.bottomRight().x(), _rect.bottomRight().y()};
    
    if(_invertedNormals){
        _borders[TOP].normal = DOWN_DIR;
        _borders[BOTTOM].normal = UP_DIR;
        _borders[LEFT].normal = RIGHT_DIR;
        _borders[RIGHT].normal = LEFT_DIR;

    } else {
        _borders[TOP].normal = UP_DIR;
        _borders[BOTTOM].normal = DOWN_DIR;
        _borders[LEFT].normal = LEFT_DIR;
        _borders[RIGHT].normal = RIGHT_DIR;
    }
}
