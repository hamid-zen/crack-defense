#include "case.h"

cell::cell(t_colors color, coordonne col, coordonne lig)
    : _color(color), _colonne(col), _ligne(lig), _y(lig){}

cell::cell(t_colors color, coordonne col, coordonne lig, float y)
    : _color(color), _colonne(col), _ligne(lig), _y(y) {}

t_colors cell::color() const
{
    return _color;
}

std::string cell::toString_color() {
    switch (_color) {
        case t_colors::bleu: return "b";
        case t_colors::rose: return "r";
        case t_colors::jaune: return "j";
        case t_colors::orange: return "o";
        default: return "";
    }
}
