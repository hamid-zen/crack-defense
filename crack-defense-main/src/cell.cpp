#include "cell.h"


cell::cell(t_colors color)
    : _color(color) {}

t_colors cell::color() const
{
    return _color;
}

void cell::setColor(t_colors newColor)
{
    _color = newColor;
}

std::string toString_color(t_colors couleur)
{
    switch (couleur) {
    case t_colors::bleu: return "b";
    case t_colors::rose: return "r";
    case t_colors::jaune: return "j";
    case t_colors::orange: return "o";
    default: return "";
    }
}
