#include "interface.h"

// #E882E8 color target
// #255,255,255 color case vide
// 
interface::interface():_width(6),_difficulty(4) {
    _font.loadFromFile("../font/cyber_game.ttf");
}

void interface::play(t_number ind)
{
    arbitre _arbitre(ind);
    _arbitre.init();

    sf::Color color_background = sf::Color::Black;
    t_number thickness_line = 10;
    sf::Color color_line = sf::Color(255, 87, 217);
    t_number _width_cell = 64 ;
    t_number score_tab_width = 500 ;
    t_number play_tab_width = _arbitre.getJoueur().width() * _width_cell + 2 * thickness_line;
    t_number total_width = score_tab_width + play_tab_width;
    t_number total_height = _arbitre.getJoueur().height() * _width_cell + 2 * thickness_line ;
    auto x(0.001);

    // On init la partie affichage du score
    sf::Text _text_score = sf::Text("SCORE",_font,60);
    _text_score.setOrigin(sf::Vector2f((_text_score.getGlobalBounds().width)/(2*_text_score.getScale().x),(_text_score.getGlobalBounds().height)/(2*_text_score.getScale().y)));
    _text_score.setPosition(sf::Vector2f(play_tab_width+(score_tab_width/2),total_height/2));
    _text_score.setFillColor(color_line);

    sf::Text _number_score = sf::Text(std::to_string(_arbitre.getJoueur().get_score()),_font,60);
    _number_score.setOrigin(sf::Vector2f((_number_score.getGlobalBounds().width)/(2*_number_score.getScale().x),(_number_score.getGlobalBounds().height)/(2*_number_score.getScale().y)));
    _number_score.setPosition(sf::Vector2f(play_tab_width+(score_tab_width/2),total_height/2 + 100));
    _number_score.setFillColor(color_line);


    // On init la window
    sf::RenderWindow window(sf::VideoMode((total_width), (total_height)), "Habibi");
    window.setFramerateLimit(30);

    // test
    sf::RectangleShape square(sf::Vector2f(64, 64));
    square.setPosition(play_tab_width+32, thickness_line+32);
    square.setOrigin(sf::Vector2f((square.getGlobalBounds().width)/(2*square.getScale().x),(square.getGlobalBounds().height)/(2*square.getScale().y)));
    square.setFillColor(sf::Color::Blue);


    // On dessine les bordures
    sf::RectangleShape line1(sf::Vector2f(thickness_line, total_height-thickness_line));
    line1.setFillColor(color_line);
    //sf::RectangleShape line2(sf::Vector2f(64 * _arbitre.getJoueur().width()+thickness_line, thickness_line));
    sf::RectangleShape line2(sf::Vector2f(total_width, thickness_line));
    line2.setFillColor(color_line);
    sf::RectangleShape line3(sf::Vector2f(thickness_line, total_height-thickness_line));
    line3.setFillColor(color_line);
    line3.setPosition(play_tab_width-thickness_line,0);
    sf::RectangleShape line4(sf::Vector2f(total_width, thickness_line));
    line4.setFillColor(color_line);
    line4.setPosition(0,total_height-thickness_line);
    sf::RectangleShape line5(sf::Vector2f(thickness_line, total_height ));
    line5.setFillColor(color_line);
    line5.setPosition(total_width-thickness_line,0);

    // On charge les textures
    load_textures();

    // On cree les sprite
    sf::Sprite s_tile, s_target(target_texture);
    s_tile.setOrigin(sf::Vector2f((s_tile.getGlobalBounds().width)/(2*s_tile.getScale().x),(s_tile.getGlobalBounds().height)/(2*s_tile.getScale().y)));
    //s_tile.setOrigin(-_width_cell/2,-_width_cell/2);

    while (window.isOpen() && !_arbitre.getJoueur().is_lost())
    {
        window.clear(color_background);
        square.rotate(15);
        sf::Event e;
        t_action action_utilisateur(t_action::nothing);
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                window.close();
            if (e.type == sf::Event::KeyPressed)
            {
                switch (e.key.code) {
                case sf::Keyboard::RShift:
                    action_utilisateur = t_action::change_direction;
                    break;
                case sf::Keyboard::Up:
                    action_utilisateur = t_action::go_up;
                    break;
                case sf::Keyboard::Left:
                    action_utilisateur = t_action::go_left;
                    break;
                case sf::Keyboard::Right:
                    action_utilisateur = t_action::go_right;
                    break;
                case sf::Keyboard::Down:
                    action_utilisateur = t_action::go_down;
                    break;
                case sf::Keyboard::Space:
                    action_utilisateur = t_action::exchange;
                    break;
                case sf::Keyboard::Enter:
                    action_utilisateur = t_action::accelerate;
                    break;
                case sf::Keyboard::M:
                    action_utilisateur = t_action::generate_malus;
                    break;
                case sf::Keyboard::Escape:{
                    window.close();
                    menu(ind);
                    break;
                }
                default:
                    action_utilisateur = t_action::nothing;
                    break;
                }
            }
        }

        // Traitement du score
        t_number _temp_score = _arbitre.getJoueur().get_score();
        if(_temp_score>100)
            _number_score.setString(sf::String(std::to_string(_temp_score/100)+std::to_string(_temp_score%100)));
        else if(_temp_score>10)
            _number_score.setString(sf::String(std::to_string(_temp_score/10)+std::to_string(_temp_score%10)));
        else
            _number_score.setString(sf::String(std::to_string(_temp_score)));
        _number_score.setOrigin(sf::Vector2f((_number_score.getGlobalBounds().width)/(2*_number_score.getScale().x),(_number_score.getGlobalBounds().height)/(2*_number_score.getScale().y)));

        // On update l'etat du jeu
        _arbitre.update(action_utilisateur);
        auto vec(_arbitre.getDelays().cells_align);

        // Affichage de la board
        for (std::size_t i(0); i < _arbitre.getJoueur().height(); i++)
        {
            for (std::size_t j(0); j < _arbitre.getJoueur().width(); j++)
            {
                t_number x(0);

                auto dx = _arbitre.getJoueur().cellDx(position(j, i));
                auto dy = _arbitre.getJoueur().cellDy(position(j, i));
                if(_arbitre.getJoueur().is_garbage(position(j,i))){
                    s_tile.setTexture(red_shade_tile_texture);
                    s_tile.setPosition(_width_cell * j + dx +thickness_line, _width_cell * i + dy +thickness_line - _arbitre.getJoueur().grid_dy());
                    window.draw(s_tile);
                }else{
                    auto color = _arbitre.getJoueur()(position(j, i));


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
                    case t_colors::sky_blue:
                    {
                        s_tile.setTexture(sky_blue_tile_texture);
                        break;
                    }
                    case t_colors::purple:
                    {
                        s_tile.setTexture(purple_tile_texture);
                        break;
                    }
                    case t_colors::green:
                    {
                        s_tile.setTexture(green_tile_texture);
                        break;
                    }
                    case t_colors::white:
                    {
                        s_tile.setTexture(white_tile_texture);
                        break;
                    }
                    case t_colors::empty_cell:
                    {
                        s_tile.setTexture(empty_tile_texture);
                        break;
                    }
                    case t_colors::all:{
                        s_tile.setTexture(all_tile_texture);
                        break;
                    }
                    default: break;
                    }

                    if (vec.size() == 0)
                        s_tile.setPosition(_width_cell * j + dx +thickness_line, _width_cell * i + dy +thickness_line - _arbitre.getJoueur().grid_dy());
                    else
                    {
                        s_tile.setPosition(_width_cell * j +thickness_line + dx, _width_cell * i +thickness_line + dy);
                        auto it(std::find(vec.begin(), vec.end(), position(j, i)));
                        if (it != vec.end())
                        {
                            if (x <= 360)
                            {
                                //s_tile.setOrigin(64 / 2.f, 64 / 2.f);
                                s_tile.rotate(0.001f);

                                // float scaleFactor =1.f + std::sin(x * 3.14159f / 180) * 0.2f; // Variation de l'échelle en fonction de l'angle de rotation
                                // s_tile.setScale(scaleFactor, scaleFactor);
                                x += 0.001f;
                                window.draw(s_tile);
                            }

                            _arbitre.getJoueur().delete_cell(position(j, i));
                            _arbitre.getJoueur().slideColumn(j, _arbitre.getDelays().cells_slide);

                            window.draw(s_tile);
                            //s_tile.setOrigin(0, 0);
                            vec.erase(it);
                        }
                    }
                    window.draw(s_tile);
                }

                // Dessin de la target
                if (_arbitre.getJoueur().getcell1target() == position(j, i) || _arbitre.getJoueur().getcell2target() == position(j, i))
                {
                    if (vec.size() == 0)
                        s_target.setPosition(64 * j+thickness_line, 64 * i+thickness_line - _arbitre.getJoueur().grid_dy());
                    else
                        s_target.setPosition(_width_cell * j, _width_cell * i);
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
                case t_colors::sky_blue:
                {
                    s_tile.setTexture(sky_blue_shade_tile_texture);
                    break;
                }
                case t_colors::purple:
                {
                    s_tile.setTexture(purple_shade_tile_texture);
                    break;
                }
                case t_colors::green:
                {
                    s_tile.setTexture(green_shade_tile_texture);
                    break;
                }
                case t_colors::white:
                {
                    s_tile.setTexture(white_shade_tile_texture);
                    break;
                }
                default: break;
                }
                s_tile.setPosition(_width_cell * j+thickness_line, _width_cell * _arbitre.getJoueur().height() - _arbitre.getJoueur().grid_dy()+thickness_line); // adapter la vitesse par rapport a la taille de la fenetre
                window.draw(s_tile);
            }

        }

        // On display
        window.draw(_number_score);
        window.draw(_text_score);
        window.draw(line1);
        window.draw(line2);
        window.draw(line3);
        window.draw(line4);
        window.draw(line5);
        window.draw(square);
        window.display();
    }
}

void interface::menu(t_number ind){

    //needed base variable
    t_number thickness_line = 10;
    t_number width_window = _width * 64 + 2 * thickness_line;
    t_number height_window = 12 * 64 + 2 * thickness_line; 
    sf::Color color_background = sf::Color::Black;
    sf::Color color_line = sf::Color(255, 87, 217);

    //window
    sf::RenderWindow window(sf::VideoMode(width_window, height_window), "Habibi");
    window.setFramerateLimit(30); // Pour set le framerate

    //border
    sf::RectangleShape line1(sf::Vector2f(thickness_line, 64 * 12 +thickness_line));
    line1.setFillColor(color_line);
    sf::RectangleShape line2(sf::Vector2f(width_window-thickness_line, thickness_line));
    line2.setFillColor(color_line);
    sf::RectangleShape line3(sf::Vector2f(thickness_line, height_window + thickness_line)); 
    line3.setFillColor(color_line);
    line3.setPosition(width_window-thickness_line,0);
    sf::RectangleShape line4(sf::Vector2f(width_window, thickness_line));
    line4.setFillColor(color_line);
    line4.setPosition(0,height_window-thickness_line);


    //text declaration
    sf::Text _text_difficulty(sf::String("DIFFICULTY"),_font);
    sf::Text _text_number_player(sf::String("NUMBER OF PLAYER"),_font);
    sf::Text _text_menu(sf::String("MENU"),_font);
    sf::Text _difficulty_choice(sf::String("EASY"),_font);
    sf::Text _number_player_choice(sf::String("SOLO"),_font);
    sf::Text _text_play(sf::String("PLAY"),_font);


    //text scale
    
    _text_menu.setScale(2,2);
    _text_difficulty.setScale(1.5,1.5);
    _text_number_player.setScale(1.5,1.5);
    _text_play.setScale(1.5,1.5);
    _difficulty_choice.setScale(1.5,1.5);
    _number_player_choice.setScale(1.5,1.5);
    



    //textorigin 
    _text_menu.setOrigin(sf::Vector2f((_text_menu.getGlobalBounds().width)/(2*_text_menu.getScale().x),(_text_menu.getGlobalBounds().height)/(2*_text_menu.getScale().y)));
    _text_difficulty.setOrigin(sf::Vector2f((_text_difficulty.getGlobalBounds().width)/(2*_text_difficulty.getScale().x),(_text_difficulty.getGlobalBounds().height)/(2*_text_difficulty.getScale().y)));
    _text_number_player.setOrigin(sf::Vector2f((_text_number_player.getGlobalBounds().width)/(2*_text_number_player.getScale().x),(_text_number_player.getGlobalBounds().height)/(2*_text_number_player.getScale().y)));
    _text_play.setOrigin(sf::Vector2f((_text_play.getGlobalBounds().width)/(2*_text_play.getScale().x),(_text_play.getGlobalBounds().height)/(2*_text_play.getScale().y)));
    _difficulty_choice.setOrigin(sf::Vector2f((_difficulty_choice.getGlobalBounds().width)/(2*_difficulty_choice.getScale().x),(_difficulty_choice.getGlobalBounds().height)/(2*_difficulty_choice.getScale().y)));
    _number_player_choice.setOrigin(sf::Vector2f((_number_player_choice.getGlobalBounds().width)/(2*_number_player_choice.getScale().x),(_number_player_choice.getGlobalBounds().height)/(2*_number_player_choice.getScale().y)));


    //textposition 
    _text_menu.setPosition(width_window/2  , thickness_line + height_window / 20);
    _text_difficulty.setPosition(width_window/2  ,thickness_line + height_window / 1.75);
    _text_number_player.setPosition(width_window/2  ,thickness_line  + height_window / 3);
    _text_play.setPosition(width_window/2  ,thickness_line  + height_window / 1.2);
    _difficulty_choice.setPosition(width_window/2  ,thickness_line  + height_window / 1.5);
    _number_player_choice.setPosition(width_window/2  ,thickness_line  + height_window / 2.35);


    //text_color
    _text_menu.setFillColor(color_line);
    _text_difficulty.setFillColor(color_line);
    _text_number_player.setFillColor(color_line);
    _text_play.setFillColor(color_line);
    _difficulty_choice.setFillColor(color_line);
    _number_player_choice.setFillColor(color_line);



    //vector choice_pos 
    std::vector<sf::Transformable *> _choices_pos;
    t_number _index_choice_pos = 0; 

    //add choice_pos

    _choices_pos.push_back(&_number_player_choice);
    _choices_pos.push_back(&_difficulty_choice);
    _choices_pos.push_back(&_text_play);

    //rectangle_choice
    sf::RectangleShape _choice_target(sf::Vector2f(_difficulty_choice.getGlobalBounds().width + 20,_difficulty_choice.getGlobalBounds().height + 20));
    _choice_target.setFillColor(sf::Color::Transparent);
    _choice_target.setOutlineThickness(5);
    _choice_target.setOutlineColor(sf::Color::Yellow);
    _choice_target.setOrigin(_choice_target.getGlobalBounds().width/2,_choice_target.getGlobalBounds().height/2);
    _choice_target.setPosition(sf::Vector2f( _choices_pos[_index_choice_pos]->getPosition().x+5,_choices_pos[_index_choice_pos]->getPosition().y+17));

    //difficulty_choice
    std::vector<sf::String> _vector_difficulties_choice;
    t_number _index_difficulties_choice=0;
    _vector_difficulties_choice.push_back(sf::String("EASY"));
    _vector_difficulties_choice.push_back(sf::String("MIDD"));
    _vector_difficulties_choice.push_back(sf::String("HARD"));

    //number_player_choice
    std::vector<sf::String>_vector_number_player_choice;
    t_number _index_number_player_choice=0;
    _vector_number_player_choice.push_back(sf::String("SOLO"));
    _vector_number_player_choice.push_back(sf::String("DUAL"));

    


    while(window.isOpen()){
        sf::Event e;
        



        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                window.close();
            if (e.type == sf::Event::KeyPressed)
            {
                
                if (e.key.code == sf::Keyboard::Key::Enter)
                {
                    if(_index_choice_pos == _choices_pos.size()-1){
                        window.close();
                        play(_index_difficulties_choice);
                    }
                }
                else if(e.key.code == sf::Keyboard::Key::Escape)
                {
                    window.close();
                }
                else if(e.key.code == sf::Keyboard::Key::Up)
                {   
                    if(_index_choice_pos>0)
                        _index_choice_pos--;;
                }
                else if(e.key.code == sf::Keyboard::Key::Down)
                {
                    if(_index_choice_pos<_choices_pos.size()-1)
                        _index_choice_pos++ ;
                }
                else if(e.key.code == sf::Keyboard::Key::Left)
                {
                    if(_index_choice_pos == 0 and _index_number_player_choice > 0){
                        _index_number_player_choice--;
                        
                    }
                    else if(_index_choice_pos == 1 and _index_difficulties_choice > 0){
                        _index_difficulties_choice--;
                        
                    }
                }
                else if(e.key.code == sf::Keyboard::Key::Right)
                {
                    if(_index_choice_pos == 0 and _index_number_player_choice < _vector_number_player_choice.size()-1){
                        _index_number_player_choice++;
                        
                    }
                    else if(_index_choice_pos == 1 and _index_difficulties_choice < _vector_difficulties_choice.size()-1){
                        _index_difficulties_choice++;
                        
                    }
                }
            }
        }
        _text_menu.setOrigin(sf::Vector2f((_text_menu.getGlobalBounds().width)/(2*_text_menu.getScale().x),(_text_menu.getGlobalBounds().height)/(2*_text_menu.getScale().y)));
        _text_difficulty.setOrigin(sf::Vector2f((_text_difficulty.getGlobalBounds().width)/(2*_text_difficulty.getScale().x),(_text_difficulty.getGlobalBounds().height)/(2*_text_difficulty.getScale().y)));
        _text_number_player.setOrigin(sf::Vector2f((_text_number_player.getGlobalBounds().width)/(2*_text_number_player.getScale().x),(_text_number_player.getGlobalBounds().height)/(2*_text_number_player.getScale().y)));
        _text_play.setOrigin(sf::Vector2f((_text_play.getGlobalBounds().width)/(2*_text_play.getScale().x),(_text_play.getGlobalBounds().height)/(2*_text_play.getScale().y)));
        _difficulty_choice.setOrigin(sf::Vector2f((_difficulty_choice.getGlobalBounds().width)/(2*_difficulty_choice.getScale().x),(_difficulty_choice.getGlobalBounds().height)/(2*_difficulty_choice.getScale().y)));
        _number_player_choice.setOrigin(sf::Vector2f((_number_player_choice.getGlobalBounds().width)/(2*_number_player_choice.getScale().x),(_number_player_choice.getGlobalBounds().height)/(2*_number_player_choice.getScale().y)));


        _choice_target.setPosition(sf::Vector2f( _choices_pos[_index_choice_pos]->getPosition().x+5,_choices_pos[_index_choice_pos]->getPosition().y+17));
        _text_menu.setPosition(width_window/2  , thickness_line + height_window / 20);
        _text_difficulty.setPosition(width_window/2  ,thickness_line + height_window / 1.75);
        _text_number_player.setPosition(width_window/2  ,thickness_line  + height_window / 3);
        _text_play.setPosition(width_window/2  ,thickness_line  + height_window / 1.2);
        _difficulty_choice.setPosition(width_window/2  ,thickness_line  + height_window / 1.5);
        _number_player_choice.setPosition(width_window/2  ,thickness_line  + height_window / 2.35);

        _difficulty_choice.setString(_vector_difficulties_choice[_index_difficulties_choice]);
        _number_player_choice.setString(_vector_number_player_choice[_index_number_player_choice]);

        window.clear(color_background);
        window.draw(line1);
        window.draw(line2);
        window.draw(line3);
        window.draw(line4);
        window.draw(_text_difficulty);
        window.draw(_text_menu);
        window.draw(_text_number_player);
        window.draw(_text_play);
        window.draw(_difficulty_choice);
        window.draw(_number_player_choice);
        window.draw(_choice_target);
        window.display();
    }

}

void interface::load_textures()
{
    blue_tile_texture.loadFromFile("../textures/single_blocks/Blue_colored.png");
    yellow_tile_texture.loadFromFile("../textures/single_blocks/Yellow_colored.png");
    orange_tile_texture.loadFromFile("../textures/single_blocks/Orange_colored.png");
    pink_tile_texture.loadFromFile("../textures/single_blocks/Pink_colored.png");
    all_tile_texture.loadFromFile("../textures/single_blocks/special.png");
    sky_blue_tile_texture.loadFromFile("../textures/single_blocks/Sky_blue_colored.png");
    purple_tile_texture.loadFromFile("../textures/single_blocks/Purple_colored.png");
    green_tile_texture.loadFromFile("../textures/single_blocks/Green_colored.png");
    white_tile_texture.loadFromFile("../textures/single_blocks/White_colored.png");

    blue_shade_tile_texture.loadFromFile("../textures/single_blocks/Blue_shade.png");
    yellow_shade_tile_texture.loadFromFile("../textures/single_blocks/Yellow_shade.png");
    orange_shade_tile_texture.loadFromFile("../textures/single_blocks/Orange_shade.png");
    pink_shade_tile_texture.loadFromFile("../textures/single_blocks/Pink_shade.png");
    red_shade_tile_texture.loadFromFile("../textures/single_blocks/Red_shade.png");
    sky_blue_shade_tile_texture.loadFromFile("../textures/single_blocks/Sky_blue_colored.png");
    purple_shade_tile_texture.loadFromFile("../textures/single_blocks/Purple_colored.png");
    green_shade_tile_texture.loadFromFile("../textures/single_blocks/Green_colored.png");
    white_shade_tile_texture.loadFromFile("../textures/single_blocks/White_colored.png");

    empty_tile_texture.loadFromFile("../textures/single_blocks/Ghost.png");
    target_texture.loadFromFile("../textures/single_blocks/Target.png");
}
