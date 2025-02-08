#ifndef GAME_STATE_HH_
#define GAME_STATE_HH_

class game_state
{
public:
    virtual void init()          = 0;
    virtual void close()         = 0;
    virtual void handle_events() = 0;
    virtual void update()        = 0;
    virtual void render()        = 0;
    
    virtual ~game_state()  = default;
};

#endif //GAME_STATE_HH_