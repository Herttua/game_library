#ifndef MAIN_MENU_HH_
#define MAIN_MENU_HH_

#include "game_state.hh"

class main_menu : public game_state
{
public:
    static main_menu* get(); 
    
    void init();
    void close();
    void handle_events();
    void update();
    void render();

private: 
    static main_menu instance;
    main_menu();
};

#endif //MAIN_MENU_HH_