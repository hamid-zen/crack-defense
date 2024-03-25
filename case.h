#pragma once
#include <string>
#include <vector>
#include <memory>

const unsigned int Max_hauteur=12;
const unsigned int Max_largeur=6;
const unsigned int nombre_couleurs=4;
using coordonne =unsigned int ;

enum class t_colors {
    bleu , rose,jaune,orange
};

class cell {

public:
    cell(t_colors color,coordonne col,coordonne lig) ;
    cell(t_colors color,coordonne col,coordonne lig, float y) ;

    t_colors color() const;

    std::string toString_color();

private:
    t_colors _color;
    coordonne _colonne;
    coordonne _ligne;
    float _y;

};
