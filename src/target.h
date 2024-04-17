#pragma once
#include "cell.h"



/*
 * Dans cette classe on stocke la position de la case gauche du viseur
 */
class target {
public:
    target(position const & p1,position const & p2);

    cordinate x1() const;
    void setX1(const cordinate &x1);

    cordinate y1() const;
    void setY1(const cordinate &y1);

    cordinate x2() const;
    void setX2(const cordinate &x2);

    cordinate y2() const;
    void setY2(const cordinate &y2);

    void setSense();
    bool isVertical() const;
    bool isHorizontal()  const ;

private:
    position _p1;
    position _p2;


};
