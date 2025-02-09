#include "program.hh"

program* g = nullptr;

int main(int argc, char* argv[])
{
    g = new program();
    g->init("Games Library", SDL_WINDOWPOS_CENTERED, 
                             SDL_WINDOWPOS_CENTERED, 
                             640, 400, false);

    try
    {
        g->run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
    catch(...)
    {
        std::cerr << "Unknown exception: " << std::endl;
        return 2;
    }
    
    g->clean();
    delete g;
    return 0;
}