#include "arbitre.h"

arbitre::arbitre()
    : _joueur1(std::make_unique<game>())
    , _vertical_speed(0.1)
    ,_nb_frame(0)
{}
void arbitre::update(t_action x){
   if(x != t_action::nothing){
        switch(x){
        case t_action::go_right :{
         _joueur1->move_target(t_direction::right);
         break;

        } 
        case t_action::go_left :{
         _joueur1->move_target(t_direction::left);
                  break;


        } case t_action::go_up :{
         _joueur1->move_target(t_direction::up);
         break;

        } case t_action::go_down :{
         _joueur1->move_target(t_direction::down);
         break;

        } 
        case t_action::change_direction :
        { _joueur1->rotate_target();
             break;
    
        }
        case t_action::exchange :{
            if(!_joueur1->target_cells_empty()){
                if(_joueur1->switch_cells_target()){ //le switch a ete effectuee
                        if(_joueur1->one_case_empty()){ //si une deux cases etaient vide
                            _joueur1->drop();
                        }
                     if(_joueur1->cells_above()){
                        _joueur1->slideColumn(_joueur1->getcell1target().x());
                        _joueur1->slideColumn(_joueur1->getcell2target().x());
                    }
                    }
                }
        break;

        }
        case t_action::accelerate:{
            //accelerer
            _joueur1->add_new_row();
            _joueur1->setGrid_dy(0);
                      break;


        }
    }
 }   auto v(_joueur1->alignment()); //faut verifier les allignement meme si on a pas fait de swotch les cases qui monte peuvent former un alignement
                    while(v.size()>=3){ 
                        
                        for(std::size_t i(0);i<v.size();i++){
                            auto col(v[i].x());
                            _joueur1->delete_cell(v[i]);
                            _joueur1->slideColumn(col);

                        }
                        v=_joueur1->alignment();

                    } 
    _nb_frame++; //on incremente le nombre de frame
}

game& arbitre::getJoueur() const{
    return (*_joueur1);
}
void arbitre::init (){
    _joueur1->init();
}
