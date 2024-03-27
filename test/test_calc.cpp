#include <catch2/catch_test_macros.hpp>
#include "../src/jeu.h"

TEST_CASE("Echange_case", "test") {
    t_colors couleur1;
    t_colors couleur2;
    srand(42);
        jeu j;
        j.deplacer_viseur(t_direction::droite); //viseur sur o-r
        couleur1=j.getColor(j.getcase1viseur()); //on stocke la couleur de la premiere case
        couleur2=j.getColor(j.getcase2viseur());
        j.echanger_cases_viseur(); //sensé etre r-o maintenant
        REQUIRE(couleur1== j.getColor(j.getcase2viseur())); //la couleur de la premiere case devient celle de la 2eme
        REQUIRE(couleur2== j.getColor(j.getcase1viseur()));
}
