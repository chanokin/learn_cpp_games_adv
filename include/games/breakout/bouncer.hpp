#ifndef BOUNCER_HPP
#define BOUNCER_HPP
#include "axis_rect.hpp"
#include "v2d.hpp"
#include "border.hpp"

class Bouncer{
    public:
        virtual ~Bouncer(){}
        void init(const AxisRect& rect, bool invertNormals=false);
        inline const AxisRect& getRect() const {return _rect;}

        bool collided(const AxisRect& rect) const;
        const Border& computeBorder(const AxisRect& rect) const;
        Vec2D collisionOffset(const AxisRect& rect) const;

        void move(const Vec2D& dist);
        void moveTo(const Vec2D& point);

        const Border& getBorder(const BorderType& btype);

    private:
        void setupBorders();
        AxisRect _rect;
        Border _borders[NUM_BORDERS];
        bool _invertedNormals;
};
#endif 