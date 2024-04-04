#include "interface.h"
#include <cmath>

// #E882E8 color target
// #255,255,255 color case vide
// 
interface::interface() {}

void interface::play()
{
    sf::Color color_background = sf::Color::Black;
    t_number thickness_line = 10;
    sf::Color color_line = sf::Color(255, 87, 217);
    auto x(0.001);
    arbitre _arbitre;
    _arbitre.init();
    sf::RenderWindow window(sf::VideoMode((_arbitre.getJoueur().width() * 64 + 2 * thickness_line), (_arbitre.getJoueur().height() * 64 + 2 * thickness_line)), "Habibi");
    window.setFramerateLimit(30); // Pour set le framerate


    sf::RectangleShape line1(sf::Vector2f(thickness_line, 64 * _arbitre.getJoueur().height()+thickness_line));
    line1.setFillColor(color_line);
    sf::RectangleShape line2(sf::Vector2f(64 * _arbitre.getJoueur().width()+thickness_line, thickness_line));
    line2.setFillColor(color_line);
    sf::RectangleShape line3(sf::Vector2f(thickness_line, 64 * _arbitre.getJoueur().height()+thickness_line*2));
    line3.setFillColor(color_line);
    line3.setPosition(64*_arbitre.getJoueur().width()+thickness_line,0);
    sf::RectangleShape line4(sf::Vector2f(64 * _arbitre.getJoueur().width()+thickness_line*2, thickness_line));
    line4.setFillColor(color_line);
    line4.setPosition(0,64*_arbitre.getJoueur().height()+thickness_line);

            

    
    // sf::Vertex line1[] =
    //     {
    //         sf::Vertex(sf::Vector2f(10, 10)),
    //         sf::Vertex(sf::Vector2f(150, 150))};

    // window.draw(line1, 2, sf::Lines);
    // sf::Vertex line1[] =
    //     {
    //         sf::Vertex(sf::Vector2f(10, 10)),
    //         sf::Vertex(sf::Vector2f(150, 150))};

    // window.draw(line1, 2, sf::Lines);
    // sf::Vertex line1[] =
    //     {
    //         sf::Vertex(sf::Vector2f(10, 10)),
    //         sf::Vertex(sf::Vector2f(150, 150))};

    // window.draw(line1, 2, sf::Lines);


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
    while (window.isOpen() && !_arbitre.getJoueur().is_lost())
    {
        // TODO: a chaque fois que dy==30 il faut reelement faire monter la ligne
        // auto fps = 1.0f / (clock.restart().asSeconds());
        // std::cout << "fps: " << fps << "\n";

        sf::Event e;
        t_action act(t_action::nothing);
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                window.close();
            if (e.type == sf::Event::KeyPressed)
            {
                if (e.key.code == sf::Keyboard::RShift)
                    act = t_action::change_direction;
                else if (e.key.code == sf::Keyboard::Up)
                    act = (t_action::go_up);
                else if (e.key.code == sf::Keyboard::Left)
                    act = (t_action::go_left);
                else if (e.key.code == sf::Keyboard::Right)
                    act = (t_action::go_right);
                else if (e.key.code == sf::Keyboard::Down)
                    act = (t_action::go_down);
                else if (e.key.code == sf::Keyboard::Key::Space)
                {
                    act = (t_action::exchange);
                }
                else if (e.key.code == sf::Keyboard::Key::Enter)
                {
                    act = (t_action::accelerate);
                }
                else
                {
                    act = t_action::nothing;
                }
            }
        }
        auto vec(_arbitre.update(act));

        window.clear(color_background);

        // Affichage de la board "jouable"
        for (std::size_t i(0); i < _arbitre.getJoueur().height(); i++)
        {
            for (std::size_t j(0); j < _arbitre.getJoueur().width(); j++)
            {
                auto x(0.001);
                // On get la couleur actuelle

                auto color = _arbitre.getJoueur()(position(j, i));
                auto dx = _arbitre.getJoueur().cellDx(position(j, i));
                auto dy = _arbitre.getJoueur().cellDy(position(j, i));

                // on check quel sprite afficher
                switch (color)
                {
                case t_colors::blue:
                {
                    s_tile.setTexture(blue_tile_texture);
                    break;
                }
                case t_colors::pink:
                {
                    s_tile.setTexture(pink_tile_texture);
                    break;
                }
                case t_colors::yellow:
                {
                    s_tile.setTexture(yellow_tile_texture);
                    break;
                }
                case t_colors::orange:
                {
                    s_tile.setTexture(orange_tile_texture);
                    break;
                }
                case t_colors::empty_cell:
                {
                    s_tile.setTexture(empty_tile_texture);
                    break;
                }
                }

                if (vec.size() == 0)
                {
                    s_tile.setPosition(64 * j + dx +thickness_line, 64 * i + dy +thickness_line - _arbitre.getJoueur().grid_dy());
                    window.draw(s_tile);
                }
                else
                {
                    s_tile.setPosition(64 * j +thickness_line + dx, 64 * i +thickness_line + dy);
                    auto it(std::find(vec.begin(), vec.end(), position(j, i)));
                    if (it != vec.end())
                    {
                        if (x <= 360)
                        {
                            s_tile.setOrigin(64 / 2.f, 64 / 2.f);
                            s_tile.rotate(0.001f);

                            // float scaleFactor =1.f + std::sin(x * 3.14159f / 180) * 0.2f; // Variation de l'échelle en fonction de l'angle de rotation
                            // s_tile.setScale(scaleFactor, scaleFactor);
                            x += 0.001f;
                            window.draw(s_tile);
                        }

                        _arbitre.getJoueur().delete_cell(position(j, i));
                        _arbitre.getJoueur().slideColumn(j, _arbitre.getDelays().cells_slide);

                        window.draw(s_tile);
                        s_tile.setOrigin(0, 0);
                        vec.erase(it);
                    }
                }
                window.draw(s_tile);

                if (_arbitre.getJoueur().getcell1target() == position(j, i) || _arbitre.getJoueur().getcell2target() == position(j, i))
                {
                    if (vec.size() == 0)
                    {
                        s_target.setPosition(64 * j+thickness_line, 64 * i+thickness_line - _arbitre.getJoueur().grid_dy());
                    }
                    else
                    {
                        s_target.setPosition(64 * j, 64 * i);
                    }
                    window.draw(s_target);
                }
            }
        }

        if (vec.size() == 0)
        {

            // Affichage de la ligne qui monte
            for (std::size_t j(0); j < _arbitre.getJoueur().width(); j++)
            {
                // On get la couleur actuelle
                auto color = _arbitre.getJoueur()(position(j, _arbitre.getJoueur().height()));

                // on check quel sprite afficher
                switch (color)
                {
                case t_colors::blue:
                {
                    s_tile.setTexture(blue_shade_tile_texture);
                    break;
                }
                case t_colors::pink:
                {
                    s_tile.setTexture(pink_shade_tile_texture);
                    break;
                }
                case t_colors::yellow:
                {
                    s_tile.setTexture(yellow_shade_tile_texture);
                    break;
                }
                case t_colors::orange:
                {
                    s_tile.setTexture(orange_shade_tile_texture);
                    break;
                }
                case t_colors::empty_cell:
                {
                    s_tile.setTexture(empty_tile_texture);
                    break;
                } // cas non possible
                }
                s_tile.setPosition(64 * j+thickness_line, 64 * _arbitre.getJoueur().height() - _arbitre.getJoueur().grid_dy()+thickness_line); // adapter la vitesse par rapport a la taille de la fenetre
                window.draw(s_tile);
            }

        }
        // On update
        window.draw(line1);
        window.draw(line2);
        window.draw(line3);
        window.draw(line4);
        window.display();
    }
}
