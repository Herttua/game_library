#include "exit_state.hh"

exit_state exit_state::instance;

exit_state::exit_state()         {}

void exit_state::init()          {}
void exit_state::update()        {}
void exit_state::handle_events() {}
void exit_state::render()        {}
void exit_state::close()         {}

exit_state* exit_state::get()
{
    return &instance;
}