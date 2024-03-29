#include "arbiter.h"

arbiter::arbiter()
    :_joueur1(std::make_unique<game> ()){}

void arbiter::play(){
    //recuperer les paramettre
    int i=0;
    _joueur1->init();
    
}