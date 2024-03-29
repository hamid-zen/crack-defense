#include <catch2/catch_test_macros.hpp>
#include "../src/game.h"

TEST_CASE("Echange_case", "test") {
    t_colors couleur1;
    t_colors couleur2;
    mysrand(42);
    game g;
    g.rotate_target();
    g.move_target(t_direction::down);
    g.move_target(t_direction::down);
    couleur1=g(g.getcell1target());
    couleur2=g(g.getcell2target());

    REQUIRE( g.switch_cells_target()==true);
    REQUIRE(couleur1== g(g.getcell2target())); //la couleur de la premiere case devient celle de la 2eme
    REQUIRE(couleur2== g(g.getcell1target()));
}

TEST_CASE("Alignement_horizontale", "[alignement][test]") {
    mysrand(56);
    game g;
    g.move_target(t_direction::right);
    g.move_target(t_direction::down);
    g.move_target(t_direction::down);
    g.switch_cells_target();
    g.move_target(t_direction::up);
    g.move_target(t_direction::up);

    std::vector<position> vec = g.alignment();
    REQUIRE(vec.size()== 3); //le vecteur devrait contenir les 3 posisition des cases qui forme l'alignement
    REQUIRE(g(vec[0])== g(vec[1]) );
    REQUIRE(g(vec[0])== g(vec[2])) ; // et ces trois cases devrait avoir la meme couleur
    REQUIRE(g(vec[0]) == t_colors::blue); //et devrait etre la couleur rouge
}

TEST_CASE("Alignement_verticale", "[alignement][test]") {
    mysrand(3);
    game g;
    g.rotate_target();
    g.move_target(t_direction::right);
    g.move_target(t_direction::down);
    g.move_target(t_direction::down);
    g.move_target(t_direction::down);
    g.switch_cells_target();
    g.move_target(t_direction::up);
    g.move_target(t_direction::up);

    std::vector<position> vec = g.alignment();
    REQUIRE(vec.size()== 3); //le vecteur devrait contenir les 3 posisition des cases qui forme l'alignement
    REQUIRE(g(vec[0])== g(vec[1]) );
    REQUIRE(g(vec[0])== g(vec[2])) ; // et ces trois cases devrait avoir la meme couleur
    REQUIRE(g(vec[0]) == t_colors::pink); //et devrait etre la couleur rouge
}

TEST_CASE("estVertical_estHorizontal", "[test]")
{
    target t1(position(3, 6), position(3, 5));
    REQUIRE(t1.isVertical());
    REQUIRE(!t1.isHorizontal());

    target t2(position(3, 6), position(4, 6));
    REQUIRE(!t2.isVertical());
    REQUIRE(t2.isHorizontal());
}

TEST_CASE("ou_tomber", "[tomber][test]") {
    mysrand(5);
    game g;
    bool fait;
    g.show();
    g.rotate_target();
    g.move_target(t_direction::up);
    g.move_target(t_direction::left);
    g.move_target(t_direction::left);
    g.show();
    fait=g.switch_cells_target();
    REQUIRE(fait==true);
    REQUIRE(g.drop_position(g.getcell2target()) == position(2, 10));
} 

TEST_CASE("bounds", "[test]")
{
    mysrand(5);
    game g;
    for (size_t i = 0; i < 3; i++)
        g.move_target(t_direction::right);
    
    REQUIRE(g.getcell1target() == position(5, 6));
    REQUIRE(g.getcell2target() == position(5, 7));
    g.rotate_target(); // rotation pas possible car on est bloqué par la gauche
    REQUIRE(g.getcell1target() == position(5, 6));
    REQUIRE(g.getcell2target() == position(5, 7));
    for (size_t i = 0; i < 7; i++)
        g.move_target(t_direction::up);
    REQUIRE(g.getcell1target() == position(5, 0));
    REQUIRE(g.getcell2target() == position(5, 1));
    g.move_target(t_direction::left);
    g.rotate_target();
    for (size_t i = 0; i < 11; i++)
        g.move_target(t_direction::down);
    REQUIRE(g.getcell1target() == position(4, 11));
    REQUIRE(g.getcell2target() == position(5, 11));
    g.rotate_target(); // rotation impossible
    REQUIRE(g.getcell1target() == position(4, 11));
    REQUIRE(g.getcell2target() == position(5, 11));
}