#ifndef EXIT_STATE_HH_
#define EXIT_STATE_HH_

#include "game_state.hh"

class exit_state : public game_state
{
public:
    static exit_state* get();

    void init();
    void close();
    void handle_events();
    void update();
    void render();

private:
    static exit_state instance;
    exit_state();
};

#endif //EXIT_STATE_HH_