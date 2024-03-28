#pragma once
#include<cstdint>

using coordonnee = uint16_t ;
using taille = uint16_t ;
using delta = uint16_t ;


class position {
public:
	position(coordonnee x, coordonnee y);
	// On peut déclarer explicitement un constructeur par recopie et donner
	// son code (cf. fichier .cc), le déclarer "=default" comme ici, ou
	// l'omettre (pour profiter du constructeur par recopie implicite).
	position(position const & p) =default;
	coordonnee x() const;
	coordonnee y() const;
	void setx(coordonnee x);
	void sety(coordonnee y);
	bool comparaison(position const & p) const;
private:
	coordonnee _x;
	coordonnee _y;
};

