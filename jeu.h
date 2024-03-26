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
   std::pair<unsigned int,unsigned int> faire_tomber(coordonne x,coordonne y ) ; //retourne endposition de la case qui glisse
 std::vector<std::pair<unsigned int,unsigned int>> alignement_vertical();
    std::vector<std::pair<unsigned int,unsigned int>> alignement_horizontale();
    std::vector<std::pair<unsigned int,unsigned int>> alignement(); //retourne l'ensemble des position qui forme le premier alignement trouvé

private:
    grid _grille1;
    viseur _viseur;
    int _score;

};


