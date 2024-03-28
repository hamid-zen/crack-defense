#pragma once
#include <string>
#include <vector>
#include <memory>
#include <cstdint>
#include "position.h"


const uint16_t  nombre_couleurs=4;
using cordinate =uint16_t ;
using t_int=int16_t;

enum class t_colors {
    blue, pink, yellow, orange, empty_cell
};

std::string toString_color(t_colors color);

class cell {

public:
    cell(t_colors color) ;

    t_colors color() const;


    void setColor(t_colors newColor);

private:
    t_colors _color;
    t_int _dx;
    t_int _dy;
};
