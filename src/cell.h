#pragma once
#include <string>
#include <vector>
#include <memory>


const unsigned int nombre_couleurs=4;
using coordonne =unsigned int ;

enum class t_colors {
    bleu , rose,jaune,orange,empty_cell
};

std::string toString_color(t_colors couleur);

class cell {

public:
    cell(t_colors color) ;

    t_colors color() const;


    void setColor(t_colors newColor);

private:
    t_colors _color;

};
