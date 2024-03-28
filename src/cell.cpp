#include "cell.h"


cell::cell(t_colors color)
    : _color(color),_dx(0),_dy(0) {}

t_colors cell::color() const
{
    return _color;
}

void cell::setColor(t_colors newColor)
{
    _color = newColor;
}

std::string toString_color(t_colors color)
{
    switch (color) {
    case t_colors::blue: return "b";
    case t_colors::pink: return "p";
    case t_colors::yellow: return "y";
    case t_colors::orange: return "o";
    default: return "";
    }
}
