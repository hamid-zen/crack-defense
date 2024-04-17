#include "arbitre.h"


arbitre::arbitre(t_number ind,bool jeu_duo)
    : _vertical_speed(0.1), _nb_frame(0)

{
    delays = {false,nullptr, nullptr, 0, 0, 0, false, _vertical_speed, -1, 0, 0, 1};
    if(ind==0){ //easy
        _joueur1=std::make_unique<game>();
        if(jeu_duo){
            _joueur2=std::make_unique<game>();
            delays2={false,nullptr, nullptr, 0, 0, 0, false, _vertical_speed, -1, 0, 0, 1};
        }else{
            _joueur2=nullptr;
        }

    }else if(ind==1){ //medium
        _joueur1=std::make_unique<game>(12,6,6);
        setVerticalSpeed_Med();
        if(jeu_duo){
            _joueur2=std::make_unique<game>(12,6,6);
            delays2={false,nullptr, nullptr, 0, 0, 0, false, _vertical_speed, -1, 0, 0, 1};
        }else{
            _joueur2=nullptr;
        }
    }else{ //hard
        _joueur1=std::make_unique<game>(14,8,6); //a changer
        setVerticalSpeed_Hard();
        if(jeu_duo){
            _joueur2=std::make_unique<game>(14,8,6);
            delays2={false,nullptr, nullptr, 0, 0, 0, false, _vertical_speed, -1, 0, 0, 1};
        }else{
            _joueur2=nullptr;
        }
    }
}
void  arbitre::update(t_action x, bool first_player)
{
    if(first_player)
        updateFirstPlayer(x);
    else updateSecondPlayer(x);
}  

void  arbitre::updateFirstPlayer(t_action x )
{
    //_joueur1->update_garbage_height();
    auto it = delays.cells_slide.begin();
    while (it != delays.cells_slide.end())
    {
        auto cells = *it;
        if (((*_joueur1)(position(cells->x(), cells->y() + 1)) != t_colors::empty_cell and _joueur1->cellDy(position(cells->x(),cells->y()+1))==0 and _joueur1->cellDy(*cells) == 0)||(_joueur1->is_garbage(*cells)and !_joueur1->hanging_malus(*cells)))
        {                                      
            std::cout << "erased: " << toString_color((*_joueur1)(*cells)) << ", at position: " << cells->x() << ", " << cells->y() << "\n";
            delete cells;
            it = delays.cells_slide.erase(it); // Supprimer l'élément et mettre à jour l'itérateur

        }
        else
        {
            if (_joueur1->cellDy(*cells) >= 64)
            {
                _joueur1->switch_cells_fall(*cells, position(cells->x(), cells->y() + 1));
                cells->sety(cells->y() + 1);
                _joueur1->resetCellDelta(*cells);
            }
            else
            {
                _joueur1->setCellDy(*cells, 16);
            }

            ++it; // Passer à l'élément suivant
        }
    }
    

    if (delays.cells_switch1 and delays.cells_switch2)
    {
        if (delays.switch_vertical)
        {
            _joueur1->setCellDy(*delays.cells_switch1, 8);
            _joueur1->setCellDy(*delays.cells_switch2, -8);
            if (_joueur1->cellDy(*delays.cells_switch1) >= 64 or _joueur1->cellDy(*delays.cells_switch2) <= -64)
            {
                _joueur1->switch_cells_position(*delays.cells_switch1, *delays.cells_switch2);
                _joueur1->resetCellDelta(*delays.cells_switch1);
                _joueur1->resetCellDelta(*delays.cells_switch2);

                delete delays.cells_switch1;
                delete delays.cells_switch2;
                delays.cells_switch1 = nullptr;
                delays.cells_switch2 = nullptr;
            }
        }
        else
        {
            _joueur1->setCellDx(*delays.cells_switch1, 8);
            _joueur1->setCellDx(*delays.cells_switch2, -8);
            if (_joueur1->cellDx(*delays.cells_switch1) >= 64 or _joueur1->cellDx(*delays.cells_switch2) <= -64)
            {

                _joueur1->resetCellDelta(*delays.cells_switch1);
                _joueur1->resetCellDelta(*delays.cells_switch2);
                _joueur1->switch_cells_position(*delays.cells_switch1, *delays.cells_switch2);
                if (_joueur1->one_case_empty(*delays.cells_switch1, *delays.cells_switch2))
                { // si une deux cases etaient vide
                    _joueur1->slideColumn(delays.cells_switch1->x(), delays.cells_slide);
                    _joueur1->slideColumn(delays.cells_switch2->x(), delays.cells_slide);
                }
                delete delays.cells_switch1;
                delete delays.cells_switch2;
                delays.cells_switch1 = nullptr;
                delays.cells_switch2 = nullptr;
            }
        }
    }

    

    if (x != t_action::nothing)
    {
        switch (x)
        {
        case t_action::go_right:
        {
            _joueur1->move_target(t_direction::right);
            break;
        }
        case t_action::go_left:
        {
            _joueur1->move_target(t_direction::left);
            break;
        }
        case t_action::go_up:
        {
            _joueur1->move_target(t_direction::up);
            break;
        }
        case t_action::go_down:
        {
            _joueur1->move_target(t_direction::down);
            break;
        }
        case t_action::change_direction:
        {
            _joueur1->rotate_target();
            break;
        }
        case t_action::exchange:
        {
            if (!_joueur1->target_cells_empty() and delays.cells_switch1 == nullptr and delays.cells_switch2 == nullptr and !(_joueur1->target_verticale() and _joueur1->one_case_empty())and !(_joueur1->is_garbage(_joueur1->getcell1target()) || _joueur1->is_garbage(_joueur1->getcell2target())))
            {

                if(_joueur1->target_verticale())
                    delays.switch_vertical=true;
                else 
                    delays.switch_vertical=false;
                delays.cells_switch1 = new position(_joueur1->getcell1target().x(), _joueur1->getcell1target().y());
                delays.cells_switch2 = new position(_joueur1->getcell2target().x(), _joueur1->getcell2target().y());
            }

            break;
        }
        case t_action::accelerate:
        {
            // accelerer
            delays.newline = true;
            break;
        }
        case t_action::generate_malus:
        {
            // On genere un malus
            // rajouter la touche pour envoyer un garbage a l'autre
            _joueur1->add_garbage(delays.cells_slide);
            break;
        }
        default: break;
        }
    }

    if (delays.newline)
    {
        
        if (_joueur1->grid_dy() >= 64)
        {
            _joueur1->add_new_row();
            increment_delays_y_pos();
            
            // On remet a zero grid_dy
            _joueur1->setGrid_dy(0);
            delays.newline = false;
            _vertical_speed = delays.oldspeed;
            std::cout<<"2";
        }
        _vertical_speed += 0.1;
        _joueur1->setGrid_dy(_joueur1->grid_dy() + _vertical_speed + 5);
    }

    else {
        if (_joueur1->grid_dy() >= 64)
        {   
            _joueur1->add_new_row(150);
            increment_delays_y_pos();

            // On remet a zero grid_dy
            _joueur1->setGrid_dy(0);
            delays.newline = false;
            _vertical_speed = delays.oldspeed;
            std::cout<<"1";
        }
        else{
            _joueur1->setGrid_dy(_joueur1->grid_dy() + _vertical_speed);
            _vertical_speed +=0.00001;
            delays.oldspeed +=0.00001 ;
        }
    }

    auto v(_joueur1->alignment()); // faut verifier les allignement meme si on a pas fait de swotch les cases qui monte peuvent former un alignement
    if (v.size() >= 3)
    {  if(delays.last_frame_alignment==-1)//pas encore initialisé
        {
            delays.last_frame_alignment=getFrame();
        }else if(( (getFrame()-(delays.last_frame_alignment) <90)|| (v.size()>4) )&& getFrame()-delays.last_garbage>60) //si les deux alignement ont ete fait en moins de 3 sec (90 frame) et qu'on vient pas tout juste degenerer un malus
        {
            // delays.last_frame_alignment=getFrame(); //ou que c'est un alignement de 5 et plus on genere un malus
            //  delays.last_garbage=getFrame();
            //  _joueur1->add_garbage(delays.cells_slide);
        }   


        if(delays.last_garbage>0){
            _joueur1->transform_malus_to_cell(v,delays.cells_slide);
            //ajouter que les cases glissent
        }


        v = _joueur1->alignment();
    }
    _nb_frame++; // on incremente le nombre de frame
    delays.cells_align = v;
    if (delays.angle >= 360 || delays.scale <= 0) {
        delays.angle = 0;
        delays.scale = 1;
        _joueur1->inc_score(getDelays().cells_align.size());
        for (std::size_t i(0); i < v.size(); i++)
        {
            auto col(v[i].x());
            _joueur1->delete_cell(v[i]);
            _joueur1->slideColumn(col, delays.cells_slide);
        }
    }
    else if(delays.cells_align.size()!=0) {
        delays.angle += 24;
        delays.scale -= 0.1;
    }
}
void  arbitre::updateSecondPlayer(t_action x )
{
    //_joueur1->update_garbage_height();
    auto it = delays2.cells_slide.begin();
    while (it != delays2.cells_slide.end())
    {
        auto cells = *it;
        if (((*_joueur2)(position(cells->x(), cells->y() + 1)) != t_colors::empty_cell and _joueur2->cellDy(position(cells->x(),cells->y()+1))==0)||(_joueur2->is_garbage(*cells)and _joueur2->hanging_malus(*cells)))
        {                                      // Supprimer les éléments pairs
            std::cout << "erased: " << toString_color((*_joueur2)(*cells)) << ", at position: " << cells->x() << ", " << cells->y() << "\n";
            delete cells;
            it = delays2.cells_slide.erase(it); // Supprimer l'élément et mettre à jour l'itérateur
        }
        else
        {
            if (_joueur2->cellDy(*cells) >= 64)
            {
                _joueur2->switch_cells_fall(*cells, position(cells->x(), cells->y() + 1));
                cells->sety(cells->y() + 1);
                _joueur2->resetCellDelta(*cells);
            }
            else
            {
                _joueur2->setCellDy(*cells, 16);
            }

            ++it; // Passer à l'élément suivant
        }
    }
    

    if (delays2.cells_switch1 and delays2.cells_switch2)
    {
        if (delays2.switch_vertical)
        {
            _joueur2->setCellDy(*delays2.cells_switch1, 8);
            _joueur2->setCellDy(*delays2.cells_switch2, -8);
            if (_joueur2->cellDy(*delays2.cells_switch1) >= 64 or _joueur2->cellDy(*delays2.cells_switch2) <= -64)
            {
                _joueur2->switch_cells_position(*delays2.cells_switch1, *delays2.cells_switch2);
                _joueur2->resetCellDelta(*delays2.cells_switch1);
                _joueur2->resetCellDelta(*delays2.cells_switch2);

                delete delays2.cells_switch1;
                delete delays2.cells_switch2;
                delays2.cells_switch1 = nullptr;
                delays2.cells_switch2 = nullptr;
            }
        }
        else
        {
            _joueur2->setCellDx(*delays2.cells_switch1, 8);
            _joueur2->setCellDx(*delays2.cells_switch2, -8);
            if (_joueur2->cellDx(*delays2.cells_switch1) >= 64 or _joueur2->cellDx(*delays2.cells_switch2) <= -64)
            {

                _joueur2->resetCellDelta(*delays2.cells_switch1);
                _joueur2->resetCellDelta(*delays2.cells_switch2);
                _joueur2->switch_cells_position(*delays2.cells_switch1, *delays2.cells_switch2);
                if (_joueur2->one_case_empty(*delays2.cells_switch1, *delays2.cells_switch2))
                { // si une deux cases etaient vide
                    _joueur2->slideColumn(delays2.cells_switch1->x(), delays2.cells_slide);
                    _joueur2->slideColumn(delays2.cells_switch2->x(), delays2.cells_slide);
                }
                delete delays2.cells_switch1;
                delete delays2.cells_switch2;
                delays2.cells_switch1 = nullptr;
                delays2.cells_switch2 = nullptr;
            }
        }
    }

    

    if (x != t_action::nothing)
    {
        switch (x)
        {
        case t_action::go_right:
        {
            _joueur2->move_target(t_direction::right);
            break;
        }
        case t_action::go_left:
        {
            _joueur2->move_target(t_direction::left);
            break;
        }
        case t_action::go_up:
        {
            _joueur2->move_target(t_direction::up);
            break;
        }
        case t_action::go_down:
        {
            _joueur2->move_target(t_direction::down);
            break;
        }
        case t_action::change_direction:
        {
            _joueur2->rotate_target();
            break;
        }
        case t_action::exchange:
        {
            if (!_joueur2->target_cells_empty() and delays2.cells_switch1 == nullptr and delays2.cells_switch2 == nullptr and !(_joueur2->target_verticale() and _joueur2->one_case_empty())and !(_joueur2->is_garbage(_joueur2->getcell1target()) || _joueur2->is_garbage(_joueur2->getcell2target())))
            {
                if(_joueur2->target_verticale())
                    delays2.switch_vertical = true;
                else delays2.switch_vertical = false;

                delays2.cells_switch1 = new position(_joueur2->getcell1target().x(), _joueur2->getcell1target().y());
                delays2.cells_switch2 = new position(_joueur2->getcell2target().x(), _joueur2->getcell2target().y());
            }

            break;
        }
        case t_action::accelerate:
        {
            // accelerer
            delays2.newline = true;
            break;
        }
        case t_action::generate_malus:
        {
            // On genere un malus
            // rajouter la touche pour envoyer un garbage a l'autre
            _joueur2->add_garbage(delays2.cells_slide);
            break;
        }
        default: break;
        }
    }

    if (delays2.newline)
    {
        
        if (_joueur2->grid_dy() >= 64)
        {
            _joueur2->add_new_row();
            increment_delays_y_pos(false);
            // On remet a zero grid_dy
            _joueur2->setGrid_dy(0);
            delays2.newline = false;
            _vertical_speed = delays2.oldspeed;
            std::cout<<"2";
        }
        _vertical_speed += 0.1;
        _joueur2->setGrid_dy(_joueur2->grid_dy() + _vertical_speed + 5);
    }

    else {
        if (_joueur2->grid_dy() >= 64)
        {   
            _joueur2->add_new_row(150);
            increment_delays_y_pos(false);

            // On remet a zero grid_dy
            _joueur2->setGrid_dy(0);
            delays2.newline = false;
            _vertical_speed = delays2.oldspeed;
            std::cout<<"1";
        }
        else{
            _joueur2->setGrid_dy(_joueur2->grid_dy() + _vertical_speed);
            _vertical_speed +=0.00001;
            delays2.oldspeed +=0.00001 ;
        }
    }

    auto v(_joueur2->alignment()); // faut verifier les allignement meme si on a pas fait de swotch les cases qui monte peuvent former un alignement
    if (v.size() >= 3)
    {  if(delays2.last_frame_alignment==-1)//pas encore initialisé
        {
            delays2.last_frame_alignment=getFrame();
        }else if(( (getFrame()-(delays2.last_frame_alignment) <90)|| (v.size()>4) )&& getFrame()-delays2.last_garbage>60) //si les deux alignement ont ete fait en moins de 3 sec (90 frame) et qu'on vient pas tout juste degenerer un malus
        {
            // delays2.last_frame_alignment=getFrame(); //ou que c'est un alignement de 5 et plus on genere un malus
            //  delays2.last_garbage=getFrame();
            //  _joueur2->add_garbage(delays2.cells_slide);
        }   
        //  _nb_frame++; // on incremente le nombre de frame


        if(delays2.last_garbage>0){
            _joueur2->transform_malus_to_cell(v,delays2.cells_slide);
            //ajouter que les cases glissent
        }


        v = _joueur2->alignment();
    }
    _nb_frame++; // on incremente le nombre de frame
    delays2.cells_align = v;
    if (delays2.angle >= 360 || delays2.scale <= 0) {
        delays2.angle = 0;
        delays2.scale = 1;
        _joueur2->inc_score(getDelays(false).cells_align.size());
        for (std::size_t i(0); i < v.size(); i++)
        {
            auto col(v[i].x());
            _joueur2->delete_cell(v[i]);
            _joueur2->slideColumn(col, delays2.cells_slide);
        }
    }
    else if(delays2.cells_align.size()!=0) {
        delays2.angle += 24;
        delays2.scale -= 0.1;
    }
}

game &arbitre::getJoueur() const
{
    return (*_joueur1);
}

game &arbitre::getJoueur2() const
{
    return (*_joueur2);
}
void arbitre::init()
{
    _joueur1->init();
    if(_joueur2!=nullptr) //cas ; jeu duo
    {
        _joueur2->init();
    }
}

delay & arbitre::getDelays(bool first_player)
{
    if(!first_player)
        return delays2;
    return delays;
}

bool arbitre::jeu_duo() const
{
    return _joueur2!=nullptr;
}

void arbitre::increment_delays_y_pos(bool first_player)
{
    if(first_player){
        for(auto & it : delays.cells_align){
            it.sety(it.y()-1);
        }

        for(auto & it : delays.cells_slide){
            it->sety(it->y()-1);
        }
        if(delays.cells_switch1)
            delays.cells_switch1->sety(delays.cells_switch1->y()-1);
        if(delays.cells_switch2)
            delays.cells_switch2->sety(delays.cells_switch2->y()-1);
    }
    else {
        for(auto & it : delays2.cells_align){
            it.sety(it.y()-1);
        }

        for(auto & it : delays2.cells_slide){
            it->sety(it->y()-1);
        }
        if(delays2.cells_switch1)
            delays2.cells_switch1->sety(delays2.cells_switch1->y()-1);
        if(delays2.cells_switch2)
            delays2.cells_switch2->sety(delays2.cells_switch2->y()-1);
    }
}
