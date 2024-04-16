#include "arbitre.h"

#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <map>

using dimension = u_int16_t;


class interface{
public:
    interface();
    void play(t_number indDiff=0,bool jeu_duo=false);
    void menu();
    void menu_lan();
    void play2(t_number indDiff=0);
    void menu_regle();
    void load_textures();
    void load_texture(sf::Sprite &sprite, t_colors color, bool shade) const;

private:
    dimension _width;
    t_number_color _difficulty ;
    sf::Font _font;
    sf::SoundBuffer _buffer_sound_choice_move;
    sf::SoundBuffer _buffer_sound_loose ;
    sf::SoundBuffer _buffer_sound_play ;
    

    // Est-ce une bonne pratique
    // est-ce que je dois la mettre en static ? (logiquement)
    std::map<std::string, sf::Texture> _textures;
};
