#ifndef GAME_HH_
#define GAME_HH_

#include "game_state.hh"

class game : public game_state
{
public:
    static game* get();

    void init();
    void close();

    void handle_events();
    void update();
    void render();

private:
    static game instance;
    game();
};

#endif //GAME_HH_