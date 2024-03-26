#include "grid.h"
#include "cell.h"
#include <cstdlib>
#include <ctime>
#include <iostream>


grid::grid(coordonne hauteur, coordonne largeur,int colors)
    : _board(hauteur*largeur),_hauteur(hauteur),_largeur(largeur),nbr_colors(colors){}

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
    return ((i-1>=0 && _board[j*Max_largeur+i-1] != nullptr && _board[j*Max_largeur+i-1]->color()==clr) ||
            (j-1>=0 && _board[(j-1)*Max_largeur+i] != nullptr && _board[(j-1)*Max_largeur+i]->color()==clr) ||
            (i+1<Max_largeur && _board[j*Max_largeur+i+1] != nullptr && _board[j*Max_largeur+i+1]->color()==clr) ||
            (j+1<Max_hauteur && _board[(j+1)*Max_largeur+i] != nullptr && _board[(j+1)*Max_largeur+i]->color()==clr )) ;

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
void grid::init()
{   for(unsigned int i(0);i<Max_largeur;i++){ //colone
        // pour chaque colone on genere un nbr de case pour la colonne
        int nbr=nombreAleatoire(Max_hauteur/2)+1; //nbr aleatoire entre 1 et 7 si MAx_hauteur=12
        for(unsigned int j(Max_hauteur-nbr);j<Max_hauteur;j++){ //ligne
            t_colors couleur;
            do{
                couleur=couleurAleatoire();
            }while(adjacent(i,j,couleur));

            _board[i+j*Max_largeur]=std::make_unique<cell>(couleur,i,j);
        }

    }
}

void grid::afficher() const
{
    for (unsigned int j(0);j<Max_hauteur;j++){
        std::cout << std::endl;
        for(unsigned int i(0);i<Max_largeur;i++){
            if( _board[i+j*Max_largeur]==nullptr){
                std::cout<<"| ";
            }
            else{
                std::cout << "|" << _board[i+j*Max_largeur]->toString_color();
            }
        }
        std::cout << "|";
    }
    std::cout << "\n";
}

t_colors grid::operator()(coordonne x, coordonne y)
{
    if(x < Max_largeur && y < Max_hauteur &&_board[ x + y *Max_largeur ])
        return _board[ x + y * Max_largeur ] -> color();
    else return t_colors::empty_cell;

}
