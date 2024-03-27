#include <iostream>
#include "src/grid.h"
#include "src/jeu.h"
using namespace std;

//TODO: tout traduire en une seule langue
int main()
{
    srand(42);
    jeu j;
    std::cout << "avant echange: \n";
    j.deplacer_viseur(t_direction::droite);
    j.afficher();
    std::cout << "avant echange (viseur sur les cases): \n";
    j.deplacer_viseur(t_direction::gauche);
    j.afficher();
    j.echanger_cases_viseur();
    std::cout << "apres echange: \n";
    j.deplacer_viseur(t_direction::droite);
    j.afficher();
    return 0;
}
