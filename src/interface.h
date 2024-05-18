#include "arbitre.h"

#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <vector>

using dimension = u_int16_t;

enum class t_textures {
    Blue, Red, Yellow, Orange, Pink, All, SkyBlue, Purple, Green, White,
    BlueShade, YellowShade, OrangeShade, PinkShade, RedShade, SkyBlueShade, PurpleShade, GreenShade, WhiteShade,
    Ghost, Target, Ctrl, DirectionalArrows, Shift, Tab, Enter, Esc, DirectionalKeys, Blue_XP, Yellow_XP, Pink_XP,
    loading_0, loading_1, loading_2, loading_3, loading_4, game_over, pause, check_mark
};

t_number t_textures_to_index(t_textures texture);

class interface{
public:
    interface();
    void intro();
    void play();
    void menu();
    void menu_lan(bool disconnected= false);
    void game_over_screen(bool first_player_lost= true, t_number score = 0); // si first_player alors first_player a perdu
    void pause_screen();
    void play2(t_number indDiff=0);
    void menu_regle();
    void load_textures();
    void load_texture(sf::Sprite &sprite, t_colors color, bool shade) const;

private:
    dimension _width;
    t_number_color _difficulty ;
    sf::Font _font;
    std::unique_ptr<arbitre> _arbitre; // pointeur car au debut oil doit etre vide (et doit etre init apres le choix de tout les params: duo/solo/wlan, difficulté)
    sf::SoundBuffer _buffer_sound_choice_move;
    sf::SoundBuffer _buffer_sound_loose;
    sf::SoundBuffer _buffer_sound_play;
    sf::SoundBuffer _buffer_sound_xp;
    
    // Est-ce une bonne pratique
    // est-ce que je dois la mettre en static ? (logiquement)
    std::vector<sf::Texture> _textures;
};
