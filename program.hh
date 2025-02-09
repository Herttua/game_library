#ifndef PROGRAM_HH_
#define PROGRAM_HH_

#include <iostream>
#include <SDL2/SDL.h>

#include "game_state.hh"
#include "exit_state.hh"
#include "main_menu.hh"
#include "bitmapfont.hh"

class program
{
public:
    program();

    static SDL_Window*   window;
    static SDL_Renderer* renderer;
    static SDL_Event     event;
    static bool          running;

    void init(const char* title, 
              int x, int y, 
              int w, int h,
              bool fullscreen);

    void run();
    void clean();

    void handle_events();
    void update();
    void render();

    static game_state* current_state;
    static game_state* next_state;
    static bitmapfont l_font;

    static void set_next_state(game_state* state);
    static void change_state();
    static void print_text(int x, int y, std::string txt);

private:
    
    const int FPS = 60;
    const int frame_delay = 1000 / FPS;

    int       frame_time;
    Uint32    last_time;
};

#endif //PROGRAM_HH_