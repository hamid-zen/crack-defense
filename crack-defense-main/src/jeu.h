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
    void echanger_cases_viseur();
    std::pair<unsigned int, unsigned int> faire_tomber(coordonne x, coordonne y);
    std::vector<std::pair<unsigned int, unsigned int> >  alignement_vertical();
    std::vector<std::pair<unsigned int, unsigned int> > alignement_horizontale();
    std::vector<std::pair<unsigned int, unsigned int> >  alignement();
    std::pair<coordonne,coordonne> getcase1viseur() const; //recupere la position de la premiere case du viseur
    std::pair<coordonne,coordonne> getcase2viseur() const;
    t_colors getColor(std::pair<coordonne,coordonne> pair) const; //recupere la couleur de la case qui a pour position pair
    void changer_sense_viseur();
private:
    grid _grille;
    viseur _viseur;
};


