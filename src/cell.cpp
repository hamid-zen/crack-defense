
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
    case t_colors::sky_blue: return "s";
    case t_colors::white: return "w";
    case t_colors::purple: return "p";
    case t_colors::green: return "g";
    case t_colors::garbage: return "m";
    case t_colors::all: return "a";
    default: return "";
    }
}
delta cell::dx() const{
    return _dx;
}
delta cell::dy() const {
    return _dy;
}

void cell::setDx(delta newDx)
{
    _dx = newDx;
}

void cell::setDy(delta newDy)
{
    _dy = newDy;
}

malusCell::malusCell(t_colors color,bool const &  bfr,bool const & aftr) 
    : cell(color),_before(bfr),_after(aftr){}
