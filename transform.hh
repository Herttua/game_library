#ifndef TRANSFORM_HH_
#define TRANSFORM_HH_

#include "component_system.hh"
#include "vector2.hh"

class transform : public component
{
public:
    vector2 pos;
    vector2 vel;
    
    float radius;
    float mass;
    int scale = 1;

    transform() 
    {
        pos.zero();
    }
    transform(int sc)
    {
        pos.zero();
        scale = sc;
    }
    transform(float x, float y, float r, float m, int sc) 
    {
        pos.x  = x;
        pos.y  = y;
        radius = r;
        mass   = m;
        scale  = sc;
    }

    ~transform() {}

    void init() override
    {
        vel.x = 0.0f;
        vel.y = 0.0f;
    }

    int x() { return pos.x; }
    int y() { return pos.y; }

    void update(float dt) override
    {
        pos.x += vel.x * dt;
        pos.y += vel.y * dt;
    }

    void set_pos(float x, float y)
    {
        pos.x = x;
        pos.y = y;
    }    
};

#endif //TRANSFORM_HH_