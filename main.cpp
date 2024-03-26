#include <iostream>
#include "grid.h"
#include "jeu.h"
using namespace std;

int main()
{
    srand(time(0));
    jeu j;
    std::cout << "Avant deplacement\n";
    j.afficher();
    j.deplacer_viseur(t_direction::haut);
    std::cout << "Apres deplacement\n";
    j.afficher();
    return 0;
}
