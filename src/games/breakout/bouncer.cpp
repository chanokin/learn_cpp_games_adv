#include "bouncer.hpp"
#include <cmath>
#include <cassert>

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
    
    float dy = maxY - minY;
    float dx = maxX - minX;

    if(dx > dy){
        // y coords go from 0 (top) to height (bottom)
        if(rect.center().y() < _rect.center().y()){
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
        Border border = computeBorder(rect);
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
