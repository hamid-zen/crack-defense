#pragma once
#include "grid.h"
#include "cell.h"
#include "viseur.h"
#include <algorithm>
#include <iostream>
#include "position.hh"

enum class t_direction{
    haut,
    bas,
    gauche,
    droite
};


class jeu{

public:
    jeu(coordonne _max_hauteur=12,coordonne _max_largeur=6,int colors=4);
    bool is_lost();
    void move_target(t_direction dir);
    void show() const;
    void switch_cells_target();
    position drop_position(coordonne x, coordonne y) const ;
    void drop(coordonne x,coordonne y);
    std::vector<position>  vertical_alignment();
    std::vector<position> horizontal_alignment();
    std::vector<position>  alignment();
    position getcell1target() const; //recupere la position de la premiere case du viseur
    position getcell2target() const;
    t_colors getColor(position const & p) const; //recupere la couleur de la case qui a pour position pair
    t_colors operator()(position const & p)const;
    void rotate_target();
    void slideColumn(coordonne x);
private:
    grid _grille;
    viseur _viseur;
};


