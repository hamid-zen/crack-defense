#include "arbitre.h"

arbitre::arbitre()
    : _joueur1(std::make_unique<game>()), _vertical_speed(0.1), _nb_frame(0)

{
    delays = {nullptr, nullptr, 0, 0, 0, false, _vertical_speed};
}
std::vector<position>  arbitre::update(t_action x)
{
    

    if (delays.cells_switch1 and delays.cells_switch2)
    {
        if (_joueur1->target_verticale())
        {
            _joueur1->setCellDy(*delays.cells_switch1, 8);
            _joueur1->setCellDy(*delays.cells_switch2, -8);
            if (_joueur1->cellDy(*delays.cells_switch1) >= 64 or _joueur1->cellDy(*delays.cells_switch2) <= -64)
            {
                _joueur1->switch_cells_position(*delays.cells_switch1, *delays.cells_switch2);
                _joueur1->resetCellDelta(*delays.cells_switch1);
                _joueur1->resetCellDelta(*delays.cells_switch2);
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
                    _joueur1->slideColumn(delays.cells_switch1->x());
                    _joueur1->slideColumn(delays.cells_switch2->x());
                }
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
            if (!_joueur1->target_cells_empty() and delays.cells_switch1 == nullptr and delays.cells_switch2 == nullptr and !(_joueur1->target_verticale() and _joueur1->one_case_empty()))
            {

                delays.cells_switch1 = new position(_joueur1->getcell1target().x(), _joueur1->getcell1target().y());
                delays.cells_switch2 = new position(_joueur1->getcell2target().x(), _joueur1->getcell2target().y());
            }

            // if(!_joueur1->target_cells_empty()){
            //     if(_joueur1->switch_cells_target()){ //le switch a ete effectuee
            //             if(_joueur1->one_case_empty()){ //si une deux cases etaient vide
            //                 _joueur1->drop();
            //             }
            //          if(_joueur1->cells_above()){
            //             _joueur1->slideColumn(_joueur1->getcell1target().x());
            //             _joueur1->slideColumn(_joueur1->getcell2target().x());
            //         }
            //         }
            //     }
            break;
        }
        case t_action::accelerate:
        {
            // accelerer
            delays.newline = true;
            // _joueur1->add_new_row();
            // _joueur1->setGrid_dy(0);
            break;
        }
        }
    }

    if (delays.newline)
    {
        
        if (_joueur1->grid_dy() >= 64)
        {
            _joueur1->add_new_row();
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
            _joueur1->add_new_row();
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
    while (v.size() >= 3)
    {
        return v;

        for (std::size_t i(0); i < v.size(); i++)
        {
            auto col(v[i].x());
            _joueur1->delete_cell(v[i]);
            _joueur1->slideColumn(col);
        }
        v = _joueur1->alignment();
    }
    _nb_frame++; // on incremente le nombre de frame
}

game &arbitre::getJoueur() const
{
    return (*_joueur1);
}
void arbitre::init()
{
    _joueur1->init();
}

delay arbitre::getDelays() const
{
    return delays;
}
