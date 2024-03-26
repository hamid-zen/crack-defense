#include "jeu.h"

jeu::jeu(coordonne _max_hauteur, coordonne _max_largeur, int colors)
    :_grille(_max_hauteur,_max_largeur,colors),_viseur(_max_largeur/2,_max_hauteur/2,_max_largeur/2,_max_hauteur/2+1){ _grille.init(); /* TODO: Enlever */}

bool jeu::perdu()
{  for(unsigned int i(0);i<_grille.max_largeur();i++){
            if(_grille(i,0)!=t_colors::empty_cell)
                return  true;
    }
    return false;
}

void jeu::deplacer_viseur(t_direction dir)
{   switch (dir) {
    case t_direction::bas:{
        _viseur.setY1(_viseur.y1()+1);
        _viseur.setY2(_viseur.y2()+1);
    }
    case t_direction::haut:{
        _viseur.setY1(_viseur.y1()-1);
        _viseur.setY2(_viseur.y2()-1);
    }
    case t_direction::gauche:{
        _viseur.setX1(_viseur.x1()+1);
        _viseur.setX2(_viseur.x2()+1);
    }
    case t_direction::droite:{
        _viseur.setX1(_viseur.x1()-1);
        _viseur.setX2(_viseur.x2()-1);

    }
    }
}

void jeu::afficher() const
{
    for (unsigned int j(0);j<_grille.max_hauteur();j++){
        std::cout << std::endl;
        for(unsigned int i(0);i<_grille.max_largeur();i++){
            if ((_viseur.x1() == i && _viseur.y1() == j) || (_viseur.x2() == i && _viseur.y2() == j)){
                std::cout<<"|F";
                continue;
            }
            if( _grille(i, j)==t_colors::empty_cell){
                std::cout<<"| ";
            }
            else{
                std::cout << "|" << toString_color(_grille(i, j));
            }
        }
        std::cout << "|";
    }
    std::cout << "\n"<<" ";
    for(unsigned int k(0);k<_grille.max_largeur();k++){
        std::cout<<"_"<<" ";
    }
    std::cout<<std::endl;
    for(unsigned int i(0);i<_grille.max_largeur();i++){
        if( _grille(i, _grille.max_hauteur())==t_colors::empty_cell){
            std::cout<<"| ";
        }
        else{
            std::cout << "|" << toString_color(_grille(i, _grille.max_hauteur()));
        }
    }
    std::cout<<"|"<<std::endl;
}
