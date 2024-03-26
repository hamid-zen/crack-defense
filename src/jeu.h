#pragma once
#include "grid.h"
#include "cell.h"
#include "viseur.h"
#include <algorithm>
#include <iostream>

enum class t_direction{
    haut,
    bas,
    gauche,
    droite
};


class jeu{

public:
    jeu(coordonne _max_hauteur=12,coordonne _max_largeur=6,int colors=4);
    bool perdu();
    void deplacer_viseur(t_direction dir);
    void afficher() const;

private:
    grid _grille;
    viseur _viseur;
};


