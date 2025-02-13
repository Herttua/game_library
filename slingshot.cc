#include "slingshot.hh"
#include "program.hh"
#include "exit_state.hh"
#include "main_menu.hh"

slingshot slingshot::instance;

slingshot::slingshot() : puck1(320, 200, 0, 0, 16, 1) 
{}

void slingshot::init() 
{
    aiming = false;
    mouse_x = 0;
    mouse_y = 0;
}

void slingshot::close() {}

void slingshot::handle_events() 
{
    SDL_PollEvent(&program::event);
    switch(program::event.type)
    {
        case SDL_QUIT:
            std::cout << "Exit program.\n";
            program::set_next_state(exit_state::get());
            program::running = false;
            break;

        case SDL_KEYDOWN:
            switch(program::event.key.keysym.scancode)
            {
                case SDL_SCANCODE_ESCAPE:
                    program::set_next_state(main_menu::get());
                    break;

                default: break;
            }
            break;

        case SDL_MOUSEBUTTONDOWN:
            {
                SDL_GetMouseState(&mouse_x, &mouse_y);
                float d_x = mouse_x - puck1.pos.x;
                float d_y = mouse_y - puck1.pos.y;
                if(d_x * d_x + d_y * d_y < puck1.radius * puck1.radius)
                {
                    puck1.dragging = true;
                    puck1.start_x = mouse_x;
                    puck1.start_y = mouse_y;
                    aiming = true;
                }
            }
            break;

        case SDL_MOUSEMOTION:
            if(puck1.dragging)
            {
                SDL_GetMouseState(&mouse_x, &mouse_y);
            }
            break;

        case SDL_MOUSEBUTTONUP:
            if(puck1.dragging)
            {
                SDL_GetMouseState(&mouse_x, &mouse_y);
                puck1.vel.x = (puck1.start_x - mouse_x) * 3.0f;
                puck1.vel.y = (puck1.start_y - mouse_y) * 3.0f;
                puck1.dragging = false;
                aiming = false;
            }
            break;

        default: break;
    }
}
void slingshot::update() 
{
    puck1.update(0.1f);
}
void slingshot::render() 
{
    SDL_SetRenderDrawColor(program::renderer, 0, 0, 0, 255);
    SDL_RenderClear(program::renderer);

    //Draw puck
    SDL_SetRenderDrawColor(program::renderer, 255, 0, 0, 255);
    for(int w = 0; w < puck1.radius * 2; w++)
    {
        for(int h = 0; h < puck1.radius * 2; h++)
        {
            int dx = puck1.radius - w; // Distance from center
            int dy = puck1.radius - h;
            if((dx * dx + dy * dy) <= (puck1.radius * puck1.radius))
            {
                SDL_RenderDrawPointF(program::renderer, 
                                     puck1.pos.x + dx, 
                                     puck1.pos.y + dy);
            }    
        }
    }

    //Draw aiming line
    if(aiming)
    {
        SDL_SetRenderDrawColor(program::renderer, 0, 255, 0, 255);
        SDL_RenderDrawLine(program::renderer, puck1.pos.x, puck1.pos.y, 
                                              mouse_x,     mouse_y);
    }

    program::print_text(5, 5, "Click the ball and drag with mouse to aim.");

    SDL_RenderPresent(program::renderer);
}

slingshot* slingshot::get() 
{ 
    return &instance; 
}