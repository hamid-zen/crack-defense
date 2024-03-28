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

TEST_CASE("estVertical_estHorizontal", "[test]")
{
    viseur v1(3, 6, 3, 5);
    REQUIRE(v1.estVerticale());
    REQUIRE(!v1.estHorizontale());

    viseur v2(3, 6, 4, 6);
    REQUIRE(!v2.estVerticale());
    REQUIRE(v2.estHorizontale());
}

TEST_CASE("setSense", "[test]")
{
    viseur v1(3, 6, 3, 5);
    REQUIRE(v1.estVerticale());
    REQUIRE(!v1.estHorizontale());

    v1.setSense();
    REQUIRE(v1.x1() == 3);
    REQUIRE(v1.y1() == 6);
    REQUIRE(v1.x2() == 4);
    REQUIRE(v1.y2() == 6);

    v1.setSense();
    REQUIRE(v1.x1() == 3);
    REQUIRE(v1.y1() == 6);
    REQUIRE(v1.x2() == 3);
    REQUIRE(v1.y2() == 7);
}

TEST_CASE("changer_sense_viseur", "[test]")
{
    srand(5);
    jeu j;

    // On check si il est bien a la bonne case
    REQUIRE(j.getcase1viseur() == std::make_pair(static_cast<unsigned int>(3), static_cast<unsigned int>(6)));
    REQUIRE(j.getcase2viseur() == std::make_pair(static_cast<unsigned int>(3), static_cast<unsigned int>(7)));

    // On change de sense
    j.changer_sense_viseur();
    REQUIRE(j.getcase1viseur() == std::make_pair(static_cast<unsigned int>(3), static_cast<unsigned int>(6)));
    REQUIRE(j.getcase2viseur() == std::make_pair(static_cast<unsigned int>(4), static_cast<unsigned int>(6)));

    // On check qu'il revient bien a la position de base
    j.changer_sense_viseur();
    REQUIRE(j.getcase1viseur() == std::make_pair(static_cast<unsigned int>(3), static_cast<unsigned int>(6)));
    REQUIRE(j.getcase2viseur() == std::make_pair(static_cast<unsigned int>(3), static_cast<unsigned int>(7)));

    // On deplace tout a droite pour check si on peut faire un switch

    // Le switch ne devrait pas marcher
    j.deplacer_viseur(t_direction::droite);
    j.deplacer_viseur(t_direction::droite);
    REQUIRE(j.getcase1viseur() == std::make_pair(static_cast<unsigned int>(5), static_cast<unsigned int>(6)));
    REQUIRE(j.getcase2viseur() == std::make_pair(static_cast<unsigned int>(5), static_cast<unsigned int>(7)));
    j.changer_sense_viseur();
    REQUIRE(j.getcase1viseur() == std::make_pair(static_cast<unsigned int>(5), static_cast<unsigned int>(6)));
    REQUIRE(j.getcase2viseur() == std::make_pair(static_cast<unsigned int>(5), static_cast<unsigned int>(7)));

    // On check horizontal=>vertical
    // On se deplace tout en bas en horizontal et ducoup convertir en vertical ne devrait pas marcher
    j.deplacer_viseur(t_direction::gauche);
    j.changer_sense_viseur();
    j.deplacer_viseur(t_direction::bas);
    j.deplacer_viseur(t_direction::bas);
    j.deplacer_viseur(t_direction::bas);
    j.deplacer_viseur(t_direction::bas);
    j.deplacer_viseur(t_direction::bas); 
    REQUIRE(j.getcase1viseur() == std::make_pair(static_cast<unsigned int>(4), static_cast<unsigned int>(11)));
    REQUIRE(j.getcase2viseur() == std::make_pair(static_cast<unsigned int>(5), static_cast<unsigned int>(11)));
    j.changer_sense_viseur();
    REQUIRE(j.getcase1viseur() == std::make_pair(static_cast<unsigned int>(4), static_cast<unsigned int>(11)));
    REQUIRE(j.getcase2viseur() == std::make_pair(static_cast<unsigned int>(5), static_cast<unsigned int>(11)));
}

TEST_CASE("faire_tomber", "[tomber][test]") {
    srand(5);
    jeu j;
    j.changer_sense_viseur();
    j.deplacer_viseur(t_direction::gauche);
    j.deplacer_viseur(t_direction::haut);
    j.echanger_cases_viseur();
    j.deplacer_viseur(t_direction::haut);
    auto position = j.faire_tomber(3,5);
    REQUIRE(position.first == 3);
    REQUIRE(position.second == 7);
}
TEST_CASE("faire_glisser_colonne", "[glisser][test]") {
    srand(6);
    jeu j;
    j.changer_sense_viseur();
    for(int i(0);i<3;i++){
        j.deplacer_viseur(t_direction::gauche);
    }
    for(int i(0);i<2;i++){
        j.deplacer_viseur(t_direction::bas);
    }
    j.echanger_cases_viseur();
    j.deplacer_viseur(t_direction::bas); 
    j.deplacer_viseur(t_direction::haut);
    coordonne xvide = j.getcase2viseur().first ;
    coordonne yvide = j.getcase2viseur().second ;
    std::vector<t_colors> v;
    coordonne jtemp = yvide;
    while(j.getColor({xvide,jtemp-1})!=t_colors::empty_cell){
        v.push_back(j.getColor({xvide,jtemp-1}));
        jtemp -- ;

    }
    j.faire_glisser_colone(xvide);
    jtemp=0;
    while(j.getColor({xvide,yvide})!=t_colors::empty_cell){
        REQUIRE(v[jtemp]==j.getColor({xvide,yvide}));
        jtemp++;
        yvide--;
    }
}
