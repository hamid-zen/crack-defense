#include <iostream>
#include "src/grid.h"
#include "src/jeu.h"
using namespace std;

int main()
{
    srand(time(0));
    jeu j;
    std::cout << "Avant deplacement\n";
    j.afficher();
    j.deplacer_viseur(t_direction::droite);
    j.deplacer_viseur(t_direction::droite);
    j.deplacer_viseur(t_direction::droite);
    std::cout << "Apres deplacement bas\n";
    j.afficher();

    return 0;
}
