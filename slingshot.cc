#include "slingshot.hh"

slingshot slingshot::instance;

slingshot::slingshot() {}

void slingshot::init() {}
void slingshot::close() {}

void slingshot::handle_events() {}
void slingshot::update() {}
void slingshot::render() {}

slingshot* slingshot::get() 
{ 
    return &instance; 
}