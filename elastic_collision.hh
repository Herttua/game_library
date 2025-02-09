#ifndef ELASTIC_COLLISION_HH_
#define ELASTIC_COLLISION_HH_

#include <vector>
#include "game_state.hh"

struct ball
{
    float x, y, vx, vy, radius, mass, frict;
    float d_t = 1.0f / 60.0f;

    ball(float p_x, float p_y, float p_vx, float p_vy, float p_r, float p_m, float p_f) : x(p_x), y(p_y), 
                                                 vx(p_vx), vy(p_vy), 
                                                 radius(p_r), mass(p_m),
                                                 frict(p_f) 
    {}

    void update()
    {
        x += vx * d_t;
        y += vy * d_t;

        vx *= frict;
        vy *= frict;

        //Wall collision
        if(x - radius < 0 || x + radius > 640) vx *= -1;
        if(y - radius < 0 || y + radius > 400) vy *= -1; 
    }
};

class elastic_collision : public game_state
{
public:
    static elastic_collision* get();

    void init();
    void close();

    void handle_events();
    void update();
    void render();

    bool check_collision(const ball& a, const ball& b);
    void resolve_collision(ball& a, ball& b);

private:
    static elastic_collision instance;
    elastic_collision();

    std::vector<ball> balls;

    const float dt = 0.16f;
    const float friction = 0.999f;
};

#endif //ELASTIC_COLLISION_HH_