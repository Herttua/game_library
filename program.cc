#include "program.hh"

#define SDL_HINT_RENDER_VSYNC "SDL_RENDER_VSYNC"

SDL_Renderer* program::renderer     = nullptr;
SDL_Window*   program::window       = nullptr;
SDL_Event     program::event;
bool          program::running      = true;

game_state* program::current_state  = nullptr;
game_state* program::next_state     = nullptr;

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

    current_state = main_menu::get();
    current_state->init();

    std::cout << "SDL initialized\n";
}

void program::run()
{
    while(running)
    {
        Uint32 frame_start = SDL_GetTicks();

        /*This calculated delta time fucks up the rendering*/
        /*so we are using fixed delta time of 0.1f for now*/
        
        //Uint32 delta_ms    = frame_start - last_time;    
        //float delta_time   = delta_ms / 1000.0f;
        //last_time          = frame_start;

        handle_events();
        update();
        change_state();
        render();

        frame_time = SDL_GetTicks() - frame_start;
        while(frame_delay > frame_time)
        {
            frame_time = SDL_GetTicks() - frame_start;
        }
    }
}

void program::handle_events()
{
    current_state->handle_events();
}

void program::update()
{
    current_state->update();
}

void program::render()
{
    current_state->render();
}

void program::set_next_state(game_state* state) 
{
    if(next_state != exit_state::get())
    {
        next_state = state;
    }
}

void program::change_state()
{
    if(next_state != nullptr)
    {
        current_state->close();
        next_state->init();

        current_state = next_state;
        next_state = nullptr;
    }
}

void program::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    SDL_Quit();
    std::cout << "All cleaned up\n";
}