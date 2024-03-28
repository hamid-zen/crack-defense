#pragma once
#include "cell.h"
#include "rand.h" 
#include <iostream>

using t_mat = std::vector<std::unique_ptr<cell>>;
using t_number_color=uint16_t ;

class grid {
public:
    grid( cordinate _max_height=12, cordinate _max_width=6,t_number_color colors=4);
    t_colors randomColor() const;
    bool neighbours_same_color(position p,t_colors clr ) const;
    void init();
    t_colors operator() (position p) const;
    cordinate max_height() const;
    cordinate max_width() const;
    void switch_cell(position p1, position p2);
    void place_cell(cell c,position p);
    void delete_cell(position p);
private:
    t_mat _board;
    cordinate _max_height;
    cordinate _max_width; //pour pouvoir le modifier pour chaque partie 
    //doit etre changer
    t_number_color nbr_colors; //pour pouvoir le modifier pour chaque partie et en fonction de la difficulté
};

int nombreAleatoire(int k);
