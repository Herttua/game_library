#include "main_menu.hh"
#include "exit_state.hh"
#include "elastic_collision.hh"
#include "program.hh"

main_menu main_menu::instance;

int active_item = 0;

main_menu::main_menu()  {}

void main_menu::init()  
{
    items.push_back(menu_item(120, 120, 140, 48, "Elastic Collision", 1));
    items.push_back(menu_item(120, 120 + 52, 140, 48, "Slingshot", 0));
    items.push_back(menu_item(120, 120 + (52 * 2), 140, 48, "Exit", 0));
}
void main_menu::close() 
{
    items.clear();
}

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

                case SDL_SCANCODE_DOWN:
                    active_item++;
                    if(active_item > items.size() - 1)
                        active_item = items.size() - 1;
                    break;

                case SDL_SCANCODE_UP:
                    active_item--;
                    if(active_item < 0)
                        active_item = 0;
                    break;

                case SDL_SCANCODE_RETURN:
                    switch(active_item)
                    {
                        case 0:
                            program::set_next_state(elastic_collision::get());
                            break;

                        case 1:
                            //program::set_next_state(slingshot::get());
                            break;
                        case 2:
                            program::set_next_state(exit_state::get());
                            program::running = false;
                            break;

                        default: break;
                    }
                    break;

                default: break;
            }
        }break;
        
        default: break;
    }
}
void main_menu::update()        
{
    for(unsigned int i = 0; i < items.size(); i++)
    {
        if(i != active_item)
            items[i].active = 0;
        else
            items[i].active = 1;
    }
}
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
    SDL_RenderDrawLine(program::renderer, x + w, y + h, x, y + h);
    SDL_RenderDrawLine(program::renderer, x, y + h, x, y);
}

void menu_item::render()
{
    draw_rect(x, y, w, h, 245, 10, 10, 255);
    
    if(active == 1)
        draw_higlight();
    
        program::print_text(x + 5, y + 5, text);
}