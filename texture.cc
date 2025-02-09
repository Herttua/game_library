#include "texture.hh"
#include "program.hh"

const SDL_FPoint* origo = nullptr;

texture::texture() {}
texture::~texture()
{
    SDL_FreeSurface(surface_pixels);
    free();
}

bool texture::load(std::string file)
{
    free();

    SDL_Texture* new_texture = 0;
    SDL_Surface* loaded_surface = IMG_Load(file.c_str());
    if(loaded_surface == 0)
    {
        std::cout << "Unable to load image! SDL_image error:\n" << IMG_GetError(); 
    }
    else
    {
        SDL_SetColorKey(loaded_surface, SDL_TRUE, SDL_MapRGB(loaded_surface->format,
							     0, 0xFF, 0xFF));
	                new_texture = SDL_CreateTextureFromSurface(program::renderer, loaded_surface);
        if(new_texture == 0)
        {
            std::cout << "Unable to create texture from " << file.c_str()
		                                                  << " SDL Error: " <<
	                                                      SDL_GetError() << std::endl;
        }
        else
        {
            width = loaded_surface->w;
            height = loaded_surface->h;
        }
        SDL_FreeSurface(loaded_surface);
    }
    tex = new_texture;
    return tex != nullptr;
}

void texture::free()
{
    if(tex != 0)
    {
        SDL_DestroyTexture(tex);
        width  = 0;
        height = 0;
    }
}

bool texture::load_from_pixels()
{
    if(surface_pixels == nullptr)
    {
        std::cout << "No pixels loaded!\n";
    }
    else
    {
        SDL_SetColorKey(surface_pixels, SDL_TRUE, 
                        SDL_MapRGB(surface_pixels->format, 0, 0xFF, 0xFF));
        tex = SDL_CreateTextureFromSurface(program::renderer, surface_pixels);
        if(tex == nullptr)
        {
            std::cout << "Unable to create texture from pixels! " << SDL_GetError();
        }
        else
        {
            width = surface_pixels->w;
            height = surface_pixels->h;
        }
        SDL_FreeSurface(surface_pixels);
        surface_pixels = nullptr;
    }
    return tex != nullptr;
}

bool texture::load_pixels_from_file(std::string file)
{
    free();
    SDL_Surface* loaded_surface = IMG_Load(file.c_str());
    if(loaded_surface == nullptr)
    {
        std::cout << "Unable to load image! " << IMG_GetError();
    }
    else
    {
        surface_pixels = SDL_ConvertSurfaceFormat(loaded_surface, 
                                                  SDL_GetWindowPixelFormat(program::window), 
                                                  0);
        if(surface_pixels == nullptr)
        {
            std::cout << "Unable to convert loaded surface to display format! " 
                      << SDL_GetError();
        }
        else
        {
            width = surface_pixels->w;
            height = surface_pixels->h;
        }
        SDL_FreeSurface(loaded_surface);
    }
    return surface_pixels != nullptr;
}

void texture::render(float x, float y, 
                   SDL_Rect* clip, 
                   double angle,
                   SDL_FPoint* center, 
                   SDL_RendererFlip flip)
{
    SDL_FRect render_quad = { x, y, 96, 96 };
    if(clip != 0)
    {
        render_quad.w = clip->w;
        render_quad.h = clip->h;
    }
    SDL_RenderCopyExF(program::renderer, tex, clip, &render_quad, angle, center, flip);
}

Uint32* texture::get_pixels32()
{
    Uint32* pixels = nullptr;
    if(surface_pixels != nullptr)
    {
        pixels = static_cast<Uint32*>(surface_pixels->pixels);
    }
    return pixels;
}

Uint32 texture::get_pixel32(Uint32 x, Uint32 y)
{
    Uint32* pixels = static_cast<Uint32*>(surface_pixels->pixels);
    return pixels[(y * get_pitch32()) + x];
}

Uint32 texture::get_pitch32()
{
    Uint32 pitch = 0;
    if(surface_pixels != nullptr)
    {
        pitch = surface_pixels->pitch / 4;
    }
    return pitch;
}

int texture::get_width()  { return width;  }
int texture::get_height() { return height; }

void draw_rect(int x, int y, int w, int h, 
               int r, int g, int b, int a)
{
    SDL_Rect fill_rect = { x, y, w, h };
    SDL_SetRenderDrawColor(program::renderer, r, g, b, a);
    SDL_RenderFillRect(program::renderer, &fill_rect);
}

