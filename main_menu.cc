#include "main_menu.hh"

main_menu main_menu::instance;

main_menu::main_menu()  {}

void main_menu::init()  {}
void main_menu::close() {}

void main_menu::handle_events() {}
void main_menu::update()        {}
void main_menu::render()        {}

main_menu* main_menu::get()
{
    return &instance;
}