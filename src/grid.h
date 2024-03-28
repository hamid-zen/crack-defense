#pragma once
#include "cell.h"
#include "rand.h" 
#include <iostream>

using t_mat = std::vector<std::unique_ptr<cell>>;
using t_number_color=uint16_t ;

class grid {
public:
    grid(coordonne _max_hauteur=12,coordonne _max_largeur=6,int colors=4);
    t_colors randomColor() const;
    bool neighbours_same_color(coordonne i,coordonne j,t_colors clr ) const;
    void init();
    t_colors operator() (coordonne x, coordonne y) const;
    coordonne max_hauteur() const;
    coordonne max_largeur() const;
    float taille_ligne_incomplete() const;
    void echange(coordonne x1, coordonne y1, coordonne x2, coordonne y2);
    void place_cell(cell c,position p);
    void delete_cell(position p);
private:
    t_mat _board;
    coordonne _max_hauteur;
    coordonne _max_largeur; //pour pouvoir le modifier pour chaque partie
    float _taille_ligne_incomplete; //la hauteur de la ligne incompletes 
    //doit etre changer
    t_number_color nbr_colors; //pour pouvoir le modifier pour chaque partie et en fonction de la difficulté
};

int nombreAleatoire(int k);
