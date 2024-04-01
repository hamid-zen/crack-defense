#include "arbitre.h"

arbitre::arbitre()
    : _joueur1(std::make_unique<game>())
    , _vertical_speed(0.5)
{}

void arbitre::play()
{
    //recuperer les paramettre
    _joueur1->init();

    sf::RenderWindow window(sf::VideoMode(320, 768), "Habibi");
    window.setFramerateLimit(30); // Pour set le framerate

    // On charge les textures
    sf::Texture blue_tile_texture, yellow_tile_texture, orange_tile_texture, pink_tile_texture,
        blue_shade_tile_texture, yellow_shade_tile_texture, orange_shade_tile_texture,
        pink_shade_tile_texture, empty_tile_texture, target_texture;

    blue_tile_texture.loadFromFile("textures/single_blocks/Blue_colored.png");
    yellow_tile_texture.loadFromFile("textures/single_blocks/Yellow_colored.png");
    orange_tile_texture.loadFromFile("textures/single_blocks/Orange_colored.png");
    pink_tile_texture.loadFromFile("textures/single_blocks/Pink_colored.png");

    blue_shade_tile_texture.loadFromFile("textures/single_blocks/Blue_shade.png");
    yellow_shade_tile_texture.loadFromFile("textures/single_blocks/Yellow_shade.png");
    orange_shade_tile_texture.loadFromFile("textures/single_blocks/Orange_shade.png");
    pink_shade_tile_texture.loadFromFile("textures/single_blocks/Pink_shade.png");

    empty_tile_texture.loadFromFile("textures/single_blocks/Ghost.png");
    target_texture.loadFromFile("textures/single_blocks/Target.png");

    // On cree les sprite
    sf::Sprite s_tile, s_target(target_texture);

    // On cree la clock
    sf::Clock clock;

    while (window.isOpen() && !_joueur1->is_lost()) {
        // TODO: a chaque fois que dy==30 il faut reelement faire monter la ligne
        // auto fps = 1.0f / (clock.restart().asSeconds());
        // std::cout << "fps: " << fps << "\n";

        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed)
                window.close();

            if (e.type == sf::Event::KeyPressed) {
                if (e.key.code == sf::Keyboard::RShift)
                    _joueur1->rotate_target();
                else if (e.key.code == sf::Keyboard::Up)
                    _joueur1->move_target(t_direction::up);
                else if (e.key.code == sf::Keyboard::Left)
                    _joueur1->move_target(t_direction::left);
                else if (e.key.code == sf::Keyboard::Right)
                    _joueur1->move_target(t_direction::right);
                else if (e.key.code == sf::Keyboard::Down)
                    _joueur1->move_target(t_direction::down);
                else if (e.key.code == sf::Keyboard::Enter)
                    _joueur1->switch_cells_target();
            }
        }
        window.clear(sf::Color::White);

        // Affichage de la board "jouable"
        for (std::size_t i(0); i < _joueur1->height(); i++) {
            for (std::size_t j(0); j < _joueur1->width(); j++) {
                // On get la couleur actuelle
                auto color = (*_joueur1)(position(j, i));
                auto dx = (*_joueur1)(position(j, i));

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
                s_tile.setPosition(64 * j, 64 * i - _vertical_speed * _joueur1->grid_dy());
                window.draw(s_tile);
                if (_joueur1->getcell1target() == position(j, i) || _joueur1->getcell2target() == position(j, i)) {
                    s_target.setPosition(64 * j, 64 * i - _vertical_speed * _joueur1->grid_dy());
                    window.draw(s_target);
                }
            }
        }

        // Affichage de la ligne qui monte
        for (std::size_t j(0); j < _joueur1->width(); j++) {
            // On get la couleur actuelle
            auto color = (*_joueur1)(position(j, _joueur1->height()));

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
            s_tile.setPosition(64 * j, 64 * _joueur1->height() - _vertical_speed * _joueur1->grid_dy()); // adapter la vitesse par rapport a la taille de la fenetre
            window.draw(s_tile);
        }

        // On update
        if (_vertical_speed * _joueur1->grid_dy() >= 64) {
            _joueur1->add_new_row();
            //On remet a zero grid_dy
            _joueur1->setGrid_dy(0);
        }
        else
            _joueur1->setGrid_dy(_joueur1->grid_dy()+1);
        _vertical_speed += 0.00001;
        window.display();
    }
}
