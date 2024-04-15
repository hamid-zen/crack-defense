#include "interface.h"

// #E882E8 color target
// #255,255,255 color case vide
//
interface::interface():_width(6), _difficulty(4), _textures() {
    _font.loadFromFile("../font/cyber_game.ttf");
    load_textures();
}

void interface::play(t_number ind)
{
    std::cout<<"whats the problem ! \n";
    arbitre _arbitre(ind);
    _arbitre.init();
    bool first_player(true);

    sf::Color color_background = sf::Color::Black;
    t_number thickness_line = 10;
    sf::Color color_line = sf::Color(255, 87, 217);
    t_number _width_cell = 64 ;
    t_number score_tab_width = 500 ;
    
    t_number play_tab_width = _arbitre.getJoueur().width() * _width_cell + 2 * thickness_line;
    t_number total_width = score_tab_width + play_tab_width;
    t_number total_height = _arbitre.getJoueur().height() * _width_cell + 2 * thickness_line ;
    auto angle(0);

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


    // On cree les sprite
    sf::Sprite s_tile, s_target(_textures.at("target"));

    while (window.isOpen() && !_arbitre.getJoueur().is_lost())
    {
        window.clear(color_background);
        // square.rotate(1);
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
                case sf::Keyboard::LShift:
                    action_utilisateur = t_action::change_direction;
                    first_player=false;
                    break;
                case sf::Keyboard::Up:
                    action_utilisateur = t_action::go_up;
                    break;
                case sf::Keyboard::Z:{
                    action_utilisateur = t_action::go_up;
                    first_player=false;
                    break;
                }

                case sf::Keyboard::Left:
                    action_utilisateur = t_action::go_left;
                    break;
                case sf::Keyboard::Q:{
                    action_utilisateur = t_action::go_left;
                    first_player=false;
                    break;
                }
                case sf::Keyboard::Right:
                    action_utilisateur = t_action::go_right;
                    break;
                case sf::Keyboard::D:{
                    action_utilisateur = t_action::go_right;
                    first_player=false;
                    break;
                }
                case sf::Keyboard::Down:
                    action_utilisateur = t_action::go_down;
                    break;
                case sf::Keyboard::S:{
                    action_utilisateur = t_action::go_down;
                    first_player=false;
                    break;
                }
                case sf::Keyboard::Space:
                    action_utilisateur = t_action::exchange;
                    break;
                case sf::Keyboard::LControl:{
                    action_utilisateur = t_action::exchange;
                    first_player=false;
                    break;
                }
                case sf::Keyboard::Enter:
                    action_utilisateur = t_action::accelerate;
                    break;
                case sf::Keyboard::Tab:{
                    action_utilisateur = t_action::accelerate;
                    first_player=false;
                    break;
                }
                case sf::Keyboard::M:
                    action_utilisateur = t_action::generate_malus;
                    break;
                
                case sf::Keyboard::Escape:{
                    window.close();
                    menu();
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

        _arbitre.update(action_utilisateur,first_player);

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
                    load_texture(s_tile, t_colors::garbage, true);
                    s_tile.setPosition(_width_cell * j + dx +thickness_line, _width_cell * i + dy +thickness_line - _arbitre.getJoueur().grid_dy());
                    window.draw(s_tile);
                }else{
                    auto color = _arbitre.getJoueur()(position(j, i));

                    load_texture(s_tile, color, false);

                    if(s_tile.getOrigin().x == 0)
                        s_tile.setOrigin(sf::Vector2f((s_tile.getGlobalBounds().width)/(2*s_tile.getScale().x),(s_tile.getGlobalBounds().height)/(2*s_tile.getScale().y)));

                    if (vec.size() == 0)
                        s_tile.setPosition(_width_cell * j + dx +thickness_line + _width_cell/2, _width_cell * i + dy +thickness_line - _arbitre.getJoueur().grid_dy() + _width_cell/2);
                    else
                    {
                        s_tile.setPosition(_width_cell * j + dx +thickness_line + _width_cell/2, _width_cell * i + dy +thickness_line - _arbitre.getJoueur().grid_dy() + _width_cell/2);
                        auto it(std::find(vec.begin(), vec.end(), position(j, i)));
                        if (it != vec.end())
                        {
                            s_tile.rotate(_arbitre.getDelays().angle);
                            s_tile.setScale(_arbitre.getDelays().scale, _arbitre.getDelays().scale);
                            //s_tile.setOrigin(0, 0);
                            vec.erase(it);
                        }
                    }

                    window.draw(s_tile);
                    s_tile.setRotation(0);
                    s_tile.setScale(1, 1);
                    //s_tile.setOrigin(0, 0);
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
            //   if(s_tile.getOrigin().x == 0)
            //             s_tile.setOrigin(sf::Vector2f((s_tile.getGlobalBounds().width)/(2*s_tile.getScale().x),(s_tile.getGlobalBounds().height)/(2*s_tile.getScale().y)));


            //TODO: deplacer vers la boucle
            // Affichage de la ligne qui monte
            for (std::size_t j(0); j < _arbitre.getJoueur().width(); j++)
            {
                // On get la couleur actuelle
                auto color = _arbitre.getJoueur()(position(j, _arbitre.getJoueur().height()));

                load_texture(s_tile, color, true);

                s_tile.setPosition(_width_cell * j+thickness_line + _width_cell/2, _width_cell * _arbitre.getJoueur().height() - _arbitre.getJoueur().grid_dy()+thickness_line+_width_cell/2); // adapter la vitesse par rapport a la taille de la fenetre
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
        angle+=5;
        window.display();
    }
}

void interface::menu(){

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
    std::vector<sf::Transformable *> _choices;
    t_number _index_choice_pos = 0; 

    //add choice_pos

    _choices.push_back(&_number_player_choice);
    _choices.push_back(&_difficulty_choice);
    _choices.push_back(&_text_play);

    //rectangle_choice
    sf::RectangleShape _choice_target(sf::Vector2f(_difficulty_choice.getGlobalBounds().width + 40,_difficulty_choice.getGlobalBounds().height + 20));
    _choice_target.setFillColor(sf::Color::Transparent);
    _choice_target.setOutlineThickness(5);
    _choice_target.setOutlineColor(sf::Color::Yellow);
    _choice_target.setOrigin(_choice_target.getGlobalBounds().width/2,_choice_target.getGlobalBounds().height/2);
    _choice_target.setPosition(sf::Vector2f( _choices[_index_choice_pos]->getPosition().x+5,_choices[_index_choice_pos]->getPosition().y+17));

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
    _vector_number_player_choice.push_back(sf::String("W-LAN"));

    


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
                    if(_index_choice_pos == _choices.size()-1){
                        if(_index_number_player_choice==1){
                            window.close();
                            play2(_index_difficulties_choice);
                        }

                       /* else if(_index_number_player_choice==2){
                            window.close();
                            menu_lan();
                        }*/

                        else {
                            window.close();
                            play(_index_difficulties_choice);
                        }
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
                    if(_index_choice_pos<_choices.size()-1)
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
                else if(e.key.code == sf::Keyboard::Key::H)
                {
                    window.close();
                    menu_regle();
                }
            }
        }
        _text_menu.setOrigin(sf::Vector2f((_text_menu.getGlobalBounds().width)/(2*_text_menu.getScale().x),(_text_menu.getGlobalBounds().height)/(2*_text_menu.getScale().y)));
        _text_difficulty.setOrigin(sf::Vector2f((_text_difficulty.getGlobalBounds().width)/(2*_text_difficulty.getScale().x),(_text_difficulty.getGlobalBounds().height)/(2*_text_difficulty.getScale().y)));
        _text_number_player.setOrigin(sf::Vector2f((_text_number_player.getGlobalBounds().width)/(2*_text_number_player.getScale().x),(_text_number_player.getGlobalBounds().height)/(2*_text_number_player.getScale().y)));
        _text_play.setOrigin(sf::Vector2f((_text_play.getGlobalBounds().width)/(2*_text_play.getScale().x),(_text_play.getGlobalBounds().height)/(2*_text_play.getScale().y)));
        _difficulty_choice.setOrigin(sf::Vector2f((_difficulty_choice.getGlobalBounds().width)/(2*_difficulty_choice.getScale().x),(_difficulty_choice.getGlobalBounds().height)/(2*_difficulty_choice.getScale().y)));
        _number_player_choice.setOrigin(sf::Vector2f((_number_player_choice.getGlobalBounds().width)/(2*_number_player_choice.getScale().x),(_number_player_choice.getGlobalBounds().height)/(2*_number_player_choice.getScale().y)));


        _choice_target.setPosition(sf::Vector2f( _choices[_index_choice_pos]->getPosition().x+5,_choices[_index_choice_pos]->getPosition().y+17));
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
void interface::menu_lan(){

    // TODO: creation des text avec une methode
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

    // texts
    sf::Text _text_title(sf::String("CONNECTION"), _font);
    sf::Text _text_type(sf::String("TYPE"), _font);
    sf::Text _type_choice(sf::String("SERVER"), _font);
    sf::Text _text_ip(sf::String("IP"), _font);
    sf::Text _ip(sf::String(sf::IpAddress::getLocalAddress().toString()), _font);
    sf::Text _text_port(sf::String("PORT"), _font);
    sf::Text _port(sf::String("8080"), _font);
    sf::Text _text_connect(sf::String("CONNECT"), _font);

    // text_scale
    _text_title.setScale(2, 2);
    _text_type.setScale(1.5, 1.5);
    _text_ip.setScale(1.5, 1.5);
    _text_port.setScale(1.5, 1.5);
    _text_connect.setScale(1.5, 1.5);

    // text_color
    _text_title.setFillColor(color_line);
    _text_type.setFillColor(color_line);
    _type_choice.setFillColor(color_line);
    _text_ip.setFillColor(color_line);
    _ip.setFillColor(sf::Color::White);
    _port.setFillColor(sf::Color::White);
    _text_port.setFillColor(color_line);
    _text_connect.setFillColor(color_line);

    // text_origin
    _text_title.setOrigin(sf::Vector2f((_text_title.getGlobalBounds().width)/(2*_text_title.getScale().x),(_text_title.getGlobalBounds().height)/(2*_text_title.getScale().y)));
    _text_type.setOrigin(sf::Vector2f((_text_type.getGlobalBounds().width)/(2*_text_type.getScale().x),(_text_type.getGlobalBounds().height)/(2*_text_type.getScale().y)));
    _type_choice.setOrigin(sf::Vector2f((_type_choice.getGlobalBounds().width)/(2*_type_choice.getScale().x),(_type_choice.getGlobalBounds().height)/(2*_type_choice.getScale().y)));
    _text_ip.setOrigin(sf::Vector2f((_text_ip.getGlobalBounds().width)/(2*_text_ip.getScale().x),(_text_ip.getGlobalBounds().height)/(2*_text_ip.getScale().y)));
    _ip.setOrigin(sf::Vector2f((_ip.getGlobalBounds().width)/(2*_ip.getScale().x),(_ip.getGlobalBounds().height)/(2*_ip.getScale().y)));
    _text_port.setOrigin(sf::Vector2f((_text_port.getGlobalBounds().width)/(2*_text_port.getScale().x),(_text_port.getGlobalBounds().height)/(2*_text_port.getScale().y)));
    _port.setOrigin(sf::Vector2f((_port.getGlobalBounds().width)/(2*_port.getScale().x),(_port.getGlobalBounds().height)/(2*_port.getScale().y)));
    _text_connect.setOrigin(sf::Vector2f((_text_connect.getGlobalBounds().width)/(2*_text_connect.getScale().x),(_text_connect.getGlobalBounds().height)/(2*_text_connect.getScale().y)));

    // text_position
    _text_title.setPosition(width_window/2, thickness_line + height_window / 20);
    _text_type.setPosition(width_window/2, thickness_line  + height_window / 4);
    _type_choice.setPosition(width_window/2, thickness_line  + height_window / 3);
    _text_ip.setPosition(width_window/2, thickness_line  + height_window / 2.25);
    _ip.setPosition(width_window/2, thickness_line  + height_window / 1.95);
    _text_port.setPosition(width_window/2, thickness_line  + height_window / 1.6);
    _port.setPosition(width_window/2, thickness_line  + height_window / 1.45);
    _text_connect.setPosition(width_window/2, thickness_line  + height_window / 1.2);

    // choices
    std::vector<sf::Transformable *> _choices;
    t_number _index_choice_pos = 0;
    _choices.push_back(&_type_choice);
    _choices.push_back(&_ip);
    _choices.push_back(&_port);
    _choices.push_back(&_text_connect);

    // type_choice
    std::vector<sf::String> _vector_type_choice;
    t_number _index_type_choice=0;
    _vector_type_choice.push_back(sf::String("SERVER"));
    _vector_type_choice.push_back(sf::String("CLIENT"));

    // rectangle_choice
    sf::RectangleShape _choice_target(sf::Vector2f(_type_choice.getGlobalBounds().width + 75, _type_choice.getGlobalBounds().height + 30));
    _choice_target.setFillColor(sf::Color::Transparent);
    _choice_target.setOutlineThickness(5);
    _choice_target.setOutlineColor(sf::Color::Yellow);
    _choice_target.setOrigin(_choice_target.getGlobalBounds().width/2,_choice_target.getGlobalBounds().height/2);
    _choice_target.setPosition(sf::Vector2f( _choices[_index_choice_pos]->getPosition().x+5,_choices[_index_choice_pos]->getPosition().y+17));

    sf::String _ip_input, _port_input;
    while(window.isOpen()){
        sf::Event e;

        while (window.pollEvent(e)){
            if (e.type == sf::Event::Closed)
                window.close();
            else if (e.type == sf::Event::KeyPressed)
            {
                if(e.key.code == sf::Keyboard::Key::Enter)
                {
                    // Connect the socket
                }
                else if(e.key.code == sf::Keyboard::Key::Up)
                {
                    if(_index_choice_pos>0)
                        _index_choice_pos--;
                }
                else if(e.key.code == sf::Keyboard::Key::Down)
                {
                    if(_index_choice_pos < _choices.size()-1)
                        _index_choice_pos++;
                }
                else if(e.key.code == sf::Keyboard::Key::Left)
                {
                    if(_index_choice_pos == 0 and _index_type_choice > 0)
                        _index_type_choice--;
                }
                else if(e.key.code == sf::Keyboard::Key::Right)
                {
                    if(_index_choice_pos == 0 and _index_type_choice < _vector_type_choice.size()-1 )
                        _index_type_choice++;
                }
                else if(e.key.code == sf::Keyboard::Key::BackSpace)
                {
                    // effacer l'input
                    if (_index_choice_pos == 1 && _ip_input.getSize() != 0)
                        _ip_input = _ip_input.substring(0, _ip_input.getSize()-1);
                    else if (_index_choice_pos == 2 && _port_input.getSize() != 0)
                        _ip_input = _port_input.substring(0, _port_input.getSize()-1);
                }
            }
            else if (e.type == sf::Event::TextEntered){
                if ((e.text.unicode <= 57 && e.text.unicode >= 48) || e.text.unicode == 46){
                    if (_index_choice_pos == 1)
                        _ip_input += e.text.unicode;
                    else if (_index_choice_pos == 2) // port
                        _port_input += e.text.unicode;
                }
            }
        }

        // updating target position
        _choice_target.setPosition(sf::Vector2f(_choices[_index_choice_pos]->getPosition().x+5, _choices[_index_choice_pos]->getPosition().y+17));

        // updating type_choice (server/client)
        _type_choice.setString(_vector_type_choice[_index_type_choice]);

        // on affiche l'ip local et le port default (8080) que si serveur est choisi
        if (_index_type_choice == 0){
            _ip.setString(sf::String(sf::IpAddress::getLocalAddress().toString()));
            _port.setString("8080");

            // On remet l'input a zero
            _ip_input = "";
            _port_input = "";
        }
        else {
            _ip.setString(_ip_input);
            _port.setString(_port_input);
        }


        window.clear(color_background);
        window.draw(_text_title);
        window.draw(_choice_target);
        window.draw(_text_type);
        window.draw(_type_choice);
        window.draw(_text_ip);
        window.draw(_ip);
        window.draw(_text_port);
        window.draw(_port);
        window.draw(_text_connect);
        window.draw(line1);
        window.draw(line2);
        window.draw(line3);
        window.draw(line4);
        window.display();
    }

}

void interface::load_textures()
{
    _textures["blue"].loadFromFile("../textures/single_blocks/Blue_colored.png");
    _textures["red"].loadFromFile("../textures/single_blocks/Red.png");
    _textures["yellow"].loadFromFile("../textures/single_blocks/Yellow_colored.png");
    _textures["orange"].loadFromFile("../textures/single_blocks/Orange_colored.png");
    _textures["pink"].loadFromFile("../textures/single_blocks/Pink_colored.png");
    _textures["all"].loadFromFile("../textures/single_blocks/special.png");
    _textures["sky_blue"].loadFromFile("../textures/single_blocks/Sky_blue_colored.png");
    _textures["purple"].loadFromFile("../textures/single_blocks/Purple_colored.png");
    _textures["green"].loadFromFile("../textures/single_blocks/Green_colored.png");
    _textures["white"].loadFromFile("../textures/single_blocks/White_colored.png");

    _textures["blue_shade"].loadFromFile("../textures/single_blocks/Blue_shade.png");
    _textures["yellow_shade"].loadFromFile("../textures/single_blocks/Yellow_shade.png");
    _textures["orange_shade"].loadFromFile("../textures/single_blocks/Orange_shade.png");
    _textures["pink_shade"].loadFromFile("../textures/single_blocks/Pink_shade.png");
    _textures["red_shade"].loadFromFile("../textures/single_blocks/Red_shade.png");
    _textures["sky_blue_shade"].loadFromFile("../textures/single_blocks/Sky_blue_shade.png");
    _textures["purple_shade"].loadFromFile("../textures/single_blocks/Purple_shade.png");
    _textures["green_shade"].loadFromFile("../textures/single_blocks/Green_shade.png");
    _textures["white_shade"].loadFromFile("../textures/single_blocks/White_shade.png");

    _textures["ghost"].loadFromFile("../textures/single_blocks/Ghost.png");
    _textures["target"].loadFromFile("../textures/single_blocks/Target.png");

    _textures["Crtl"].loadFromFile("../textures/keycaps/Crtl.png");
    _textures["Fleches_directionelles"].loadFromFile("../textures/keycaps/Fleches_directionelles.png");
    _textures["Shift"].loadFromFile("../textures/keycaps/Shift.png");
    _textures["Up"].loadFromFile("../textures/keycaps/Up.png");
    _textures["Down"].loadFromFile("../textures/keycaps/Down.png");
    _textures["Left"].loadFromFile("../textures/keycaps/Left.png");
    _textures["Space"].loadFromFile("../textures/keycaps/Space.png");
    _textures["Z"].loadFromFile("../textures/keycaps/Z.png");
    _textures["D"].loadFromFile("../textures/keycaps/D.png");
    _textures["Q"].loadFromFile("../textures/keycaps/Q.png");
    _textures["S"].loadFromFile("../textures/keycaps/S.png");
    _textures["Esc"].loadFromFile("../textures/keycaps/Esc.png");
    _textures["Right"].loadFromFile("../textures/keycaps/Right.png");
    _textures["Touches_directionelles"].loadFromFile("../textures/keycaps/Touches_directionelles.png");
}


void interface::load_texture(sf::Sprite &sprite, t_colors color, bool shade) const
{
    if (!shade) {
        switch (color) {
        case t_colors::blue:
            sprite.setTexture(_textures.at("blue"));
            break;
        case t_colors::pink:
            sprite.setTexture(_textures.at("pink"));
            break;
        case t_colors::yellow:
            sprite.setTexture(_textures.at("yellow"));
            break;
        case t_colors::orange:
            sprite.setTexture(_textures.at("orange"));
            break;
        case t_colors::sky_blue:
            sprite.setTexture(_textures.at("sky_blue"));
            break;
        case t_colors::purple:
            sprite.setTexture(_textures.at("purple"));
            break;
        case t_colors::green:
            sprite.setTexture(_textures.at("green"));
            break;
        case t_colors::white:
            sprite.setTexture(_textures.at("white"));
            break;
        case t_colors::empty_cell:
            sprite.setTexture(_textures.at("ghost"));
            break;
        case t_colors::garbage:
            sprite.setTexture(_textures.at("red"));
            break;
        default:
            break;
        }
    } else {
        switch (color) {
        case t_colors::blue:
            sprite.setTexture(_textures.at("blue_shade"));
            break;
        case t_colors::pink:
            sprite.setTexture(_textures.at("pink_shade"));
            break;
        case t_colors::yellow:
            sprite.setTexture(_textures.at("yellow_shade"));
            break;
        case t_colors::orange:
            sprite.setTexture(_textures.at("orange_shade"));
            break;
        case t_colors::sky_blue:
            sprite.setTexture(_textures.at("sky_blue_shade"));
            break;
        case t_colors::purple:
            sprite.setTexture(_textures.at("purple_shade"));
            break;
        case t_colors::green:
            sprite.setTexture(_textures.at("green_shade"));
            break;
        case t_colors::white:
            sprite.setTexture(_textures.at("white_shade"));
            break;
        default:
            break;
        }
    }

}


void interface::play2(t_number indDiff ){
    std::cout<<"sa rentre "<<std::endl;
}


void interface::menu_regle(){

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

    sf::Sprite _key_space;


    //text declaration
    sf::Text _text_joueur1(sf::String("JOUEUR 1"),_font);
    sf::Text _text_joueur2(sf::String("JOUEUR 2"),_font);
    sf::Text _text_menu(sf::String("RULES"),_font);
    sf::Text _text_explication(sf::String(""),_font);


    //text scale
    _text_menu.setScale(2,2);
    _text_joueur2.setScale(1.5,1.5);
    _text_joueur1.setScale(1.5,1.5);
    // _text_play.setScale(1.5,1.5);
    // _difficulty_choice.setScale(1.5,1.5);
    // _number_player_choice.setScale(1.5,1.5);
    

    //textorigin 
    _text_menu.setOrigin(sf::Vector2f((_text_menu.getGlobalBounds().width)/(2*_text_menu.getScale().x),(_text_menu.getGlobalBounds().height)/(2*_text_menu.getScale().y)));
    _text_joueur2.setOrigin(sf::Vector2f((_text_joueur2.getGlobalBounds().width)/(2*_text_joueur2.getScale().x),(_text_joueur2.getGlobalBounds().height)/(2*_text_joueur2.getScale().y)));
    _text_joueur1.setOrigin(sf::Vector2f((_text_joueur1.getGlobalBounds().width)/(2*_text_joueur1.getScale().x),(_text_joueur1.getGlobalBounds().height)/(2*_text_joueur1.getScale().y)));
    // _text_play.setOrigin(sf::Vector2f((_text_play.getGlobalBounds().width)/(2*_text_play.getScale().x),(_text_play.getGlobalBounds().height)/(2*_text_play.getScale().y)));
    // _difficulty_choice.setOrigin(sf::Vector2f((_difficulty_choice.getGlobalBounds().width)/(2*_difficulty_choice.getScale().x),(_difficulty_choice.getGlobalBounds().height)/(2*_difficulty_choice.getScale().y)));
    // _number_player_choice.setOrigin(sf::Vector2f((_number_player_choice.getGlobalBounds().width)/(2*_number_player_choice.getScale().x),(_number_player_choice.getGlobalBounds().height)/(2*_number_player_choice.getScale().y)));


    //textposition 
    _text_menu.setPosition(width_window/2  , thickness_line + height_window / 20);
    _text_joueur2.setPosition(width_window/2  ,thickness_line + height_window / 10);
    _text_joueur1.setPosition(width_window/2  ,thickness_line  + height_window / 17);
    //_text_play.setPosition(width_window/2  ,thickness_line  + height_window / 1.2);
    // _difficulty_choice.setPosition(width_window/2  ,thickness_line  + height_window / 1.5);
    // _number_player_choice.setPosition(width_window/2  ,thickness_line  + height_window / 2.35);


    //text_color
    _text_menu.setFillColor(color_line);
    _text_joueur2.setFillColor(color_line);
    _text_joueur1.setFillColor(color_line);

    // sprites
    sf::Sprite s_fleches, s_ctrl_1, s_ctrl_2, s_shift_1, s_shift_2, s_space_1, s_space_2, s_touches;
    s_fleches.setTexture(_textures.at("Fleches_directionelles"));
    s_ctrl_1.setTexture(_textures.at("Crtl"));
    s_shift_1.setTexture(_textures.at("Shift"));
    s_space_1.setTexture(_textures.at("Space"));
    s_touches.setTexture(_textures.at("Touches_directionelles"));
    s_ctrl_2.setTexture(_textures.at("Crtl"));
    s_shift_2.setTexture(_textures.at("Shift"));
    s_space_2.setTexture(_textures.at("Space"));

    //vector choice_pos
    std::vector<sf::Sprite *> _choices;

    //add choice_pos
    _choices.push_back(&s_fleches);
    _choices.push_back(&s_ctrl_1);
    _choices.push_back(&s_shift_1);
    _choices.push_back(&s_space_1);
    _choices.push_back(&s_touches);
    _choices.push_back(&s_ctrl_2);
    _choices.push_back(&s_shift_2);
    _choices.push_back(&s_space_2);

    //number_player_choice
    std::vector<sf::String> _controls;
    t_number _index_controls_choice=0;
    _controls.push_back(sf::String("Move j1"));
    _controls.push_back(sf::String("rotate j1"));
    _controls.push_back(sf::String("switch j1"));
    _controls.push_back(sf::String("accelerate j1"));
    _controls.push_back(sf::String("Move j2"));
    _controls.push_back(sf::String("rotate j2"));
    _controls.push_back(sf::String("switch j2"));
    _controls.push_back(sf::String("accelerate j2"));

    
    while(window.isOpen()){
        sf::Event e;
        
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                window.close();
            if (e.type == sf::Event::KeyPressed)
            {
                
                if(e.key.code == sf::Keyboard::Key::Escape)
                {
                    window.close();
                    menu();
                }
                else if(e.key.code == sf::Keyboard::Key::Up)
                {   
                    if(_index_controls_choice>3)
                        _index_controls_choice-=4;
                }
                else if(e.key.code == sf::Keyboard::Key::Down)
                {
                    if(_index_controls_choice<4)
                        _index_controls_choice+=4;
                }
                else if(e.key.code == sf::Keyboard::Key::Left)
                {
                    if(_index_controls_choice > 0)
                        _index_controls_choice--;
                }
                else if(e.key.code == sf::Keyboard::Key::Right)
                {
                    if(_index_controls_choice < _choices.size()-1)
                        _index_controls_choice++;
                }
            }
        }

        _text_menu.setOrigin(sf::Vector2f((_text_menu.getGlobalBounds().width)/(2*_text_menu.getScale().x),(_text_menu.getGlobalBounds().height)/(2*_text_menu.getScale().y)));
        _text_joueur2.setOrigin(sf::Vector2f((_text_joueur2.getGlobalBounds().width)/(2*_text_joueur2.getScale().x),(_text_joueur2.getGlobalBounds().height)/(2*_text_joueur2.getScale().y)));
        _text_joueur1.setOrigin(sf::Vector2f((_text_joueur1.getGlobalBounds().width)/(2*_text_joueur1.getScale().x),(_text_joueur1.getGlobalBounds().height)/(2*_text_joueur1.getScale().y)));
        //_text_play.setOrigin(sf::Vector2f((_text_play.getGlobalBounds().width)/(2*_text_play.getScale().x),(_text_play.getGlobalBounds().height)/(2*_text_play.getScale().y)));
        // _difficulty_choice.setOrigin(sf::Vector2f((_difficulty_choice.getGlobalBounds().width)/(2*_difficulty_choice.getScale().x),(_difficulty_choice.getGlobalBounds().height)/(2*_difficulty_choice.getScale().y)));
        // _number_player_choice.setOrigin(sf::Vector2f((_number_player_choice.getGlobalBounds().width)/(2*_number_player_choice.getScale().x),(_number_player_choice.getGlobalBounds().height)/(2*_number_player_choice.getScale().y)));


        // _choice_target.setPosition(sf::Vector2f( _choices[_index_choice_pos]->getPosition().x+5,_choices[_index_choice_pos]->getPosition().y+17));
        _text_menu.setPosition(width_window/2  , thickness_line + height_window / 20);
        _text_joueur2.setPosition(width_window/2  ,thickness_line + height_window / 2.25);
        _text_joueur1.setPosition(width_window/2  ,thickness_line  + height_window / 7);
        //_text_play.setPosition(width_window/2  ,thickness_line  + height_window / 1.2);
        // _difficulty_choice.setPosition(width_window/2  ,thickness_line  + height_window / 1.5);
        // _number_player_choice.setPosition(width_window/2  ,thickness_line  + height_window / 2.35);

        // _difficulty_choice.setString(_vector_difficulties_choice[_index_difficulties_choice]);
        // _number_player_choice.setString(_vector_number_player_choice[_index_number_player_choice]);

        window.clear(color_background);

        // sprite display joueur 1
        s_fleches.setPosition(thickness_line, s_fleches.getGlobalBounds().height + thickness_line + height_window / 17);
        window.draw(s_fleches);
        s_ctrl_1.setPosition(s_ctrl_1.getGlobalBounds().width*3 + thickness_line, s_ctrl_1.getGlobalBounds().height+s_fleches.getGlobalBounds().height + thickness_line + height_window / 17);
        window.draw(s_ctrl_1);
        s_shift_1.setPosition(s_shift_1.getGlobalBounds().width*4 + thickness_line, s_shift_1.getGlobalBounds().height+s_fleches.getGlobalBounds().height + thickness_line + height_window / 17);
        window.draw(s_shift_1);
        s_space_1.setPosition(s_space_1.getGlobalBounds().width*5 + thickness_line, s_space_1.getGlobalBounds().height+s_fleches.getGlobalBounds().height + thickness_line + height_window / 17);
        window.draw(s_space_1);

        // sprite display joueur 2
        s_touches.setPosition(thickness_line, s_touches.getGlobalBounds().height + thickness_line + height_window / 2.75);
        window.draw(s_touches);
        s_ctrl_2.setPosition(s_ctrl_2.getGlobalBounds().width*3 + thickness_line, s_touches.getGlobalBounds().height+s_ctrl_2.getGlobalBounds().height + thickness_line + height_window / 2.75);
        window.draw(s_ctrl_2);
        s_shift_2.setPosition(s_shift_2.getGlobalBounds().width*4 + thickness_line, s_touches.getGlobalBounds().height+s_shift_2.getGlobalBounds().height + thickness_line + height_window / 2.75);
        window.draw(s_shift_2);
        s_space_2.setPosition(s_space_2.getGlobalBounds().width*5 + thickness_line, s_touches.getGlobalBounds().height+s_space_2.getGlobalBounds().height + thickness_line + height_window / 2.75);
        window.draw(s_space_2);

        // line_choice
        sf::RectangleShape line_choice(sf::Vector2f(30, 5));
        sf::Sprite choosen_sprite = *_choices[_index_controls_choice];
        line_choice.setPosition(choosen_sprite.getPosition().x + (choosen_sprite.getTexture()->getSize().x * choosen_sprite.getScale().x - 30)/2, choosen_sprite.getPosition().y + choosen_sprite.getGlobalBounds().height + thickness_line);
        line_choice.setFillColor(sf::Color::Green);

        // Affichage de l'aide
        //TODO: changer les textures
        _text_explication.setString(_controls[_index_controls_choice]);
        _text_explication.setPosition((width_window - _text_explication.getLocalBounds().width)/2, thickness_line  + height_window / 1.2);

        window.draw(line1);
        window.draw(line2);
        window.draw(line3);
        window.draw(line4);
        window.draw(line_choice);
        window.draw(_text_joueur2);
        window.draw(_text_menu);
        window.draw(_text_joueur1);
        window.draw(_text_explication);
        window.display();
    }
}
