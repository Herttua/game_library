#ifndef ELASTIC_COLLISION_HH_
#define ELASTIC_COLLISION_HH_

#include "game_state.hh"

class elastic_collision : public game_state
{
public:
    static elastic_collision* get();

    void init();
    void close();
    void handle_events();
    void update();
    void render();

private:
    static elastic_collision instance;
    elastic_collision();
};

#endif //ELASTIC_COLLISION_HH_