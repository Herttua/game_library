#include "game.hh"
#include "program.hh"
#include "main_menu.hh"
#include "exit_state.hh"
#include "component_system.hh"
#include "transform.hh"

game game::instance;
master _master;
//auto& player(_master.add_entity()); 

game::game() 
{
    //player.add_component<transform>(280.f, 150.f, 15.f, 3.f, 1);
}

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

    SDL_SetRenderDrawColor(program::renderer, 255, 0, 0, 255);
    /*for(int w = 0; w < player.get_component<transform>().radius * 2; w++)
    {
        for(int h = 0; h < player.get_component<transform>().radius * 2; h++)
        {
            int dx = player.get_component<transform>().radius - w; // Distance from center
            int dy = player.get_component<transform>().radius - h;
            if((dx * dx + dy * dy) <= (player.get_component<transform>().radius * player.get_component<transform>().radius))
            {
                SDL_RenderDrawPointF(program::renderer, 
                    player.get_component<transform>().pos.x + dx, 
                    player.get_component<transform>().pos.y + dy);
            }    
        }
    }*/

    program::print_text(5, 5, "Entity Component System");

    SDL_RenderPresent(program::renderer);
}

game* game::get() 
{
    return &instance;
}