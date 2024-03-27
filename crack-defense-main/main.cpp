#include <iostream>
#include "src/grid.h"
#include "src/jeu.h"
using namespace std;

//TODO: tout traduire en une seule langue
int main()
{
    srand(5);
    jeu j;
    std::cout << "avant deplacement: \n";
    j.afficher();
    j.deplacer_viseur(t_direction::gauche);
    j.deplacer_viseur(t_direction::gauche);
    j.deplacer_viseur(t_direction::bas);
    j.echanger_cases_viseur();
    for(int i(1);i<=3;i++)
        j.deplacer_viseur(t_direction::bas);
   
    j.echanger_cases_viseur();
j.deplacer_viseur(t_direction::droite);
           j.afficher();


    return 0;
}
