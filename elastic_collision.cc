#include "elastic_collision.hh"
#include "program.hh"
#include "exit_state.hh"

elastic_collision elastic_collision::instance;

elastic_collision::elastic_collision() {}

void elastic_collision::init() {}
void elastic_collision::close() {}
void elastic_collision::handle_events() 
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

            case SDL_SCANCODE_LEFT:
                program::set_next_state(main_menu::get());
                break;

            default: break;
        }
        default: break;
    }
}
void elastic_collision::update() {}
void elastic_collision::render() 
{
    SDL_SetRenderDrawColor(program::renderer, 255, 0, 0, 255);
    SDL_RenderClear(program::renderer);

    SDL_RenderPresent(program::renderer);
}

elastic_collision* elastic_collision::get()
{
    return &instance;
}