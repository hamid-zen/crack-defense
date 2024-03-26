#include "jeu.h"
#include <algorithm>

jeu::jeu(coordonne _max_hauteur, coordonne _max_largeur, int colors) //le viseur est positionné au millieu en debut de jeu
    :_grille1(_max_hauteur,_max_largeur,colors),_viseur(_max_largeur/2,_max_hauteur/2,_max_largeur/2+1,_max_hauteur/2+1),_score(0){}

bool jeu::perdu()
{  for(unsigned int i(0);i<_grille1.max_largeur();i++){
            if(_grille1(i,0)!=t_colors::empty_cell)
                return  true;
    }
    return false;
}

void jeu::deplacer_viseur(tdirection dir)
{   switch (dir) {
    case tdirection::bas:{
        _viseur.setY1(_viseur.y1()+1);
        _viseur.setY2(_viseur.y2()+1);
    }
    case tdirection::haut:{
        _viseur.setY1(_viseur.y1()-1);
        _viseur.setY2(_viseur.y2()-1);
    }
    case tdirection::gauche:{
        _viseur.setX1(_viseur.x1()+1);
        _viseur.setX2(_viseur.x2()+1);
    }
    case tdirection::droite:{
        _viseur.setX1(_viseur.x1()-1);
        _viseur.setX2(_viseur.x2()-1);

    }
    }
}
