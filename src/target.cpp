#include "target.h"

target::target(position const & p1,position const & p2) :
    _p1(p1),
    _p2(p2)
    {}

void target::setSense(){
    if(isVertical() ) //on evrifie les bounds avant de changer le snese du visuer
    {
        _p2.setx(_p1.x()+1);
        _p2.sety(_p1.y());
    }
     else {
        _p2.setx(_p1.x());
        _p2.sety(_p1.y()+1);
     }
}

cordinate target::y2() const
{
    return _p2.y();
}

void target::setY2(const cordinate &y2)
{
   _p2.sety(y2);
}

cordinate target::x2() const
{
    return _p2.x();
}

void target::setX2(const cordinate &x2)
{
   _p2.setx(x2);
}

cordinate target::y1() const
{
    return _p1.y();
}

void target::setY1(const cordinate &y1)
{
    _p1.sety(_p1.y());
}

cordinate target::x1() const
{
    return _p1.x();
}

void target::setX1(const cordinate &x1)
{
   _p1.setx(x1);
}

bool target::isVertical() const{
    return (_p1.x()==_p2.x());
}

bool target::isHorizontal()  const {
    return (_p1.y()==_p2.y());}
