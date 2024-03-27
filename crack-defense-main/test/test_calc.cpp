#include <catch2/catch_test_macros.hpp>
#include "../src/jeu.h"

TEST_CASE("Echange_case", "test") {
    t_colors couleur1;
    t_colors couleur2;
    srand(42);
        jeu j;
        j.deplacer_viseur(t_direction::droite); //viseur sur o-r
        couleur1=j.getColor(j.getcase1viseur());
        couleur2=j.getColor(j.getcase2viseur());
        j.echanger_cases_viseur(); //sensé etre r-o maintenant
        REQUIRE(couleur1== j.getColor(j.getcase2viseur())); //la couleur de la premiere case devient celle de la 2eme
        REQUIRE(couleur2== j.getColor(j.getcase1viseur()));
}

TEST_CASE("Alignement_horizontale", "[alignement][test]") {
    std::vector<std::pair<unsigned int, unsigned int> > vec;
    srand(12);
        jeu j;
        j.deplacer_viseur(t_direction::gauche);
        j.deplacer_viseur(t_direction::gauche);
        for(int i(1);i<5;i++)
            j.deplacer_viseur(t_direction::bas);

        j.echanger_cases_viseur(); //echange le r-o et forme un alignement de 3
        vec=j.alignement();
        REQUIRE(vec.size()== 3); //le vecteur devrait contenir les 3 posisition des cases qui forme l'alignement
        REQUIRE(j.getColor(vec[0])== j.getColor(vec[1]) );
        REQUIRE(j.getColor(vec[0])== j.getColor(vec[2])) ; // et ces trois cases devrait avoir la meme couleur
        REQUIRE(j.getColor(vec[0])==t_colors::rose); //et devrait etre la couleur rouge
}


TEST_CASE("Alignement_verticale", "[alignement][test]") {
    std::vector<std::pair<unsigned int, unsigned int> > vec;
    srand(5);
        jeu j;
        j.deplacer_viseur(t_direction::gauche);
        j.deplacer_viseur(t_direction::gauche);
        j.deplacer_viseur(t_direction::bas);
        j.echanger_cases_viseur();
        for(int i(1);i<=3;i++)
            j.deplacer_viseur(t_direction::bas);
   
        j.echanger_cases_viseur();
        j.deplacer_viseur(t_direction::droite);
    vec=j.alignement();
    REQUIRE(vec.size()== 3); 
    REQUIRE(j.getColor(vec[0])== j.getColor(vec[1]) );
    REQUIRE(j.getColor(vec[0])== j.getColor(vec[2])) ; //les 3 cases devraient avoir la meme couleur
    REQUIRE(j.getColor(vec[0])==t_colors::rose); //et devrait etre la couleur rouge
}