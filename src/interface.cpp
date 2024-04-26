#include "interface.h"


// #E882E8 color target
// #255,255,255 color case vide
//
interface::interface():_width(6), _difficulty(4), _textures(40, sf::Texture()) {
    _font.loadFromFile("../font/cyber_game.ttf");
    load_textures();
}

void interface::play(t_number ind,bool jeu_duo)
{
    sf::Sound _sound_xp;
    _sound_xp.setBuffer(_buffer_sound_xp);
    _sound_xp.setVolume(10);

    sf::Music _music ;
    _music.openFromFile("../msc/EWD.ogg");
    _music.setLoop(true);
    // _music.play();

    arbitre _arbitre(ind, jeu_duo);
    _arbitre.init();

    sf::Color color_background = sf::Color::Black;
    t_number thickness_line = 10;
    sf::Color color_line = sf::Color(255, 87, 217);
    t_number _width_cell = 64 ;
    t_number score_tab_width = 500 ;
    
    t_number play_tab_width = _arbitre.getJoueur().width() * _width_cell + 2 * thickness_line;
    t_number total_width = score_tab_width + play_tab_width;
    if(_arbitre.jeu_duo())
        total_width += play_tab_width;
    t_number total_height = _arbitre.getJoueur().height() * _width_cell + 2 * thickness_line ;
    auto angle(0);

    // On init la partie affichage du score
    sf::Text _text_score_1 = sf::Text("SCORE JOUEUR 1",_font,60);
    _text_score_1.setOrigin(sf::Vector2f((_text_score_1.getGlobalBounds().width)/(2*_text_score_1.getScale().x),(_text_score_1.getGlobalBounds().height)/(2*_text_score_1.getScale().y)));
    _text_score_1.setPosition(sf::Vector2f(play_tab_width+(score_tab_width/2), total_height/20));
    _text_score_1.setFillColor(color_line);

    sf::Text _number_score_1 = sf::Text(std::to_string(_arbitre.getJoueur().get_score()),_font,60);
    _number_score_1.setOrigin(sf::Vector2f((_number_score_1.getGlobalBounds().width)/(2*_number_score_1.getScale().x),(_number_score_1.getGlobalBounds().height)/(2*_number_score_1.getScale().y)));
    _number_score_1.setPosition(sf::Vector2f(play_tab_width+(score_tab_width/2), total_height/20 + 100));
    _number_score_1.setFillColor(color_line);

    sf::Text _text_score_2 = sf::Text("SCORE JOUEUR 2",_font,60);
    _text_score_2.setOrigin(sf::Vector2f((_text_score_2.getGlobalBounds().width)/(2*_text_score_2.getScale().x),(_text_score_2.getGlobalBounds().height)/(2*_text_score_2.getScale().y)));
    _text_score_2.setPosition(sf::Vector2f(play_tab_width+(score_tab_width/2), total_height/1.3));
    _text_score_2.setFillColor(color_line);

    sf::Text _number_score_2 = sf::Text(std::to_string(_arbitre.getJoueur().get_score()),_font,60);
    _number_score_2.setOrigin(sf::Vector2f((_number_score_2.getGlobalBounds().width)/(2*_number_score_2.getScale().x),(_number_score_2.getGlobalBounds().height)/(2*_number_score_2.getScale().y)));
    _number_score_2.setPosition(sf::Vector2f(play_tab_width+(score_tab_width/2), total_height/1.3 + 100));
    _number_score_2.setFillColor(color_line);


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
    sf::RectangleShape line6(sf::Vector2f(thickness_line, total_height ));
    line6.setFillColor(color_line);
    line6.setPosition(total_width-play_tab_width,0);


    // On cree les sprite
    sf::Sprite s_tile, s_target(_textures[t_textures_to_index(t_textures::Target)]), s_xp(_textures[t_textures_to_index(t_textures::Blue_XP)]);
    s_xp.setOrigin(sf::Vector2f((s_xp.getGlobalBounds().width)/(2*_number_score_2.getScale().x),(s_xp.getGlobalBounds().height)/(2*s_xp.getScale().y)));


    struct score_particle {
        position pos;
        sf::Vector2f direction ;
        float vitesse ;

        score_particle(position p,position sco,float vit):pos(p),vitesse(vit){
            direction = sf::Vector2f(sco.x()+20-pos.x(),sco.y()+20-pos.y());
        }
        
        
    
    };

    std::vector<score_particle *> particles ;

    while (window.isOpen() && !_arbitre.lost())
    {
        window.clear(color_background);
        // square.rotate(1);



        sf::Event e;
        t_action action_utilisateur1(t_action::nothing);
        t_action action_utilisateur2(t_action::nothing);

        while (window.pollEvent(e))
        {
            //TODO: remplacer par un appel a une methode meth(event, &first_player):t_action
            if (e.type == sf::Event::Closed){
                window.close();
                _music.stop();
            }
            if (e.type == sf::Event::KeyPressed)
            {
                if (e.key.code == sf::Keyboard::LShift)
                    action_utilisateur1 = t_action::change_direction;
                else if (e.key.code == sf::Keyboard::Z)
                    action_utilisateur1 = t_action::go_up;
                else if (e.key.code == sf::Keyboard::Q)
                    action_utilisateur1 = t_action::go_left;
                else if (e.key.code == sf::Keyboard::D)
                    action_utilisateur1 = t_action::go_right;
                else if (e.key.code == sf::Keyboard::S)
                    action_utilisateur1 = t_action::go_down;
                else if (e.key.code == sf::Keyboard::LControl)
                    action_utilisateur1 = t_action::exchange;
                else if (e.key.code == sf::Keyboard::Tab)
                    action_utilisateur1 = t_action::accelerate;
                else if (e.key.code == sf::Keyboard::M)
                    action_utilisateur1 = t_action::generate_malus;
                else if (e.key.code == sf::Keyboard::Escape){
                    _music.stop();
                    window.close();
                }
                else
                    action_utilisateur1 = t_action::nothing;

                if (e.key.code == sf::Keyboard::RShift)
                    action_utilisateur2 = t_action::change_direction;
                else if (e.key.code == sf::Keyboard::Up)
                    action_utilisateur2 = t_action::go_up;
                else if (e.key.code == sf::Keyboard::Left)
                    action_utilisateur2 = t_action::go_left;
                else if (e.key.code == sf::Keyboard::Right)
                    action_utilisateur2 = t_action::go_right;
                else if (e.key.code == sf::Keyboard::Down)
                    action_utilisateur2 = t_action::go_down;
                else if (e.key.code == sf::Keyboard::RControl)
                    action_utilisateur2 = t_action::exchange;
                else if (e.key.code == sf::Keyboard::Enter)
                    action_utilisateur2 = t_action::accelerate;
                else
                    action_utilisateur2 = t_action::nothing;
            }
        }


        // Traitement du score
        t_number _temp_score = _arbitre.getJoueur().get_score();
        _number_score_1.setString(sf::String(std::to_string(_temp_score)));
        _number_score_1.setOrigin(sf::Vector2f((_number_score_1.getGlobalBounds().width)/(2*_number_score_1.getScale().x),(_number_score_1.getGlobalBounds().height)/(2*_number_score_1.getScale().y)));

        if (_arbitre.jeu_duo()){
            t_number _temp_score = _arbitre.getJoueur2().get_score();
            _number_score_2.setString(sf::String(std::to_string(_temp_score)));
            _number_score_2.setOrigin(sf::Vector2f((_number_score_2.getGlobalBounds().width)/(2*_number_score_2.getScale().x),(_number_score_2.getGlobalBounds().height)/(2*_number_score_2.getScale().y)));
        }


        // On update l'etat du jeu
        _arbitre.update(action_utilisateur1);
        if(_arbitre.jeu_duo())
            _arbitre.update(action_utilisateur2, false);

        auto vec(_arbitre.getDelays().cells_align);

        // Affichage de la board
        for (std::size_t i(0); i < _arbitre.getJoueur().height(); i++)
        {
            for (std::size_t j(0); j < _arbitre.getJoueur().width(); j++)
            {
                t_number x(0);

                auto dx = _arbitre.getJoueur().cellDx(position(j, i));
                auto dy = _arbitre.getJoueur().cellDy(position(j, i));
                
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

                            if (s_tile.getScale().x <= 0.01)
                                particles.push_back(new score_particle(position(s_tile.getPosition().x,s_tile.getPosition().y),position(_number_score_1.getPosition().x, _number_score_1.getPosition().y),0.01));
                        }
                    }

                    window.draw(s_tile);
                    s_tile.setRotation(0);
                    s_tile.setScale(1, 1);
                    //s_tile.setOrigin(0, 0);
                

                // Dessin de la target
                if (_arbitre.getJoueur().getcell1target() == position(j, i) || _arbitre.getJoueur().getcell2target() == position(j, i))
                {
                    s_target.setPosition(_width_cell * j+thickness_line, _width_cell * i+thickness_line - _arbitre.getJoueur().grid_dy());

                    window.draw(s_target);
                }
            }
        }
        for (std::size_t j(0); j < _arbitre.getJoueur().width(); j++)
            {
                // On get la couleur actuelle
                auto color = _arbitre.getJoueur()(position(j, _arbitre.getJoueur().height()));

                load_texture(s_tile, color, true);

                s_tile.setPosition(_width_cell * j+thickness_line + _width_cell/2, _width_cell * _arbitre.getJoueur().height() - _arbitre.getJoueur().grid_dy()+thickness_line+_width_cell/2); // adapter la vitesse par rapport a la taille de la fenetre
                window.draw(s_tile);
            }

        // Affichage second joueur

        if (_arbitre.jeu_duo()){
            vec = _arbitre.getDelays(false).cells_align;
            for (std::size_t i(0); i < _arbitre.getJoueur2().height(); i++)
            {
                for (std::size_t j(0); j < _arbitre.getJoueur2().width(); j++)
                {
                    t_number x(0);

                    auto dx = _arbitre.getJoueur2().cellDx(position(j, i));
                    auto dy = _arbitre.getJoueur2().cellDy(position(j, i));
                    
                        auto color = _arbitre.getJoueur2()(position(j, i));

                        load_texture(s_tile, color, false);

                        if(s_tile.getOrigin().x == 0)
                            s_tile.setOrigin(sf::Vector2f((s_tile.getGlobalBounds().width)/(2*s_tile.getScale().x),(s_tile.getGlobalBounds().height)/(2*s_tile.getScale().y)));

                        if (vec.size() == 0)
                            s_tile.setPosition( play_tab_width+score_tab_width + _width_cell * j + dx +thickness_line + _width_cell/2, _width_cell * i + dy +thickness_line - _arbitre.getJoueur2().grid_dy() + _width_cell/2);
                        else
                        {
                            s_tile.setPosition(play_tab_width+score_tab_width +  _width_cell * j + dx +thickness_line + _width_cell/2, _width_cell * i + dy +thickness_line - _arbitre.getJoueur2().grid_dy() + _width_cell/2);
                            auto it(std::find(vec.begin(), vec.end(), position(j, i)));
                            if (it != vec.end())
                            {
                                s_tile.rotate(_arbitre.getDelays(false).angle);
                                s_tile.setScale(_arbitre.getDelays(false).scale, _arbitre.getDelays(false).scale);
                                //s_tile.setOrigin(0, 0);
                                vec.erase(it);

                            }
                        }

                        window.draw(s_tile);
                        s_tile.setRotation(0);
                        s_tile.setScale(1, 1);
                        //s_tile.setOrigin(0, 0);
                    

                    // Dessin de la target
                    if (_arbitre.getJoueur2().getcell1target() == position(j, i) || _arbitre.getJoueur2().getcell2target() == position(j, i))
                    {

                        s_target.setPosition(play_tab_width+score_tab_width + 64 * j+thickness_line, 64 * i+thickness_line - _arbitre.getJoueur2 ().grid_dy());
                        window.draw(s_target);
                    }
                }
            }

            // Affichage de la ligne qui monte joueur 2
            for (std::size_t j(0); j < _arbitre.getJoueur2().width(); j++)
            {
                // On get la couleur actuelle
                auto color = _arbitre.getJoueur2()(position(j, _arbitre.getJoueur2().height()));

                load_texture(s_tile, color, true);

                s_tile.setPosition(play_tab_width+score_tab_width + _width_cell * j+thickness_line + _width_cell/2, _width_cell * _arbitre.getJoueur2().height() - _arbitre.getJoueur2().grid_dy()+thickness_line+_width_cell/2); // adapter la vitesse par rapport a la taille de la fenetre
                window.draw(s_tile);
            }
        }

        for(auto it(particles.begin()); it != particles.end(); it++){
            s_xp.rotate(18);
            s_xp.setPosition((*it)->pos.x(),(*it)->pos.y());
            if (_arbitre.getFrame() % 3 == 0)
                s_xp.setTexture(_textures[t_textures_to_index(t_textures::Blue_XP)]);
            else if (_arbitre.getFrame() % 3 == 1)
                s_xp.setTexture(_textures[t_textures_to_index(t_textures::Yellow_XP)]);
            else
                s_xp.setTexture(_textures[t_textures_to_index(t_textures::Pink_XP)]);
            if((*it)->pos.x() <= _number_score_1.getPosition().x || (*it)->pos.y() >= _number_score_1.getPosition().y){
                (*it)->pos.sety((*it)->pos.y()+(*it)->direction.y * (*it)->vitesse);
                std::cout<< "original: " << (*it)->pos.x()<<std::endl;
                std::cout << "v2: " << ((*it)->pos.x()+(*it)->direction.x * (*it)->vitesse) << "\n";
                (*it)->pos.setx((*it)->pos.x()+(*it)->direction.x * (*it)->vitesse);
                (*it)->vitesse += 0.001;
                std::cout<<(*it)->pos.x() <<"//"<<(*it)->direction.x<<"//"<<(*it)->vitesse<< std::endl;
            }
            else {
                particles.erase(it);
                it--;
                _arbitre.getDelays().score++;
                _sound_xp.play();
            }
            
            window.draw(s_xp);
        }

        // On display
        window.draw(_number_score_1);
        window.draw(_text_score_1);
        window.draw(line1);
        window.draw(line2);
        window.draw(line3);
        window.draw(line4);
        window.draw(line5);
        if(_arbitre.jeu_duo()){
            window.draw(_number_score_2);
            window.draw(_text_score_2);
            window.draw(line6);
        }
        angle+=5;
        window.display();
    }

    sf::Sound _sound_loose ;
    _sound_loose.setBuffer(_buffer_sound_loose);
    _sound_loose.setVolume(10);
    _sound_loose.play();
    window.close();
    menu();
}

void interface::menu(){

    sf::Sound _sound ;
    _sound.setBuffer(_buffer_sound_choice_move);
    _sound.setVolume(5);
    _sound.setAttenuation(0.5);

    sf::Sound _sound_play ; 
    _sound_play.setBuffer(_buffer_sound_play);
    _sound_play.setVolume(5);

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
    sf::Text _text_difficulty(sf::String("DIFFICULTY"), _font);
    sf::Text _text_help(sf::String("press H For Help"), _font);
    sf::Text _text_number_player(sf::String("NUMBER OF PLAYER"), _font);
    sf::Text _text_menu(sf::String("MENU"), _font);
    sf::Text _difficulty_choice(sf::String("EASY"), _font);
    sf::Text _number_player_choice(sf::String("SOLO"), _font);
    sf::Text _text_play(sf::String("PLAY"), _font);

    //text scale
    _text_menu.setScale(2, 2);
    _text_difficulty.setScale(1.5, 1.5);
    _text_help.setScale(0.75, 0.75);
    _text_number_player.setScale(1.5, 1.5);
    _text_play.setScale(1.5, 1.5);
    _difficulty_choice.setScale(1.5, 1.5);
    _number_player_choice.setScale(1.5, 1.5);
    
    //textorigin 
    _text_menu.setOrigin(sf::Vector2f((_text_menu.getGlobalBounds().width)/(2*_text_menu.getScale().x),(_text_menu.getGlobalBounds().height)/(2*_text_menu.getScale().y)));
    _text_help.setOrigin(sf::Vector2f((_text_help.getGlobalBounds().width)/(2*_text_help.getScale().x),(_text_help.getGlobalBounds().height)/(2*_text_help.getScale().y)));
    _text_difficulty.setOrigin(sf::Vector2f((_text_difficulty.getGlobalBounds().width)/(2*_text_difficulty.getScale().x),(_text_difficulty.getGlobalBounds().height)/(2*_text_difficulty.getScale().y)));
    _text_number_player.setOrigin(sf::Vector2f((_text_number_player.getGlobalBounds().width)/(2*_text_number_player.getScale().x),(_text_number_player.getGlobalBounds().height)/(2*_text_number_player.getScale().y)));
    _text_play.setOrigin(sf::Vector2f((_text_play.getGlobalBounds().width)/(2*_text_play.getScale().x),(_text_play.getGlobalBounds().height)/(2*_text_play.getScale().y)));
    _difficulty_choice.setOrigin(sf::Vector2f((_difficulty_choice.getGlobalBounds().width)/(2*_difficulty_choice.getScale().x),(_difficulty_choice.getGlobalBounds().height)/(2*_difficulty_choice.getScale().y)));
    _number_player_choice.setOrigin(sf::Vector2f((_number_player_choice.getGlobalBounds().width)/(2*_number_player_choice.getScale().x),(_number_player_choice.getGlobalBounds().height)/(2*_number_player_choice.getScale().y)));

    //textposition 
    _text_menu.setPosition(width_window/2  , thickness_line + height_window / 20);
    _text_help.setPosition(width_window/2  , thickness_line + height_window / 1.05);
    _text_difficulty.setPosition(width_window/2  ,thickness_line + height_window / 1.75);
    _text_number_player.setPosition(width_window/2  ,thickness_line  + height_window / 3);
    _text_play.setPosition(width_window/2  ,thickness_line  + height_window / 1.2);
    _difficulty_choice.setPosition(width_window/2  ,thickness_line  + height_window / 1.5);
    _number_player_choice.setPosition(width_window/2  ,thickness_line  + height_window / 2.35);


    //text_color
    _text_menu.setFillColor(color_line);
    _text_help.setFillColor(sf::Color::Yellow);
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
                if(_sound.getStatus()!=sf::Music::Status::Playing){
                    _sound.play();
                    //_sound.stop();
                }
                
                if (e.key.code == sf::Keyboard::Key::Enter)
                {
                    if(_index_choice_pos == _choices.size()-1){
                        if(_index_number_player_choice==1){
                            window.close();
                            _sound.stop();
                            _sound_play.play();
                            play(_index_difficulties_choice,true);
                            
                        }

                         else if(_index_number_player_choice==2){
                            window.close();
                            menu_lan();
                        }

                        else {
                            window.close();
                            _sound.stop();
                            _sound_play.play();
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
        window.draw(_text_help);
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
void interface::game_over_screen()
{
    // TODO: adapter dans le cas ou jeu a deux joueur
    t_number thickness_line = 10;
    t_number width_window = _width * 64 + 2 * thickness_line;
    t_number height_window = 12 * 64 + 2 * thickness_line;
    sf::Color color_background = sf::Color::Black;
    sf::Color color_line = sf::Color(255, 87, 217);

    // window
    sf::RenderWindow window(sf::VideoMode(width_window, height_window), "Habibi");
    window.setFramerateLimit(30); // Pour set le framerate

    // border
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

    // game over sprite
    sf::Sprite s_game_over;
    s_game_over.setTexture(_textures[t_textures_to_index(t_textures::game_over)]);
    s_game_over.setOrigin(s_game_over.getGlobalBounds().width/2, s_game_over.getGlobalBounds().height/2);
    s_game_over.setPosition(width_window/2, thickness_line + height_window / 4);

    // texts
    sf::Text _text_main_menu(sf::String("MENU"), _font);
    sf::Text _text_exit(sf::String("EXIT"), _font);

    // text_scale
    _text_main_menu.setScale(1.5, 1.5);
    _text_exit.setScale(1.5, 1.5);

    // text_color
    _text_main_menu.setFillColor(color_line);
    _text_exit.setFillColor(color_line);

    // text_origin
    _text_main_menu.setOrigin(sf::Vector2f((_text_main_menu.getGlobalBounds().width)/(2*_text_main_menu.getScale().x),(_text_main_menu.getGlobalBounds().height)/(2*_text_main_menu.getScale().y)));
    _text_exit.setOrigin(sf::Vector2f((_text_exit.getGlobalBounds().width)/(2*_text_exit.getScale().x),(_text_exit.getGlobalBounds().height)/(2*_text_exit.getScale().y)));

    // text_position
    _text_main_menu.setPosition(width_window/2, thickness_line + height_window / 1.75);
    _text_exit.setPosition(width_window/2, thickness_line  + height_window / 1.5);

    // choices
    std::vector<sf::Transformable *> _choices;
    t_number _index_choice_pos = 0;
    _choices.push_back(&_text_main_menu);
    _choices.push_back(&_text_exit);

    // rectangle_choice
    sf::RectangleShape _choice_target(sf::Vector2f(_text_main_menu.getGlobalBounds().width + 75, _text_main_menu.getGlobalBounds().height + 30));
    _choice_target.setFillColor(sf::Color::Transparent);
    _choice_target.setOutlineThickness(5);
    _choice_target.setOutlineColor(sf::Color::Yellow);
    _choice_target.setOrigin(_choice_target.getGlobalBounds().width/2,_choice_target.getGlobalBounds().height/2);
    _choice_target.setPosition(sf::Vector2f( _choices[_index_choice_pos]->getPosition().x+5,_choices[_index_choice_pos]->getPosition().y+17));

    while(window.isOpen()){

        window.clear(color_background);

        sf::Event e;

        while (window.pollEvent(e)){
            if (e.type == sf::Event::Closed)
                window.close();
            else if (e.type == sf::Event::KeyPressed)
            {
                if(e.key.code == sf::Keyboard::Key::Enter)
                {
                    if(_index_choice_pos == 0){ // main menu
                        window.close();
                        menu();
                    } else if (_index_choice_pos == 1) {
                        window.close();
                    }
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
            }
        }

        // updating target position and size
        _choice_target.setPosition(sf::Vector2f(_choices[_index_choice_pos]->getPosition().x+5, _choices[_index_choice_pos]->getPosition().y+17));

        window.draw(s_game_over);
        window.draw(_text_main_menu);
        window.draw(_text_exit);
        window.draw(_choice_target);
        window.draw(line1);
        window.draw(line2);
        window.draw(line3);
        window.draw(line4);
        window.display();
    }
}
void interface::pause_screen()
{
    // TODO: adapter dans le cas ou jeu a deux joueur
    t_number thickness_line = 10;
    t_number width_window = _width * 64 + 2 * thickness_line;
    t_number height_window = 12 * 64 + 2 * thickness_line;
    sf::Color color_background = sf::Color::Black;
    sf::Color color_line = sf::Color(255, 87, 217);
    
    // window
    sf::RenderWindow window(sf::VideoMode(width_window, height_window), "Habibi");
    window.setFramerateLimit(30); // Pour set le framerate
    
    // border
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
    
    // game over sprite
    sf::Sprite s_game_over;
    s_game_over.setTexture(_textures[t_textures_to_index(t_textures::pause)]);
    s_game_over.setOrigin(s_game_over.getGlobalBounds().width/2, s_game_over.getGlobalBounds().height/2);
    s_game_over.setPosition(width_window/2, thickness_line + height_window / 4);
    
    // texts
    sf::Text _text_resume(sf::String("RESUME"), _font);
    sf::Text _text_main_menu(sf::String("MENU"), _font);
    sf::Text _text_exit(sf::String("EXIT"), _font);
    
    // text_scale
    _text_resume.setScale(1.5, 1.5);
    _text_main_menu.setScale(1.5, 1.5);
    _text_exit.setScale(1.5, 1.5);
    
    // text_color
    _text_resume.setFillColor(color_line);
    _text_main_menu.setFillColor(color_line);
    _text_exit.setFillColor(color_line);
    
    // text_origin
    _text_resume.setOrigin(sf::Vector2f((_text_resume.getGlobalBounds().width)/(2*_text_resume.getScale().x),(_text_resume.getGlobalBounds().height)/(2*_text_resume.getScale().y)));
    _text_main_menu.setOrigin(sf::Vector2f((_text_main_menu.getGlobalBounds().width)/(2*_text_main_menu.getScale().x),(_text_main_menu.getGlobalBounds().height)/(2*_text_main_menu.getScale().y)));
    _text_exit.setOrigin(sf::Vector2f((_text_exit.getGlobalBounds().width)/(2*_text_exit.getScale().x),(_text_exit.getGlobalBounds().height)/(2*_text_exit.getScale().y)));
    
    // text_position
    _text_resume.setPosition(width_window/2, thickness_line + height_window / 2.1);
    _text_main_menu.setPosition(width_window/2, thickness_line + height_window / 1.75);
    _text_exit.setPosition(width_window/2, thickness_line  + height_window / 1.5);
    
    // choices
    std::vector<sf::Transformable *> _choices;
    t_number _index_choice_pos = 0;
    _choices.push_back(&_text_resume);
    _choices.push_back(&_text_main_menu);
    _choices.push_back(&_text_exit);
    
    // rectangle_choice
    sf::RectangleShape _choice_target(sf::Vector2f(_text_main_menu.getGlobalBounds().width + 75, _text_main_menu.getGlobalBounds().height + 30));
    _choice_target.setFillColor(sf::Color::Transparent);
    _choice_target.setOutlineThickness(5);
    _choice_target.setOutlineColor(sf::Color::Yellow);
    _choice_target.setOrigin(_choice_target.getGlobalBounds().width/2,_choice_target.getGlobalBounds().height/2);
    _choice_target.setPosition(sf::Vector2f( _choices[_index_choice_pos]->getPosition().x+5,_choices[_index_choice_pos]->getPosition().y+17));
    
    while(window.isOpen()){
        
        window.clear(color_background);
        
        sf::Event e;
        
        while (window.pollEvent(e)){
            if (e.type == sf::Event::Closed)
                window.close();
            else if (e.type == sf::Event::KeyPressed)
            {
                if(e.key.code == sf::Keyboard::Key::Enter)
                {
                    if(_index_choice_pos == 0){ // resume
                        window.close();
                        menu();
                    } else if (_index_choice_pos == 1) { // main_menu
                        window.close();
                        menu();
                    } else { // exit
                        window.close();
                    }
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
            }
        }
        
        // updating target position and size
        _choice_target.setPosition(sf::Vector2f(_choices[_index_choice_pos]->getPosition().x+5, _choices[_index_choice_pos]->getPosition().y+17));
        
        window.draw(s_game_over);
        window.draw(_text_resume);
        window.draw(_text_main_menu);
        window.draw(_text_exit);
        window.draw(_choice_target);
        window.draw(line1);
        window.draw(line2);
        window.draw(line3);
        window.draw(line4);
        window.display();
    }
}

void interface::load_textures()
{
    _textures[t_textures_to_index(t_textures::Blue)].loadFromFile("../textures/single_blocks/Blue_colored.png");
    _textures[t_textures_to_index(t_textures::Red)].loadFromFile("../textures/single_blocks/Red.png");
    _textures[t_textures_to_index(t_textures::Yellow)].loadFromFile("../textures/single_blocks/Yellow_colored.png");
    _textures[t_textures_to_index(t_textures::Orange)].loadFromFile("../textures/single_blocks/Orange_colored.png");
    _textures[t_textures_to_index(t_textures::Pink)].loadFromFile("../textures/single_blocks/Pink_colored.png");
    _textures[t_textures_to_index(t_textures::All)].loadFromFile("../textures/single_blocks/special.png");
    _textures[t_textures_to_index(t_textures::SkyBlue)].loadFromFile("../textures/single_blocks/Sky_blue_colored.png");
    _textures[t_textures_to_index(t_textures::Purple)].loadFromFile("../textures/single_blocks/Purple_colored.png");
    _textures[t_textures_to_index(t_textures::Green)].loadFromFile("../textures/single_blocks/Green_colored.png");
    _textures[t_textures_to_index(t_textures::White)].loadFromFile("../textures/single_blocks/White_colored.png");

    _textures[t_textures_to_index(t_textures::BlueShade)].loadFromFile("../textures/single_blocks/Blue_shade.png");
    _textures[t_textures_to_index(t_textures::YellowShade)].loadFromFile("../textures/single_blocks/Yellow_shade.png");
    _textures[t_textures_to_index(t_textures::OrangeShade)].loadFromFile("../textures/single_blocks/Orange_shade.png");
    _textures[t_textures_to_index(t_textures::PinkShade)].loadFromFile("../textures/single_blocks/Pink_shade.png");
    _textures[t_textures_to_index(t_textures::RedShade)].loadFromFile("../textures/single_blocks/Red_shade.png");
    _textures[t_textures_to_index(t_textures::SkyBlueShade)].loadFromFile("../textures/single_blocks/Sky_blue_shade.png");
    _textures[t_textures_to_index(t_textures::PurpleShade)].loadFromFile("../textures/single_blocks/Purple_shade.png");
    _textures[t_textures_to_index(t_textures::GreenShade)].loadFromFile("../textures/single_blocks/Green_shade.png");
    _textures[t_textures_to_index(t_textures::WhiteShade)].loadFromFile("../textures/single_blocks/White_shade.png");

    _textures[t_textures_to_index(t_textures::Ghost)].loadFromFile("../textures/single_blocks/Ghost.png");
    _textures[t_textures_to_index(t_textures::Target)].loadFromFile("../textures/single_blocks/Target.png");

    _textures[t_textures_to_index(t_textures::Ctrl)].loadFromFile("../textures/keycaps/Crtl.png");
    _textures[t_textures_to_index(t_textures::DirectionalArrows)].loadFromFile("../textures/keycaps/Fleches_directionelles.png");
    _textures[t_textures_to_index(t_textures::Shift)].loadFromFile("../textures/keycaps/Shift.png");
    _textures[t_textures_to_index(t_textures::Tab)].loadFromFile("../textures/keycaps/Tab.png");
    _textures[t_textures_to_index(t_textures::Enter)].loadFromFile("../textures/keycaps/Enter.png");
    _textures[t_textures_to_index(t_textures::Esc)].loadFromFile("../textures/keycaps/Esc.png");
    _textures[t_textures_to_index(t_textures::DirectionalKeys)].loadFromFile("../textures/keycaps/Touches_directionelles.png");

    _textures[t_textures_to_index(t_textures::Blue_XP)].loadFromFile("../textures/xp_chips/Blue_XP.png");
    _textures[t_textures_to_index(t_textures::Yellow_XP)].loadFromFile("../textures/xp_chips/Yellow_XP.png");
    _textures[t_textures_to_index(t_textures::Pink_XP)].loadFromFile("../textures/xp_chips/Pink_XP.png");

    _textures[t_textures_to_index(t_textures::loading_0)].loadFromFile("../textures/loading_circle/loading_0.png");
    _textures[t_textures_to_index(t_textures::loading_1)].loadFromFile("../textures/loading_circle/loading_1.png");
    _textures[t_textures_to_index(t_textures::loading_2)].loadFromFile("../textures/loading_circle/loading_2.png");
    _textures[t_textures_to_index(t_textures::loading_3)].loadFromFile("../textures/loading_circle/loading_3.png");
    _textures[t_textures_to_index(t_textures::loading_4)].loadFromFile("../textures/loading_circle/loading_4.png");

    _textures[t_textures_to_index(t_textures::game_over)].loadFromFile("../textures/game_over.png");
    _textures[t_textures_to_index(t_textures::pause)].loadFromFile("../textures/pause.png");
    _textures[t_textures_to_index(t_textures::check_mark)].loadFromFile("../textures/check_mark.png");

    _buffer_sound_choice_move.loadFromFile("../sound/Menu_Sounds_Hover.wav");
    _buffer_sound_loose.loadFromFile("../sound/Menu_Sounds_Save_Savefile.wav");
    _buffer_sound_play.loadFromFile("../sound/Menu_Sounds_Load_Savefile.wav");
    _buffer_sound_xp.loadFromFile("../sound/xp.wav");
}

void interface::menu_lan(){

    sf::Sound _sound_move ;
    _sound_move.setBuffer(_buffer_sound_choice_move);
    _sound_move.setVolume(5);


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
                if(_sound_move.getStatus()!=sf::Music::Status::Playing)
                    _sound_move.play();
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
                else if(e.key.code == sf::Keyboard::Key::Escape)
                {
                    window.close();
                    menu();
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

void interface::load_texture(sf::Sprite &sprite, t_colors color, bool shade) const
{
    if (!shade) {
        switch (color) {
        case t_colors::blue:
            sprite.setTexture(_textures[t_textures_to_index(t_textures::Blue)]);
            break;
        case t_colors::pink:
            sprite.setTexture(_textures[t_textures_to_index(t_textures::Pink)]);
            break;
        case t_colors::yellow:
            sprite.setTexture(_textures[t_textures_to_index(t_textures::Yellow)]);
            break;
        case t_colors::orange:
            sprite.setTexture(_textures[t_textures_to_index(t_textures::Orange)]);
            break;
        case t_colors::sky_blue:
            sprite.setTexture(_textures[t_textures_to_index(t_textures::SkyBlue)]);
            break;
        case t_colors::purple:
            sprite.setTexture(_textures[t_textures_to_index(t_textures::Purple)]);
            break;
        case t_colors::green:
            sprite.setTexture(_textures[t_textures_to_index(t_textures::Green)]);
            break;
        case t_colors::white:
            sprite.setTexture(_textures[t_textures_to_index(t_textures::White)]);
            break;
        case t_colors::empty_cell:
            sprite.setTexture(_textures[t_textures_to_index(t_textures::Ghost)]);
            break;
        case t_colors::garbage:
            sprite.setTexture(_textures[t_textures_to_index(t_textures::Red)]);
            break;
        default:
            break;
        }
    } else {
        switch (color) {
        case t_colors::blue:
            sprite.setTexture(_textures[t_textures_to_index(t_textures::BlueShade)]);
            break;
        case t_colors::pink:
            sprite.setTexture(_textures[t_textures_to_index(t_textures::PinkShade)]);
            break;
        case t_colors::yellow:
            sprite.setTexture(_textures[t_textures_to_index(t_textures::YellowShade)]);
            break;
        case t_colors::orange:
            sprite.setTexture(_textures[t_textures_to_index(t_textures::OrangeShade)]);
            break;
        case t_colors::sky_blue:
            sprite.setTexture(_textures[t_textures_to_index(t_textures::SkyBlueShade)]);
            break;
        case t_colors::purple:
            sprite.setTexture(_textures[t_textures_to_index(t_textures::PurpleShade)]);
            break;
        case t_colors::green:
            sprite.setTexture(_textures[t_textures_to_index(t_textures::GreenShade)]);
            break;
        case t_colors::white:
            sprite.setTexture(_textures[t_textures_to_index(t_textures::WhiteShade)]);
            break;
        default:
            break;
        }
    }
}


void interface::menu_regle(){

    sf::Sound _sound_move ;
    _sound_move.setBuffer(_buffer_sound_choice_move);
    _sound_move.setVolume(5);

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
    

    //textorigin 
    _text_menu.setOrigin(sf::Vector2f((_text_menu.getGlobalBounds().width)/(2*_text_menu.getScale().x),(_text_menu.getGlobalBounds().height)/(2*_text_menu.getScale().y)));
    _text_joueur2.setOrigin(sf::Vector2f((_text_joueur2.getGlobalBounds().width)/(2*_text_joueur2.getScale().x),(_text_joueur2.getGlobalBounds().height)/(2*_text_joueur2.getScale().y)));
    _text_joueur1.setOrigin(sf::Vector2f((_text_joueur1.getGlobalBounds().width)/(2*_text_joueur1.getScale().x),(_text_joueur1.getGlobalBounds().height)/(2*_text_joueur1.getScale().y)));


    //textposition 
    _text_menu.setPosition(width_window/2  , thickness_line + height_window / 20);
    _text_joueur2.setPosition(width_window/2  ,thickness_line + height_window / 10);
    _text_joueur1.setPosition(width_window/2  ,thickness_line  + height_window / 17);


    //text_color
    _text_menu.setFillColor(color_line);
    _text_joueur2.setFillColor(color_line);
    _text_joueur1.setFillColor(color_line);

    // sprites
    sf::Sprite s_fleches, s_ctrl_1, s_ctrl_2, s_shift_1, s_shift_2, s_enter, s_tab, s_touches;
    s_fleches.setTexture(_textures[t_textures_to_index(t_textures::DirectionalArrows)]);
    s_ctrl_1.setTexture(_textures[t_textures_to_index(t_textures::Ctrl)]);
    s_shift_1.setTexture(_textures[t_textures_to_index(t_textures::Shift)]);
    s_enter.setTexture(_textures[t_textures_to_index(t_textures::Enter)]);
    s_touches.setTexture(_textures[t_textures_to_index(t_textures::DirectionalKeys)]);
    s_ctrl_2.setTexture(_textures[t_textures_to_index(t_textures::Ctrl)]);
    s_shift_2.setTexture(_textures[t_textures_to_index(t_textures::Shift)]);
    s_tab.setTexture(_textures[t_textures_to_index(t_textures::Tab)]);

    //vector choice_pos
    std::vector<sf::Sprite *> _choices;

    //add choice_pos
    _choices.push_back(&s_fleches);
    _choices.push_back(&s_ctrl_2);
    _choices.push_back(&s_shift_2);
    _choices.push_back(&s_tab);
    _choices.push_back(&s_touches);
    _choices.push_back(&s_ctrl_1);
    _choices.push_back(&s_shift_1);
    _choices.push_back(&s_enter);

    //number_player_choice
    std::vector<sf::String> _controls;
    t_number _index_controls_choice=0;
    _controls.push_back(sf::String("Move j2"));
    _controls.push_back(sf::String("rotate j2"));
    _controls.push_back(sf::String("switch j2"));
    _controls.push_back(sf::String("accelerate j2"));
    _controls.push_back(sf::String("Move j1"));
    _controls.push_back(sf::String("rotate j1"));
    _controls.push_back(sf::String("switch j1"));
    _controls.push_back(sf::String("accelerate j1"));

    
    while(window.isOpen()){
        sf::Event e;
        
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                window.close();
            if (e.type == sf::Event::KeyPressed)
            {
                if(_sound_move.getStatus()!=sf::Music::Status::Playing)
                    _sound_move.play();
                
                
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

        _text_menu.setPosition(width_window/2  , thickness_line + height_window / 20);
        _text_joueur2.setPosition(width_window/2  ,thickness_line + height_window / 2.25);
        _text_joueur1.setPosition(width_window/2  ,thickness_line  + height_window / 7);


        window.clear(color_background);

        // sprite display joueur 1
        s_fleches.setPosition(thickness_line, s_fleches.getGlobalBounds().height + thickness_line + height_window / 17);
        window.draw(s_fleches);
        s_ctrl_2.setPosition(s_ctrl_2.getGlobalBounds().width*3 + thickness_line, s_ctrl_2.getGlobalBounds().height+s_fleches.getGlobalBounds().height + thickness_line + height_window / 17);
        window.draw(s_ctrl_2);
        s_shift_2.setPosition(s_shift_2.getGlobalBounds().width*4 + thickness_line, s_shift_2.getGlobalBounds().height+s_fleches.getGlobalBounds().height + thickness_line + height_window / 17);
        window.draw(s_shift_2);
        s_tab.setPosition(s_tab.getGlobalBounds().width*5 + thickness_line, s_tab.getGlobalBounds().height+s_fleches.getGlobalBounds().height + thickness_line + height_window / 17);
        window.draw(s_tab);

        // sprite display joueur 2
        s_touches.setPosition(thickness_line, s_touches.getGlobalBounds().height + thickness_line + height_window / 2.75);
        window.draw(s_touches);
        s_ctrl_1.setPosition(s_ctrl_1.getGlobalBounds().width*3 + thickness_line, s_touches.getGlobalBounds().height+s_ctrl_1.getGlobalBounds().height + thickness_line + height_window / 2.75);
        window.draw(s_ctrl_1);
        s_shift_1.setPosition(s_shift_1.getGlobalBounds().width*4 + thickness_line, s_touches.getGlobalBounds().height+s_shift_1.getGlobalBounds().height + thickness_line + height_window / 2.75);
        window.draw(s_shift_1);
        s_enter.setPosition(s_enter.getGlobalBounds().width*5 + thickness_line, s_touches.getGlobalBounds().height+s_enter.getGlobalBounds().height + thickness_line + height_window / 2.75);
        window.draw(s_enter);

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

t_number t_textures_to_index(t_textures texture)
{
    return static_cast<t_number>(texture);
}
