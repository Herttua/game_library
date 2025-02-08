#include "program.hh"

#define SDL_HINT_RENDER_VSYNC "SDL_RENDER_VSYNC"

SDL_Renderer* program::renderer = nullptr;
SDL_Window*   program::window   = nullptr;
SDL_Event     program::event;
bool          program::running = true;

program::program() {}

void program::init(const char* title, 
    int x, int y, 
    int w, int h,
    bool fullscreen) 
{
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "SDL initialized\n";

        int flags = 0;
        if(fullscreen)
        {
        flags = SDL_WINDOW_FULLSCREEN;
        }
        window = SDL_CreateWindow(title, x, y, w, h, flags);
        renderer = SDL_CreateRenderer(window, -1, 
                                SDL_RENDERER_ACCELERATED | 
                                SDL_RENDERER_PRESENTVSYNC | 
                                SDL_RENDERER_TARGETTEXTURE);
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
        SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");
        SDL_SetRenderDrawColor(renderer, 250, 250, 250, 255);
        std::cout << "Renderer created\n";
    }

    last_time = SDL_GetTicks();

    std::cout << "SDL initialized\n";
}

void program::run()
{
    while(running)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                running = false;
            }

            if(event.type == SDL_KEYDOWN)
            {
                if(event.key.keysym.sym == SDLK_ESCAPE)
                {
                    running = false;
                }
            }
        }
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }
}

void program::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    SDL_Quit();
    std::cout << "All cleaned up\n";
}