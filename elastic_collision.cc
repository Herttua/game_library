#include "elastic_collision.hh"
#include "program.hh"
#include "exit_state.hh"

elastic_collision elastic_collision::instance;

elastic_collision::elastic_collision() {}

void elastic_collision::init() 
{
    for (int i = 0; i < 20; i++) 
    {
        float radius = 10 + std::rand() % 15;
        float x = radius + std::rand() % (640 - 2 * (int)radius);
        float y = radius + std::rand() % (400 - 2 * (int)radius);
        float vx = (std::rand() % 800 - 300) * 1.5f; 
        float vy = (std::rand() % 800 - 300) * 1.5f;
        balls.emplace_back(x, y, vx, vy, radius, 1, friction);
    }
}
void elastic_collision::close() 
{
    balls.clear();
}
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
                    program::set_next_state(main_menu::get());
                    break;

                default: break;
            }
            break;

        default: break;
    }
}
void elastic_collision::update() 
{
    for(auto& b : balls)
    { 
        b.update();
    }   
    for(size_t i = 0; i < balls.size(); ++i)
    {
        for(size_t j = i + 1; j < balls.size(); ++j)
        {
            if(check_collision(balls[i], balls[j])) resolve_collision(balls[i], balls[j]);
        }
    }
}
void elastic_collision::render() 
{
    SDL_SetRenderDrawColor(program::renderer, 0, 0, 0, 255);
    SDL_RenderClear(program::renderer);

    SDL_SetRenderDrawColor(program::renderer, 255, 0, 0, 255);
    for(const auto& b : balls)
    {
        for(int w = 0; w < b.radius * 2; w++)
        {
            for(int h = 0; h < b.radius * 2; h++)
            {
                int dx = b.radius - w; // Distance from center
                int dy = b.radius - h;
                if((dx * dx + dy * dy) <= (b.radius * b.radius))
                {
                    SDL_RenderDrawPointF(program::renderer, b.x + dx, b.y + dy);
                }
            }
        }
    }

    program::print_text(5, 5, "Elastic Collision Simulation");

    SDL_RenderPresent(program::renderer);
}

bool elastic_collision::check_collision(const ball& a, const ball& b)
{
    float dx = b.x - a.x, dy = b.y - a.y;
    float distance = std::sqrt(dx * dx + dy * dy);
    return distance < (a.radius + b.radius);
}

void elastic_collision::resolve_collision(ball& a, ball& b)
{
    float dx = b.x - a.x, dy = b.y - a.y;
    float distance = std::sqrt(dx * dx + dy * dy);
    if(distance == 0.0f) return; // Avoid division by zero

    float nx = dx / distance, ny = dy / distance; // Normal vector
    float dvx = b.vx - a.vx, dvy = b.vy - a.vy; // Relative velocity

    // Dot product of relative velocity and normal vector
    float dot = dvx * nx + dvy * ny;
    if(dot > 0) return; // Prevent double collision resolution

    float m1 = a.mass, m2 = b.mass;
    float coef = (2 * dot) / (m1 + m2);

    // Update velocities
    a.vx += coef * m2 * nx;
    a.vy += coef * m2 * ny;
    b.vx -= coef * m1 * nx;
    b.vy -= coef * m1 * ny;
}

elastic_collision* elastic_collision::get()
{
    return &instance;
}