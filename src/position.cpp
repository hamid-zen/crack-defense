#include "position.h"

position::position(coordonnee x, coordonnee y)
	:_x(x), _y(y) {
}

// Il est inutile de définir ce constructeur par recopie car le code que nous
// écrivons ici n'est rien d'autre que le comportement du constructeur par
// recopie implicite.
/*
position::position(position const & p)
	:_x(p._x), _y(p._y) {
}
*/

coordonnee position::x() const {
	return _x;
}

coordonnee position::y() const {
	return _y;
}

void position::setx(coordonnee x) {
	_x = x;
}

void position::sety(coordonnee y) {
	_y = y;
}

bool position::comparaison(position const & p) const {
	return (_x == p._x) && (_y == p._y);
}
