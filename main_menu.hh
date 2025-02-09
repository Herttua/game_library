#ifndef MAIN_MENU_HH_
#define MAIN_MENU_HH_

#include <vector>
#include "game_state.hh"
#include "texture.hh"

struct menu_item
{
    menu_item(int p_x, int p_y, 
              int p_w, int p_h, std::string t) : x(p_x), y(p_y), 
                                                 w(p_w), h(p_h), 
                                                 text(t)
    {}

    void update() {}
    void render() 
    {
        draw_rect(x, y, w, h, 255, 0, 0, 255);
    }

    int x, y, w, h;
    std::string text;
};

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

    std::vector<menu_item> items;
};

#endif //MAIN_MENU_HH_