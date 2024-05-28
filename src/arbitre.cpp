#include "arbitre.h"

/*
 * On send un signal comme quoi on cree un arbitre dans l'instance du serveur et on le fait connecter au client
 * */
arbitre::arbitre(t_number ind, typeplayer plyr1, typeplayer plyr2, unsigned int port)
    : _vertical_speed(0.1), _nb_frame(0)

{
    delay_player1 = std::make_unique<delay>();
    *delay_player1 = {false, nullptr, nullptr, 0, 0, 0, false, _vertical_speed, -1, 0, 0, 1, 0, true, -1,0,false};

    delay_player2 = std::make_unique<delay>();
    *delay_player2 = {false, nullptr, nullptr, 0, 0, 0, false, _vertical_speed, -1, 0, 0, 1, 0, true, -1,0,false};

    bool jeu_reseau(plyr1 == typeplayer::client || plyr1 == typeplayer::server);
    bool server_game(plyr1 == typeplayer::server);

    if (ind == 0)
    { // easy
        if (jeu_reseau && server_game)
        {
            _player1 = std::make_unique<server>(port);
            _player2 = std::make_unique<game>();
        }
        else if (jeu_reseau && !server_game)
        {
            _player1 = std::make_unique<client>();
            _player2 = std::make_unique<game>();
        }
        else if (plyr2 != typeplayer::none)
        { // jeu_duo

            if (plyr1 == typeplayer::ai)
                _player1 = std::make_unique<ai>();
            else
                _player1 = std::make_unique<game>();

            if (plyr2 == typeplayer::ai)
                _player2 = std::make_unique<ai>();
            else
                _player2 = std::make_unique<game>();
        }
        else
        {
            if (plyr1 == typeplayer::ai)
                _player1 = std::make_unique<ai>();
            else
            {
                _player1 = std::make_unique<game>();
            }

            _player2 = nullptr;
            delay_player2 = nullptr;
        }
    }
    else if (ind == 1)
    { // medium
        if (jeu_reseau && server_game)
        {
            _player1 = std::make_unique<server>(port, 12, 6, 6);
            _player2 = std::make_unique<game>(12, 6, 6);
        }
        else if (jeu_reseau && !server_game)
        {
            _player1 = std::make_unique<client>(12, 6, 6);
            _player2 = std::make_unique<game>(12, 6, 6);
        }
        else if (plyr2 != typeplayer::none)
        { // jeu_duo

            if (plyr1 == typeplayer::ai)
                _player1 = std::make_unique<ai>(12, 6, 6, 15, 1);
            else
                _player1 = std::make_unique<game>(12, 6, 6);

            setVerticalSpeed_Med();

            if (plyr2 == typeplayer::ai)
                _player2 = std::make_unique<ai>(12, 6, 6, 15, 1);
            else
                _player2 = std::make_unique<game>(12, 6, 6);
        }
        else
        {

            if (plyr1 == typeplayer::ai)
                _player1 = std::make_unique<ai>(12, 6, 6, 15, 1);
            else
                _player1 = std::make_unique<game>(12, 6, 6);
            setVerticalSpeed_Med();

            _player2 = nullptr;
            delay_player2 = nullptr;
        }
    }
    else
    { // hard
        if (jeu_reseau && server_game)
        {
            _player1 = std::make_unique<server>(port, 14, 8, 6);
            _player2 = std::make_unique<game>(14, 8, 6);
        }
        else if (jeu_reseau && !server_game)
        {
            _player1 = std::make_unique<client>(14, 8, 6);
            _player2 = std::make_unique<game>(14, 8, 6);
        }
        else if (plyr2 != typeplayer::none)
        { // jeu_duo
            if (plyr1 == typeplayer::ai)
            {
                _player1 = std::make_unique<ai>(14, 8, 6, 10, 1);
            }
            else
            {
                _player1 = std::make_unique<game>(14, 8, 6); // a changer
            }

            setVerticalSpeed_Hard();

            if (plyr2 == typeplayer::ai)
                _player2 = std::make_unique<ai>(14, 8, 6, 10, 1);
            else
                _player2 = std::make_unique<game>(14, 8, 6);
        }
        else
        {
            if (plyr1 == typeplayer::ai)
                _player1 = std::make_unique<ai>(14, 8, 6, 10, 1);
            else
                _player1 = std::make_unique<game>(14, 8, 6);

            setVerticalSpeed_Hard();

            _player2 = nullptr;
            delay_player2 = nullptr;
        }
    }
}

void arbitre::update(t_action x, bool first_player)
{
    _nb_frame++;
    if (jeu_duo() && x == t_action::generate_malus)
    {
        _player1->setAction(x);
        updatePlayer(_player1->getBlow(getFrame()), true);
        _player2->setAction(x);
        updatePlayer(_player2->getBlow(getFrame()), false);
    }
    else if (first_player && delay_player1->activated)
    {
        //std::cout << "first \n";
        _player1->setAction(x);
        updatePlayer(_player1->getBlow(getFrame()), true);
    }
    else if (jeu_duo() && !first_player and delay_player2->activated)
    {
        //std::cout << "second \n";
        _player2->setAction(x);
        updatePlayer(_player2->getBlow(getFrame()), false);
    }
}

void arbitre::updatePlayer(t_action x, bool first_player)
{
    game *player_to_update = ((first_player) ? (_player1.get()) : (_player2.get()));
    delay *delay_to_update = ((first_player) ? (delay_player1.get()) : (delay_player2.get()));
    if(delay_to_update->score_signal){
        player_to_update->inc_score(delay_to_update->score );
        delay_to_update->score = 0;
        delay_to_update->score_signal=false;
    }
    // player_to_update->update_garbage_height();
    auto it = delay_to_update->cells_slide.begin();
    while (it != delay_to_update->cells_slide.end())
    {
        auto cells = *it;
        if (player_to_update->is_garbage(*cells))
        {
            it++;
        }
        else
        {
            if (((*player_to_update)(position(cells->x(), cells->y() + 1)) != t_colors::empty_cell and player_to_update->cellDy(position(cells->x(), cells->y() + 1)) == 0 and player_to_update->cellDy(*cells) == 0))
            {
                if(first_player)std::cout<<"player1 : ";
                else std::cout<<"player2 :"; 
                std::cout <<"erased: " << toString_color((*player_to_update)(*cells)) << ", at position: " << cells->x() << ", " << cells->y() << "\n";
                delete cells;
                it = delay_to_update->cells_slide.erase(it); // Supprimer l'élément et mettre à jour l'itérateur
            }
            else
            {
                if (player_to_update->cellDy(*cells) >= 64)
                {
                    player_to_update->switch_cells_fall(*cells, position(cells->x(), cells->y() + 1));
                    cells->sety(cells->y() + 1);
                    player_to_update->resetCellDelta(*cells);
                }
                else
                {
                    player_to_update->setCellDy(*cells, 16);
                }

                ++it; // Passer à l'élément suivant
            }
        }
    }
    it = delay_to_update->cells_slide.begin();
    while (it != delay_to_update->cells_slide.end())
    {
        auto cells = *it;
        if (!player_to_update->is_garbage(*cells))
        {
            it++;
        }
        else
        {
            if ((player_to_update->cellDy(*cells) == 0 && player_to_update->is_garbage(*cells) and !player_to_update->hanging_malus_slide(*cells, delay_to_update->cells_slide)))
            {
                std::cout << "erased: " << toString_color((*player_to_update)(*cells)) << ", at position: " << cells->x() << ", " << cells->y() << "\n";
                delete cells;
                it = delay_to_update->cells_slide.erase(it); // Supprimer l'élément et mettre à jour l'itérateur
            }
            else
            {
                if (player_to_update->cellDy(*cells) >= 64)
                {
                    player_to_update->switch_cells_fall(*cells, position(cells->x(), cells->y() + 1));
                    cells->sety(cells->y() + 1);
                    player_to_update->resetCellDelta(*cells);
                }
                else
                {
                    player_to_update->setCellDy(*cells, 16);
                }

                ++it; // Passer à l'élément suivant
            }
        }
    }

    if (delay_to_update->cells_switch1 and delay_to_update->cells_switch2)
    {
        if (delay_to_update->switch_vertical)
        {
            player_to_update->setCellDy(*delay_to_update->cells_switch1, 8);
            player_to_update->setCellDy(*delay_to_update->cells_switch2, -8);
            if (player_to_update->cellDy(*delay_to_update->cells_switch1) >= 64 or player_to_update->cellDy(*delay_to_update->cells_switch2) <= -64)
            {
                player_to_update->switch_cells_position(*delay_to_update->cells_switch1, *delay_to_update->cells_switch2);
                player_to_update->resetCellDelta(*delay_to_update->cells_switch1);
                player_to_update->resetCellDelta(*delay_to_update->cells_switch2);

                delete delay_to_update->cells_switch1;
                delete delay_to_update->cells_switch2;
                delay_to_update->cells_switch1 = nullptr;
                delay_to_update->cells_switch2 = nullptr;
            }
        }
        else
        {
            player_to_update->setCellDx(*delay_to_update->cells_switch1, 8);
            player_to_update->setCellDx(*delay_to_update->cells_switch2, -8);
            if (player_to_update->cellDx(*delay_to_update->cells_switch1) >= 64 or player_to_update->cellDx(*delay_to_update->cells_switch2) <= -64)
            {

                player_to_update->resetCellDelta(*delay_to_update->cells_switch1);
                player_to_update->resetCellDelta(*delay_to_update->cells_switch2);
                player_to_update->switch_cells_position(*delay_to_update->cells_switch1, *delay_to_update->cells_switch2);
                if (player_to_update->one_case_empty(*delay_to_update->cells_switch1, *delay_to_update->cells_switch2))
                { // si une deux cases etaient vide
                    player_to_update->slideColumn(delay_to_update->cells_switch1->x(), delay_to_update->cells_slide);
                    player_to_update->slideColumn(delay_to_update->cells_switch2->x(), delay_to_update->cells_slide);
                }
                delete delay_to_update->cells_switch1;
                delete delay_to_update->cells_switch2;
                delay_to_update->cells_switch1 = nullptr;
                delay_to_update->cells_switch2 = nullptr;
            }
        }
    }

    if (x != t_action::nothing)
    {
        switch (x)
        {
        case t_action::go_right:
        {
            player_to_update->move_target(t_direction::right);
            break;
        }
        case t_action::go_left:
        {
            player_to_update->move_target(t_direction::left);
            break;
        }
        case t_action::go_up:
        {
            player_to_update->move_target(t_direction::up);
            break;
        }
        case t_action::go_down:
        {
            player_to_update->move_target(t_direction::down);
            break;
        }
        case t_action::change_direction:
        {
            if(!delay_to_update->cells_switch1 && !delay_to_update->cells_switch2)
                player_to_update->rotate_target();
            break;
        }
        case t_action::exchange:
        {
            if (!player_to_update->target_cells_empty() and delay_to_update->cells_switch1 == nullptr and delay_to_update->cells_switch2 == nullptr and !(player_to_update->target_verticale() and player_to_update->one_case_empty()) and !(player_to_update->is_garbage(player_to_update->getcell1target()) || player_to_update->is_garbage(player_to_update->getcell2target())))
            {
                position first_cell = position(player_to_update->getcell1target().x(), player_to_update->getcell1target().y());
                position snd_cell =  position(player_to_update->getcell2target().x(), player_to_update->getcell2target().y());
                auto it = std::find_if(delay_to_update->cells_align.begin(), delay_to_update->cells_align.end(), [&first_cell](position & pos)
                                       { return pos == first_cell; });
                auto it2 = std::find_if(delay_to_update->cells_align.begin(), delay_to_update->cells_align.end(), [&snd_cell](position & pos)
                                        { return pos == snd_cell; });
                if (it == delay_to_update->cells_align.end() && it2 == delay_to_update->cells_align.end() && player_to_update->cellDx(first_cell) == 0 && player_to_update->cellDy(first_cell) == 0 && player_to_update->cellDx(snd_cell) == 0 && player_to_update->cellDy(snd_cell) == 0)
                {

                    if (player_to_update->target_verticale())
                        delay_to_update->switch_vertical = true;
                    else
                        delay_to_update->switch_vertical = false;

                    delay_to_update->cells_switch1 = new position(player_to_update->getcell1target().x(), player_to_update->getcell1target().y());
                    delay_to_update->cells_switch2 = new position(player_to_update->getcell2target().x(), player_to_update->getcell2target().y());
                }
            }

            break;
        }
        case t_action::accelerate:
        {
            // accelerer
            delay_to_update->newline = true;
            break;
        }
        case t_action::generate_malus:
        {
            // On genere un malus
            player_to_update->add_garbage(delay_to_update->cells_slide);
            // delay_to_update->last_frame_alignment = getFrame();
            delay_to_update->last_garbage = getFrame();
            break;
        }
        default:
            break;
        }
    }

    if (delay_to_update->newline)
    {

        if (player_to_update->grid_dy() >= 64)
        {
            player_to_update->add_new_row();
            increment_delays_y_pos(delay_to_update);

            // On remet a zero grid_dy
            player_to_update->setGrid_dy(0);
            delay_to_update->newline = false;
            _vertical_speed = delay_to_update->oldspeed;
            std::cout << "2";
        }
        _vertical_speed += 0.1;
        if (delay_to_update->cells_align.size() == 0)
            player_to_update->setGrid_dy(player_to_update->grid_dy() + _vertical_speed + 5);
    }

    else
    {
        if (player_to_update->grid_dy() >= 64)
        {
            player_to_update->add_new_row(150);
            increment_delays_y_pos(delay_to_update);

            // On remet a zero grid_dy
            player_to_update->setGrid_dy(0);
            delay_to_update->newline = false;
            _vertical_speed = delay_to_update->oldspeed;
            
        }
        else
        {
            if (delay_to_update->cells_align.size() == 0)
                player_to_update->setGrid_dy(player_to_update->grid_dy() + _vertical_speed);
            _vertical_speed += 0.00001;
            delay_to_update->oldspeed += 0.00001;
        }
    }

    auto v(player_to_update->alignment()); // faut verifier les allignement meme si on a pas fait de swotch les cases qui monte peuvent former un alignement
    // if (v.size() >= 3)
    // {
        
    //     if (delay_to_update->last_frame_alignment == -1) // pas encore initialisé
    //         delay_to_update->last_frame_alignment = getFrame();
    //     else if ((getFrame() - (delay_to_update->last_frame_alignment) < 90) && (getFrame() - (delay_to_update->last_garbage) > 150)) // si les deux alignement ont ete fait en moins de 3 sec (90 frame) et qu'on vient pas tout juste degenerer un malus
    //     {
    //         if(jeu_duo()) //si jeu a deux joueur les alignement causent des malus à l'adversaire
    //         {
    //             delay_to_update->last_frame_alignment=getFrame(); //ou que c'est un alignement de 5 et plus on genere un malus
    //             if (player_to_update == _player1.get())
    //                 _player2->add_garbage(delay_player2->cells_slide);
    //             else
    //                 _player1->add_garbage(delay_to_update->cells_slide);
    //             delay_to_update->last_garbage=getFrame();
    //         } else {
    //             delay_to_update->last_frame_alignment=getFrame(); //ou que c'est un alignement de 5 et plus on genere un malus
    //             player_to_update->add_garbage(delay_to_update->cells_slide);
    //             delay_to_update->last_garbage=getFrame();
    //         }
    //     }

    //     if (delay_to_update->last_garbage > 0)
    //     {
            
    //         // for (auto e : delay_to_update->cells_slide)
    //         // {
    //         //     std::cout << e->x() << ',' << e->y() << std::endl;
    //         // }
    //         player_to_update->transform_malus_to_cell(v, delay_to_update->cells_slide);

    //         // ajouter que les cases glissent
    //     }
    //     v = player_to_update->alignment();
    // }
    
    delay_to_update->cells_align = v;
    if (delay_to_update->angle >= 360 || delay_to_update->scale <= 0)
    {
        delay_to_update->angle = 0;
        delay_to_update->scale = 1;
        if( delay_to_update->combo==0 || delay_to_update->last_frame_alignment==-1){
            delay_to_update->combo++;
            delay_to_update->last_frame_alignment=getFrame();
        }
        else if(getFrame()-delay_to_update->last_frame_alignment<120){
            delay_to_update->combo++;
            delay_to_update->last_frame_alignment = getFrame();
            if(delay_to_update->combo % 3 == 0){
                if(jeu_duo()){
                    if(first_player)
                        _player2->add_garbage(delay_player2->cells_slide);
                    else
                        _player1->add_garbage(delay_player1->cells_slide);
                }
                else{
                    player_to_update->add_garbage(delay_to_update->cells_slide);
                }
            }
        }
        else {
            delay_to_update->last_frame_alignment=getFrame();
            delay_to_update->combo=1;
        }
        // player_to_update->inc_score(getdelay_to_update().cells_align.size());
        for (std::size_t i(0); i < v.size(); i++)
        {
            delay_to_update->score+=1*delay_to_update->combo;
            auto col(v[i].x());
            player_to_update->delete_cell(v[i]);
            player_to_update->slideColumn(col, delay_to_update->cells_slide);
        }
    }
    else if (delay_to_update->cells_align.size() != 0)
    {
        delay_to_update->angle += 24;
        delay_to_update->scale -= 0.1;
    }
    if (player_to_update->is_lost())
        delay_to_update->activated = false;
    if (first_player and jeu_duo() and !delay_player2->activated)
    {
        if (delay_player1->time_left == -1)
            delay_player1->time_left = 600;
        else if (delay_player1->time_left == 0)
        {
            delay_player1->activated = false;
        }
        else
            delay_player1->time_left--;
    }
    if (!first_player and jeu_duo() and !delay_player1->activated)
    {
        if (delay_player2->time_left == -1)
            delay_player2->time_left = 600;
        else if (delay_player2->time_left == 0)
        {
            delay_player2->activated = false;
        }
        else
            delay_player2->time_left--;
    }
    if (v.size() >= 3){
        player_to_update->transform_malus_to_cell(v, delay_to_update->cells_slide);

    }
}

game &arbitre::player1() const
{
    return (*_player1);
}

game &arbitre::player2() const
{
    return (*_player2);
}
void arbitre::init(t_number seed)
{
    if (jeu_res())
    { // On donne une seed
        _player1->init(seed);
        _player2->init(seed);
    }
    else
    { // Pas de seed car soit jeu solo soit duo meme machine
        _player1->init();
        if (_player2 != nullptr)
            _player2->init();
    }
}

delay &arbitre::getDelays(bool first_player)
{
    if (first_player)
        return *delay_player1;
    return *delay_player2;
}

bool arbitre::jeu_duo() const
{
    return _player2 != nullptr;
}

bool arbitre::jeu_res() const
{
    return dynamic_cast<remote_game *>(_player1.get());
}

bool arbitre::server_game() const
{
    return dynamic_cast<server *>(_player1.get());
}

bool arbitre::connected() const
{
    auto joueur = dynamic_cast<remote_game *>(_player1.get());
    return joueur && joueur->connected();
}

void arbitre::connect(const sf::IpAddress &server_ip, unsigned int port)
{
    auto joueur = dynamic_cast<client *>(_player1.get());
    if (joueur)
        joueur->connect(server_ip, port);
}

void arbitre::connect_client()
{
    auto joueur = dynamic_cast<server *>(_player1.get());
    if (joueur)
        joueur->connect_client();
}

void arbitre::send_action(const t_action &action)
{
    auto joueur = dynamic_cast<remote_game *>(_player1.get());
    if (joueur)
        joueur->send_action(action);
}

sf::Socket::Status arbitre::recieve_action(t_action &action)
{
    auto joueur = dynamic_cast<remote_game *>(_player1.get());
    if (joueur)
        return joueur->recieve_action(action);
    return sf::Socket::Error; // TODO: peut etre remplacer par une exception
}

void arbitre::send_number(t_number number)
{
    auto joueur = dynamic_cast<remote_game *>(_player1.get());
    if (joueur)
        joueur->send_number(number);
}

sf::Socket::Status arbitre::recieve_number(t_number &number)
{
    auto joueur = dynamic_cast<remote_game *>(_player1.get());
    if (joueur)
        return joueur->recieve_number(number);
    return sf::Socket::Error; // TODO: peut etre remplacer par une exception
}

void arbitre::send_string(std::string message)
{
    auto joueur = dynamic_cast<remote_game *>(_player1.get());
    if (joueur)
        joueur->send_string(message);
}

sf::Socket::Status arbitre::recieve_string(std::string &message)
{
    auto joueur = dynamic_cast<remote_game *>(_player1.get());
    if (joueur)
        return joueur->recieve_string(message);
    return sf::Socket::Error; // TODO: peut etre remplacer par une exception
}

void arbitre::increment_delays_y_pos(delay * delay_to_update)
{
    for (auto &it : delay_to_update->cells_align)
    {
        it.sety(it.y() - 1);
    }

    for (auto &it : delay_to_update->cells_slide)
    {
        it->sety(it->y() - 1);
    }
    if (delay_to_update->cells_switch1)
        delay_to_update->cells_switch1->sety(delay_to_update->cells_switch1->y() - 1);
    if (delay_to_update->cells_switch2)
        delay_to_update->cells_switch2->sety(delay_to_update->cells_switch2->y() - 1);
}
bool arbitre::lost() const
{
    if (jeu_duo())
    {
        return (_player1->is_lost() || _player2->is_lost());
    }
    else
        return _player1->is_lost();
}
