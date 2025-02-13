#ifndef SLINGSHOT_HH_
#define SLINGSHOT_HH_

#include "game_state.hh"
#include "vector2.hh"

struct puck
{
    puck(float x, float y, 
         float vx, float vy, 
         float r, float m)   : pos(x, y), vel(vx, vy),
                               radius(r), mass(m) 
    {}

    void update(float dt)
    {
        if(!dragging)
        {
            pos.x += vel.x * dt;
            pos.y += vel.y * dt;

            vel.x *= friction;
            vel.y *= friction;

            if(pos.x - radius < 0 || pos.x + radius > 640) vel.x *= -1;
            if(pos.y - radius < 0 || pos.y + radius > 400) vel.y *= -1;
        }
    }

    const float friction = 0.99f;

    vector2 pos;
    vector2 vel;

    float radius;
    float mass;

    int start_x;
    int start_y;
    bool dragging;
};

class slingshot : public game_state
{
public:
    static slingshot* get();
    void init();
    void close();

    void handle_events();
    void update();
    void render();

private:
    static slingshot instance;
    slingshot();

    bool aiming;
    int mouse_x, mouse_y;
    puck puck1;
};

#endif //SLINGSHOT_HH_