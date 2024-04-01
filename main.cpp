#include "src/arbitre.h"
#include <SFML/Graphics.hpp>
#include <iostream>

//TODO: tout traduire en une seule langue

void test()
{
    game g;

    sf::RenderWindow window(sf::VideoMode(320, 480), "Habibi");

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
    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed)
                window.close();

            if (e.type == sf::Event::KeyPressed) {
                if (e.key.code == sf::Keyboard::RShift)
                    g.rotate_target();
                else if (e.key.code == sf::Keyboard::Up)
                    g.move_target(t_direction::up);
                else if (e.key.code == sf::Keyboard::Left)
                    g.move_target(t_direction::left);
                else if (e.key.code == sf::Keyboard::Right)
                    g.move_target(t_direction::right);
                else if (e.key.code == sf::Keyboard::Down)
                    g.move_target(t_direction::down);
                else if (e.key.code == sf::Keyboard::Enter)
                    g.switch_cells_target();
            }
        }
        window.clear(sf::Color::White);

        // Affichage de la board "jouable"
        for (std::size_t i(0); i < g.height(); i++) {
            for (std::size_t j(0); j < g.width(); j++) {
                // On get la couleur actuelle
                auto color = g(position(j, i));

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
                s_tile.setScale(0.5, 0.5);
                s_tile.setPosition(30 * j, 30 * i);
                window.draw(s_tile);
                if (g.getcell1target() == position(j, i) || g.getcell2target() == position(j, i)) {
                    s_target.setPosition(30 * j, 30 * i);
                    window.draw(s_target);
                }
            }
        }

        // Affichage de la ligne qui monte
        for (std::size_t j(0); j < g.width(); j++) {
            // On get la couleur actuelle
            auto color = g(position(j, g.height()));

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
            s_tile.setScale(0.5, 0.5);
            s_tile.setPosition(30 * j, 30 * g.height());
            window.draw(s_tile);
        }

        window.display();
    }
}
int main(){
    arbitre a;
    a.play();
    return 0;
}
