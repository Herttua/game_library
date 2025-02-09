#ifndef TEXTURE_HH_
#define TEXTURE_HH_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class texture
{
public:
    texture();
    ~texture();

    bool         load(std::string file);
    bool         load_from_pixels();
    bool         load_pixels_from_file(std::string file);
    void         render(float x, float y, 
                        SDL_Rect* clip, 
                        double angle = 0.0f,
                        SDL_FPoint* center = nullptr, 
                        SDL_RendererFlip flip = SDL_FLIP_NONE);
    void free();

    Uint32* get_pixels32();
    Uint32  get_pixel32(Uint32 x, Uint32 y);
    Uint32  get_pitch32();

    int get_width();
    int get_height();

private:
    SDL_Texture* tex;
    SDL_Surface* surface_pixels;

    int width;
    int height;
};

void draw_rect(int x, int y, int w, int h, 
               int r, int g, int b, int a);

#endif //TEXTURE_HH_