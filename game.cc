#include "game.hh"
#include "program.hh"
#include "main_menu.hh"
#include "exit_state.hh"

game::game() {}

game game::instance;

void game::init() {}
void game::close() {}
void game::handle_events() 
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
        {    
            switch(program::event.key.keysym.scancode)
            {
                case SDL_SCANCODE_ESCAPE:
                    program::set_next_state(main_menu::get());
                    break;
            }
        }
        break;

        default: break;
    }
}
void game::update() {}
void game::render() 
{
    SDL_SetRenderDrawColor(program::renderer, 0, 0, 0, 255);
    SDL_RenderClear(program::renderer);

    program::print_text(5, 5, "Entity Component System");

    SDL_RenderPresent(program::renderer);
}

game* game::get() 
{
    return &instance;
}