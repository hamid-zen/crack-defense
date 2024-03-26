#pragma once
#include "cell.h"


/*
 * Dans cette classe on stocke la position de la case gauche du viseur
 */
class viseur {
public:
    viseur(coordonne x, coordonne y);

    coordonne x() const;
    void setX(coordonne newX);

    coordonne y() const;
    void setY(coordonne newY);

private:
    coordonne _x;
    coordonne _y;
};
