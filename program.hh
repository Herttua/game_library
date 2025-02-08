#ifndef PROGRAM_HH_
#define PROGRAM_HH_

#include <iostream>
#include <SDL2/SDL.h>

class program
{
public:
    program();

    void init(const char* title, 
              int x, int y, 
              int w, int h,
              bool fullscreen);

    void run();
    void clean();

    static SDL_Window* window;
    static SDL_Renderer* renderer;
    static SDL_Event event;
    static bool running;
    
private:
    const int FPS = 60;
    const int frame_delay = 1000 / FPS;

    int       frame_time;
    Uint32    last_time;
};

#endif //PROGRAM_HH_