#pragma once
#include <string>
#include <vector>
#include <memory>
#include <cstdint>


const uint16_t  nombre_couleurs=4;
using coordonne =uint16_t ;

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
