#include <iostream>
#include "src/grid.h"
#include "src/jeu.h"
using namespace std;

//TODO: tout traduire en une seule langue
int main(){
 srand(6);
    jeu j; 
    j.deplacer_viseur(t_direction::bas);
    j.changer_sense_viseur();
    j.afficher();
    j.echanger_cases_viseur();
    auto position (j.getcase1viseur()); //on recupere la position de la premiere case pour faire glisser la colone apres
    auto position1(j.getcase2viseur()); //on recupere la position de la deuxiemme case 

    j.deplacer_viseur(t_direction::haut);//pour avoir de la visibilité
    j.deplacer_viseur(t_direction::haut);
    j.afficher();
    j.faire_glisser_colone(position.first);
    j.afficher();
    j.faire_tomber(position1.first,position1.second);
        j.afficher();

    return 0;}
