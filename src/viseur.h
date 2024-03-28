#pragma once
#include "cell.h"



/*
 * Dans cette classe on stocke la position de la case gauche du viseur
 */
class viseur {
public:
    viseur(coordonne x1, coordonne y1,coordonne x2, coordonne y2);

    coordonne x1() const;
    void setX1(const coordonne &x1);

    coordonne y1() const;
    void setY1(const coordonne &y1);

    coordonne x2() const;
    void setX2(const coordonne &x2);

    coordonne y2() const;
    void setY2(const coordonne &y2);

    void setSense();
    bool estVerticale() const;
    bool estHorizontale()  const ;

private:
    coordonne _x1;
    coordonne _y1;
    coordonne _x2;
    coordonne _y2;

};
