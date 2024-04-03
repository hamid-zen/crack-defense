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
        std::cout << "hehe1 \n";
        g.show();

    g.rotate_target();
    g.move_target(t_direction::right);
    g.move_target(t_direction::down);
    g.move_target(t_direction::down);
    g.move_target(t_direction::down);
    g.switch_cells_target();
    g.move_target(t_direction::up);
    g.move_target(t_direction::up);
    std::cout << "hehe \n";
    g.show();
    std::vector<position> vec = g.alignment();
    REQUIRE(vec.size()== 3); //le vecteur devrait contenir les 3 posisition des cases qui forme l'alignement
    REQUIRE(g(vec[0])== g(vec[1]) );
    REQUIRE(g(vec[0])== g(vec[2])) ; // et ces trois cases devrait avoir la meme couleur
    REQUIRE(g(vec[0]) == t_colors::pink); //et devrait etre la couleur rouge
}

TEST_CASE("Alignement_verticale_et_horizontale", "[alignement][test]") {
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
    g.move_target(t_direction::left);
    g.rotate_target();
    g.switch_cells_target();
    g.move_target(t_direction::left);
    g.move_target(t_direction::down);
    g.switch_cells_target();
    g.move_target(t_direction::left);
    //g.show();
    std::vector<position> vec1=g.horizontal_alignment(vec);
    REQUIRE(vec1.size()== 2); //le vecteur devrait contenir les 3 posisition des cases qui forme l'alignement
    REQUIRE(g(vec1[0])== g(vec1[1]) );
    REQUIRE(g(vec1[0]) == t_colors::pink); //et devrait etre la couleur rose
    //std::cout<<vec1[0].x()<<" "<<vec1[0].y()<<std::endl;
}
TEST_CASE("Alignement", "[alignement][test]") {
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
    g.move_target(t_direction::left);
    g.rotate_target();
    g.switch_cells_target();
    g.move_target(t_direction::left);
    g.move_target(t_direction::down);
    g.switch_cells_target();
    g.move_target(t_direction::left);
    //g.show();
    std::vector<position> vec1=g.alignment();
    std::cout<<"taille : "<<vec1.size()<<std::endl;
    REQUIRE(vec1.size()== 5); //le vecteur devrait contenir les 3 posisition des cases qui forme l'alignement
    REQUIRE(g(vec1[0])== g(vec1[1]) );
    REQUIRE(g(vec1[0])== g(vec1[2]) );
    REQUIRE(g(vec1[0])== g(vec1[3]) );
    REQUIRE(g(vec1[0])== g(vec1[4]) );
    REQUIRE(g(vec1[0]) == t_colors::pink); //et devrait etre la couleur rose
    //std::cout<<vec1[0].x()<<" "<<vec1[0].y()<<std::endl;
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
    std::cout << "shoowing\n";
    g.show();
    REQUIRE(g.getcell1target() == position(4, 11));
    REQUIRE(g.getcell2target() == position(5, 11));
    g.rotate_target(); // rotation impossible
    REQUIRE(g.getcell1target() == position(4, 11));
    REQUIRE(g.getcell2target() == position(5, 11));
}
TEST_CASE("max_column", "[test]")
{
    mysrand(3);
    game g;
    std::cout<<" habibi come to dubai "<<std::endl;
    g.show();
    auto vec=(g.max_column());
   // std::cout<<" x: "<<vec[0].x()<<" ,y :"<<vec[0].y()<<std::endl;

    REQUIRE(vec.size()==3);
    REQUIRE(vec[0].x()==3);
    REQUIRE(vec[1].x()==4);
    REQUIRE(vec[2].x()==5);
    REQUIRE(vec[0].y()==6);
    REQUIRE(vec[0].y()==vec[1].y());
    REQUIRE(vec[0].y()==vec[2].y());
}
