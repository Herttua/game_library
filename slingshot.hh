#ifndef SLINGSHOT_HH_
#define SLINGSHOT_HH_

#include "game_state.hh"

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
};

#endif //SLINGSHOT_HH_