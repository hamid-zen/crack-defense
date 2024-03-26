#include "grid.h"
#include "cell.h"
#include <cstdlib>
#include <ctime>
#include <iostream>


grid::grid(coordonne hauteur, coordonne largeur,int colors)
    : _board((hauteur+1)*largeur),_max_hauteur(hauteur),_max_largeur(largeur),_taille_ligne_incomplete(0),nbr_colors(colors){}

/**
 * @brief grid::couleurAleatoire
 * @return une couleur aleatoire
 */
// TODO: rajouter les autres couleurs
t_colors grid::couleurAleatoire() const
{
    int k =nombreAleatoire(nbr_colors);
    switch (k) {
    case 0:{
        return t_colors::bleu;
    }
    case 1:{
        return t_colors::jaune;
    }
    case 2:{
        return t_colors::orange;
    }
    case 3:{
        return t_colors::rose;
    }
    default:{
         return t_colors::rose;
    }
    };
}

/**
 * @brief grid::adjacent
 * @param i
 * @param j
 * @param clr
 * @return si la case ajdacente (gauce, droite, bas, haut) est de la meme couleur
 */
bool grid::adjacent(coordonne i, coordonne j, t_colors clr) const
{
    return ((i-1>=0 && _board[j*_max_largeur+i-1] != nullptr && _board[j*_max_largeur+i-1]->color()==clr) || //verif à gauche
            (j-1>=0 && _board[(j-1)*_max_largeur+i] != nullptr && _board[(j-1)*_max_largeur+i]->color()==clr) || //verif au dessus
            (i+1<_max_largeur && _board[j*_max_largeur+i+1] != nullptr && _board[j*_max_largeur+i+1]->color()==clr) || //verif à droite
            (j+1<_max_hauteur && _board[(j+1)*_max_largeur+i] != nullptr && _board[(j+1)*_max_largeur+i]->color()==clr )) ; //verif en dessous

}

/**
 * @brief nombreAleatoire
 * @param k
 * @return une nombre aleatoire entre 0 et k (inclu)
 */
int nombreAleatoire(int k) {
    return rand() % (k + 1);
}

/**
 * @brief grid::_init
 * initialise la grille
 */
void grid::init() // on initialisse une grille aleatoire de max 7 ligne (+1 ligne caché)
{   for(unsigned int i(0);i<_max_largeur;i++){ //colone
        // pour chaque colone on genere un nbr de case pour la colonne
        int nbr=nombreAleatoire((_max_hauteur+1)/2)+1; //nbr aleatoire entre  2 et 8 si MAx_hauteur=12 sachant que 1 sera caché au debut
        for(unsigned int j(_max_hauteur-nbr);j<_max_hauteur+1;j++){ //ligne
            t_colors couleur;
            do{
                couleur=couleurAleatoire();
            }while(adjacent(i,j,couleur));

            _board[i+j*_max_largeur]=std::make_unique<cell>(couleur,i,j);
        }

    }
}

void grid::afficher() const
{
    for (unsigned int j(0);j<_max_hauteur;j++){
        std::cout << std::endl;
        for(unsigned int i(0);i<_max_largeur;i++){
            if( _board[i+j*_max_largeur]==nullptr){
                std::cout<<"| ";
            }
            else{
                std::cout << "|" << _board[i+j*_max_largeur]->toString_color();
            }
        }
        std::cout << "|";
    }
    std::cout << "\n"<<" ";
    for(unsigned int k(0);k<_max_largeur;k++){
        std::cout<<"_"<<" ";
    }
    std::cout<<std::endl;
    for(unsigned int i(0);i<_max_largeur;i++){
        if( _board[i+_max_hauteur*_max_largeur]==nullptr){
            std::cout<<"| ";
        }
        else{
            std::cout << "|" << _board[i+_max_hauteur*_max_largeur]->toString_color();
        }
    }
    std::cout<<"|"<<std::endl;
}

t_colors grid::operator()(coordonne x, coordonne y)
{
    if(x < _max_largeur && y < _max_hauteur &&_board[ x + y *_max_largeur ])
        return _board[ x + y * _max_largeur ] -> color();
    else return t_colors::empty_cell;

}

float grid::taille_ligne_incomplete() const
{
    return _taille_ligne_incomplete;
}

coordonne grid::max_largeur() const
{
    return _max_largeur;
}

coordonne grid::max_hauteur() const
{
    return _max_hauteur;
}
