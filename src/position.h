#pragma once
#include<cstdint>

using cordinate = uint16_t ;
using size = uint16_t ;
using delta = uint16_t ;


class position {
public:
	position(cordinate x, cordinate y);
	// On peut déclarer explicitement un constructeur par recopie et donner
	// son code (cf. fichier .cc), le déclarer "=default" comme ici, ou
	// l'omettre (pour profiter du constructeur par recopie implicite).
	position(position const & p) =default;
	cordinate x() const;
	cordinate y() const;
	void setx(cordinate x);
	void sety(cordinate y);
	
	bool operator == (position const &p) const { return _x==p._x && _y==p._y;}
	bool operator != (position const &p) const { return !(*this == p) ;}
private:
	cordinate _x;
	cordinate _y;
};
