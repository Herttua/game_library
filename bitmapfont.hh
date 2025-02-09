#ifndef BITMAPFONT_HH_
#define BITMAPFONT_HH_

#include "texture.hh"

class bitmapfont
{
public:
    bitmapfont();
    ~bitmapfont();

    bool build_font(std::string file, int spacing, int new_l);
    void free();
    void render_text(int x, int y, std::string txt);

    texture f_texture;
    SDL_Rect chars[256];
    int newline;
    int space;
};

#endif //BITMAPFONT_HH_