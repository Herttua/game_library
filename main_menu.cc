#include "main_menu.hh"
#include "exit_state.hh"
#include "elastic_collision.hh"
#include "program.hh"

main_menu main_menu::instance;

main_menu::main_menu()  {}

void main_menu::init()  {}
void main_menu::close() {}

void main_menu::handle_events() 
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
                program::set_next_state(exit_state::get());
                program::running = false;
                break;

            case SDL_SCANCODE_RIGHT:
                program::set_next_state(elastic_collision::get());
                break;

            default: break;
        }
        default: break;
    }
}
void main_menu::update()        {}
void main_menu::render()        
{
    SDL_SetRenderDrawColor(program::renderer, 0, 0, 0, 255);
    SDL_RenderClear(program::renderer);

    SDL_RenderPresent(program::renderer);
}

main_menu* main_menu::get()
{
    return &instance;
}