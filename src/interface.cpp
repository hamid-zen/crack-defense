#include "interface.h"

interface::interface(){}

void interface::play()
{
    arbitre _arbitre;
    _arbitre.init();
    sf::RenderWindow window(sf::VideoMode(320, 768), "Habibi");
    window.setFramerateLimit(30); // Pour set le framerate

    // On charge les textures
    sf::Texture blue_tile_texture, yellow_tile_texture, orange_tile_texture, pink_tile_texture,
        blue_shade_tile_texture, yellow_shade_tile_texture, orange_shade_tile_texture,
        pink_shade_tile_texture, empty_tile_texture, target_texture;

    blue_tile_texture.loadFromFile("../textures/single_blocks/Blue_colored.png");
    yellow_tile_texture.loadFromFile("../textures/single_blocks/Yellow_colored.png");
    orange_tile_texture.loadFromFile("../textures/single_blocks/Orange_colored.png");
    pink_tile_texture.loadFromFile("../textures/single_blocks/Pink_colored.png");

    blue_shade_tile_texture.loadFromFile("../textures/single_blocks/Blue_shade.png");
    yellow_shade_tile_texture.loadFromFile("../textures/single_blocks/Yellow_shade.png");
    orange_shade_tile_texture.loadFromFile("../textures/single_blocks/Orange_shade.png");
    pink_shade_tile_texture.loadFromFile("../textures/single_blocks/Pink_shade.png");

    empty_tile_texture.loadFromFile("../textures/single_blocks/Ghost.png");
    target_texture.loadFromFile("../textures/single_blocks/Target.png");

    // On cree les sprite
    sf::Sprite s_tile, s_target(target_texture);

    // On cree la clock
    sf::Clock clock;
    while (window.isOpen() && !_arbitre.getJoueur().is_lost()) {
        // TODO: a chaque fois que dy==30 il faut reelement faire monter la ligne
        // auto fps = 1.0f / (clock.restart().asSeconds());
        // std::cout << "fps: " << fps << "\n";

           sf::Event e;
        t_action act(t_action::nothing);
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed)
                window.close();
            if (e.type == sf::Event::KeyPressed) {
                if (e.key.code == sf::Keyboard::RShift)
                    act=t_action::change_direction;
                else if (e.key.code == sf::Keyboard::Up)
                    act=(t_action::go_up);
                else if (e.key.code == sf::Keyboard::Left)
                    act=(t_action::go_left);
                else if (e.key.code == sf::Keyboard::Right)
                    act=(t_action::go_right);
                else if (e.key.code == sf::Keyboard::Down)
                    act=(t_action::go_down);
                 else if (e.key.code == sf::Keyboard::Key::Space){
                    act=(t_action::exchange);
                }
                else if(e.key.code == sf::Keyboard::Key::Enter){
                    act=(t_action::accelerate);
                }else {
                    act=t_action::nothing;
                }
            }
        }
        window.clear(sf::Color::White);

        // Affichage de la board "jouable"
        for (std::size_t i(0); i < _arbitre.getJoueur().height(); i++) {
            for (std::size_t j(0); j < _arbitre.getJoueur().width(); j++) {
                // On get la couleur actuelle
                auto color = _arbitre.getJoueur()(position(j, i));
                auto dx = _arbitre.getJoueur()(position(j, i));

                // on check quel sprite afficher
                switch (color) {
                case t_colors::blue: {
                    s_tile.setTexture(blue_tile_texture);
                    break;
                }
                case t_colors::pink: {
                    s_tile.setTexture(pink_tile_texture);
                    break;
                }
                case t_colors::yellow: {
                    s_tile.setTexture(yellow_tile_texture);
                    break;
                }
                case t_colors::orange: {
                    s_tile.setTexture(orange_tile_texture);
                    break;
                }
                case t_colors::empty_cell: {
                    s_tile.setTexture(empty_tile_texture);
                    break;
                }
                }
                
                if(_arbitre.getDelays().cells_switch1 and _arbitre.getDelays().cells_switch1->x()==j and _arbitre.getDelays().cells_switch1->y()==i){
                     s_tile.setPosition(64 * j + _arbitre.getDelays().cell1Dx , 64 * i - _arbitre.getVerticalSpeed() * _arbitre.getJoueur().grid_dy());
                     std::cout << "4";
                }
                else if (_arbitre.getDelays().cells_switch2 and _arbitre.getDelays().cells_switch2->x()==j and _arbitre.getDelays().cells_switch2->y()==i){
                    s_tile.setPosition(64 * j -  _arbitre.getDelays().cell2Dx, 64 * i - _arbitre.getVerticalSpeed() * _arbitre.getJoueur().grid_dy()); 
                    std::cout << "5" ;
                }

                else
                    s_tile.setPosition(64 * j, 64 * i - _arbitre.getVerticalSpeed() * _arbitre.getJoueur().grid_dy());
                window.draw(s_tile);
                if (_arbitre.getJoueur().getcell1target() == position(j, i) || _arbitre.getJoueur().getcell2target() == position(j, i)) {
                    s_target.setPosition(64 * j, 64 * i - _arbitre.getVerticalSpeed() * _arbitre.getJoueur().grid_dy());
                    window.draw(s_target);
                }
            }
        }

        // Affichage de la ligne qui monte
        for (std::size_t j(0); j < _arbitre.getJoueur().width(); j++) {
            // On get la couleur actuelle
            auto color = _arbitre.getJoueur()(position(j, _arbitre.getJoueur().height()));

            // on check quel sprite afficher
            switch (color) {
            case t_colors::blue: {
                s_tile.setTexture(blue_shade_tile_texture);
                break;
            }
            case t_colors::pink: {
                s_tile.setTexture(pink_shade_tile_texture);
                break;
            }
            case t_colors::yellow: {
                s_tile.setTexture(yellow_shade_tile_texture);
                break;
            }
            case t_colors::orange: {
                s_tile.setTexture(orange_shade_tile_texture);
                break;
            }
            case t_colors::empty_cell: {
                s_tile.setTexture(empty_tile_texture);
                break;
            } // cas non possible
            }
            s_tile.setPosition(64 * j, 64 * _arbitre.getJoueur().height() - _arbitre.getVerticalSpeed() * _arbitre.getJoueur().grid_dy()); // adapter la vitesse par rapport a la taille de la fenetre
            window.draw(s_tile);
        }
        
        // On update
        if (_arbitre.getVerticalSpeed() * _arbitre.getJoueur().grid_dy() >= 64) {
            _arbitre.getJoueur().add_new_row();
            //On remet a zero grid_dy
            _arbitre.getJoueur().setGrid_dy(0);
        }
        else
            _arbitre.getJoueur().setGrid_dy(_arbitre.getJoueur().grid_dy()+1);
        
        
         _arbitre.update(act);
        window.display();
    }
}
