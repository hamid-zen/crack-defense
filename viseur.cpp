#include "viseur.h"

viseur::viseur(coordonne x, coordonne y) :
    _x(x),
    _y(y)
{}

coordonne viseur::x() const
{
    return _x;
}

void viseur::setX(coordonne newX)
{
    _x = newX;
}

coordonne viseur::y() const
{
    return _y;
}

void viseur::setY(coordonne newY)
{
    _y = newY;
}
