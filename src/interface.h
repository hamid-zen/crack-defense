#include "arbitre.h"
#include<iostream>
using dimension = u_int16_t;


class interface{
public:
    interface();
    void play(t_number indDif=0);
    void play2(t_number indDif=0);
    void menu();
    void load_textures();

private:
    dimension _width;
    t_number_color _difficulty ;
    sf::Font _font;

    // Est-ce une bonne pratique
    // est-ce que je dois la mettre en static ? (logiquement)
    sf::Texture
                blue_tile_texture,
                yellow_tile_texture,
                orange_tile_texture,
                pink_tile_texture,
                sky_blue_tile_texture,//
                purple_tile_texture,
                green_tile_texture,
                white_tile_texture,

                blue_shade_tile_texture,
                yellow_shade_tile_texture,
                orange_shade_tile_texture,
                pink_shade_tile_texture,
                red_shade_tile_texture,
                sky_blue_shade_tile_texture,
                purple_shade_tile_texture,
                green_shade_tile_texture,
                white_shade_tile_texture,

                empty_tile_texture,
                target_texture,
                all_tile_texture;
};
