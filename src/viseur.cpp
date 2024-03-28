#include "viseur.h"

viseur::viseur(coordonne x1, coordonne y1,coordonne x2, coordonne y2) :
    _x1(x1),
    _y1(y1),
    _x2(x2),
    _y2(y2){}

void viseur::setSense(){
    if(estVerticale() ) //on evrifie les bounds avant de changer le snese du visuer
    {
        _x2=_x1+1;
        _y2=_y1;
    }
     else {
        _x2=_x1;
        _y2=_y1+1;
     }
}

coordonne viseur::y2() const
{
    return _y2;
}

void viseur::setY2(const coordonne &y2)
{
    _y2 = y2;
}

coordonne viseur::x2() const
{
    return _x2;
}

void viseur::setX2(const coordonne &x2)
{
    _x2 = x2;
}

coordonne viseur::y1() const
{
    return _y1;
}

void viseur::setY1(const coordonne &y1)
{
    _y1 = y1;
}

coordonne viseur::x1() const
{
    return _x1;
}

void viseur::setX1(const coordonne &x1)
{
    _x1 = x1;
}

bool viseur::estVerticale() const{
    return (_x1==_x2);
}

bool viseur::estHorizontale()  const {
    return _y1==_y2;
}
