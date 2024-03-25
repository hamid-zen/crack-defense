#pragma once
#include "case.h"

using t_mat = std::vector<std::unique_ptr<cell>>;

class grid {
public:
    grid(coordonne hauteur=12,coordonne largeur=6,int colors=4);
    t_colors couleurAleatoire() const;
    bool adjacent(coordonne i,coordonne j,t_colors clr ) const;

    void init();

    void afficher() const;

private:
    t_mat _board;
    coordonne _hauteur;
    coordonne _largeur; //pour pouvoir le modifier pour chaque partie
    int nbr_colors; //pour pouvoir le modifier pour chaque partie et en fonction de la difficulté
};

int nombreAleatoire(int k);
