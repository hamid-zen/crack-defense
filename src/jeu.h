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
<<<<<<<< HEAD:src/jeu.h
    void deplacer_viseur(t_direction dir);
    void afficher() const;
========
    void deplacer_viseur(tdirection dir);
   std::pair<unsigned int,unsigned int> faire_tomber(coordonne x,coordonne y ) ; //retourne endposition de la case qui glisse
 std::vector<std::pair<unsigned int,unsigned int>> alignement_vertical();
    std::vector<std::pair<unsigned int,unsigned int>> alignement_horizontale();
    std::vector<std::pair<unsigned int,unsigned int>> alignement(); //retourne l'ensemble des position qui forme le premier alignement trouvé
>>>>>>>> b26d574d861da262d1536043d262c8054d6ef9eb:jeu.h

private:
    grid _grille;
    viseur _viseur;
<<<<<<<< HEAD:src/jeu.h
========
    int _score;

>>>>>>>> b26d574d861da262d1536043d262c8054d6ef9eb:jeu.h
};


