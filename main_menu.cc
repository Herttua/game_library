#include "main_menu.hh"
#include "exit_state.hh"
#include "elastic_collision.hh"
#include "program.hh"

main_menu main_menu::instance;

main_menu::main_menu()  {}

void main_menu::init()  
{
    for(unsigned int i = 0; i < 4; i++)
    {
        items.push_back(menu_item(120, 120 + 52 * i, 140, 48, "Item"));
    }
}
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
        {
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
        }break;
        
        default: break;
    }
}
void main_menu::update()        {}
void main_menu::render()        
{
    SDL_SetRenderDrawColor(program::renderer, 0, 0, 0, 255);
    SDL_RenderClear(program::renderer);

    for(unsigned int i = 0; i < items.size(); i++)
    {
        items[i].render();
    }

    program::print_text(5, 5, "Main Menu");

    SDL_RenderPresent(program::renderer);
}

main_menu* main_menu::get()
{
    return &instance;
}

void menu_item::draw_higlight()
{
    SDL_SetRenderDrawColor(program::renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(program::renderer, x, y, x + w, y);
    SDL_RenderDrawLine(program::renderer, x + w, y, x + w, y + h);
}

void menu_item::render()
{
    draw_rect(x, y, w, h, 245, 10, 10, 255);
    draw_higlight();
    program::print_text(x + 5, y + 5, text);
}