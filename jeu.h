#pragma once
#include "grid.h"
#include "viseur.h"

enum class tdirection{
    haut,
    bas,
    gauche,
    droite
};


class jeu{

public:
    jeu(coordonne _max_hauteur=12,coordonne _max_largeur=6,int colors=4);
    bool perdu();
    void deplacer_viseur(tdirection dir);

private:
    grid _grille1;
    viseur _viseur;

};


