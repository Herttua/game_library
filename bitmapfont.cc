#include "bitmapfont.hh"
#include <iostream>

bitmapfont::bitmapfont() : newline(0), space(0) {}
bitmapfont::~bitmapfont() {}

bool bitmapfont::build_font(std::string file, int spacing, int new_l)
{
    free();
    //std::cout << "Building font\n";
    
    space = spacing;
    newline = new_l;
    bool success = true;

    if(!f_texture.load_pixels_from_file(file))
    {
        std::cout << "Unable to load bitmap font surface!\n";
        success = false;
    }
    else
    {
        Uint32 bg_color = f_texture.get_pixel32(0, 0);

        int cell_w = f_texture.get_width() / 16;
        int cell_h = f_texture.get_height() / 16;

        int top = cell_h;
        int base_a = cell_h;
        int current_char = 0;

        //Go through the cell rows
        for(int rows = 0; rows < 16; ++rows)
        {
            //Go through the cell columns
            for(int cols = 0; cols < 16; ++cols)
            {
                chars[current_char].x = cell_w * cols;
                chars[current_char].y = cell_h * rows;
                chars[current_char].w = cell_w;
                chars[current_char].h = cell_h;

                //Find left side
                //Go through pixel columns
                for(int p_col = 0; p_col < cell_w; ++p_col)
                {
                    for(int p_row = 0; p_row < cell_h; ++p_row)
                    {
                        //Get the pixel offsets
                        int p_x = (cell_w * cols) + p_col;
                        int p_y = (cell_h * rows) + p_row;

                        //If a non colorkey pixel is found
                        if(f_texture.get_pixel32(p_x, p_y) != bg_color)
                        {
                            chars[current_char].x = p_x;
                            p_col = cell_w;
                            p_row = cell_h;
                        }
                    }
                }

                //Find the right side
                //Go through pixel columns
                for(int p_col_w = cell_w - 1; p_col_w >= 0; --p_col_w)
                {
                    for(int p_row_w = 0; p_row_w < cell_h; ++p_row_w)
                    {
                        int p_x = (cell_w * cols) + p_col_w;
                        int p_y = (cell_h * rows) + p_row_w;
                        
                        if(f_texture.get_pixel32(p_x, p_y) != bg_color)
                        {
                            //Set the width
                            chars[current_char].w = (p_x - chars[current_char].x) + 1;

                            //Break the loops
                            p_col_w = -1;
                            p_row_w = cell_h;
                        }
                    }
                }

                    //Find top
                    //Go through pixel rows
                    for(int p_row = 0; p_row < cell_h; ++p_row)
                    {
                        for(int p_col = 0; p_col < cell_w; ++p_col)
                        {
                            int p_x = (cell_w * cols) + p_col;
                            int p_y = (cell_h * rows) + p_row;

                            if(f_texture.get_pixel32(p_x, p_y) != bg_color)
                            {
                                if(p_row < top)
                                {
                                    top = p_row;
                                }

                                //Break the loops
							    p_col = cell_w;
							    p_row = cell_h;
                            }
                        }
                    }

                    //Find bottom of A
                    if(current_char == 'A')
                    {
                        for(int p_row = cell_h - 1; p_row >= 0; --p_row)
                        {
                            for(int p_col = 0; p_col < cell_w; ++p_col)
                            {
                                int p_x = (cell_w * cols) + p_col;
                                int p_y = (cell_h * rows) + p_row;

                                if(f_texture.get_pixel32(p_x, p_y) != bg_color)
                                {
                                    base_a = p_row;
                                    p_col = cell_w;
                                    p_row = -1;
                                }
                            }
                        }
                    }
                current_char++;
            }
        }
        
        //Calculate space
        //space = cell_w / 4;
        
        //Calculate new line
        //new_line = base_a -top;
        
        //Lop off excess top pixels
        for(int i = 0; i < 256; ++i)
        {
            chars[i].y += top;
            chars[i].h -= top;
        }

        //Create final texture
        if(!f_texture.load_from_pixels())
        {
            std::cout << "Unable to create font texture\n";
            success = false;
        }
    }
    std::cout << "Font loaded\n";
    return success;
}

void bitmapfont::render_text(int x, int y, std::string txt)
{
     if(f_texture.get_width() > 0)
    {
        int cur_x = x; 
        int cur_y = y;

        //Go through the text
        for(int i = 0; i < txt.length(); ++i)
        {
            //If the character is a space
            if(txt[i] == ' ')
            {
                //Move over
                cur_x += space;
            }
            //If the current character is a newline
            else if(txt[i] == '\n')
            {
                cur_y += newline;
                cur_x = x;
            }
            else
            {
                int ascii = (unsigned char)txt[i];
                f_texture.render(cur_x, cur_y, &chars[ascii], 0.0, 
                                    nullptr, 
                                    SDL_FLIP_NONE);
                cur_x += chars[ascii].w + 1;
            }
        }
    }
}

void bitmapfont::free()
{
    f_texture.free();
}