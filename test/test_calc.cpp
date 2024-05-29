#include <catch2/catch_test_macros.hpp>
#include "../src/game.h"

TEST_CASE("switch_cell", "test")
{
    t_colors couleur1;
    t_colors couleur2;
    game g;
    g.init(42);
    // g.show();
    g.rotate_target();
    g.move_target(t_direction::down);
    g.move_target(t_direction::down);
    couleur1 = g(g.getcell1target());
    couleur2 = g(g.getcell2target());

    REQUIRE(g.switch_cells_target() == true);
    REQUIRE(couleur1 == g(g.getcell2target())); // la couleur de la premiere case devient celle de la 2eme
    REQUIRE(couleur2 == g(g.getcell1target()));
}

TEST_CASE("horizontal_alignment", "[alignement][test]")
{
    game g;
    g.init(3);
    g.show();
    g.move_target(t_direction::right);
    g.move_target(t_direction::down);
    g.move_target(t_direction::down);
    g.move_target(t_direction::down);
    g.move_target(t_direction::down);
    g.switch_cells_target();

    std::vector<position> vec = g.horizontal_alignment();
    REQUIRE(vec.size() == 3); // le vecteur devrait contenir les 3 posisition des cases qui forme l'alignement
    REQUIRE(g(vec[0]) == g(vec[1]));
    REQUIRE(g(vec[0]) == g(vec[2]));      // et ces trois cases devrait avoir la meme couleur
    REQUIRE(g(vec[0]) == t_colors::blue); // et devrait etre la couleur rouge
}

TEST_CASE("vertical_alignment", "[alignement][test]")
{
    game g;
    g.init(3);
    g.show();
    g.move_target(t_direction::down);
    g.move_target(t_direction::down);
    g.move_target(t_direction::down);
    g.move_target(t_direction::left);
    g.move_target(t_direction::left);
    g.move_target(t_direction::left);
    g.rotate_target();
    g.switch_cells_target();
    g.show();
    std::vector<position> vec = g.alignment();
    REQUIRE(vec.size() == 3); // le vecteur devrait contenir les 3 posisition des cases qui forme l'alignement
    REQUIRE(g(vec[0]) == g(vec[1]));
    REQUIRE(g(vec[0]) == g(vec[2]));      // et ces trois cases devrait avoir la meme couleur
    REQUIRE(g(vec[0]) == t_colors::pink); // et devrait etre la couleur rouge
}

TEST_CASE("Alignment", "[alignement][test]")
{
    game g;
    g.init(3);
    g.move_target(t_direction::down);
    g.move_target(t_direction::down);
    g.switch_cells_target();
    g.move_target(t_direction::left);
    g.move_target(t_direction::down);
    g.rotate_target();
    g.switch_cells_target();
    g.move_target(t_direction::right);
    g.switch_cells_target();
    g.move_target(t_direction::left);
    g.move_target(t_direction::left);
    g.move_target(t_direction::left);
    g.switch_cells_target();

       g.move_target(t_direction::down);
    g.move_target(t_direction::down);
    g.show();
    //un alignement verticale combiné à un horizontale est genere en T

    g.move_target(t_direction::up);
    g.move_target(t_direction::up);
    std::vector<position> vec1 = g.alignment();
    REQUIRE(vec1.size() == 5);
    REQUIRE(g(vec1[0]) == g(vec1[1]));
    REQUIRE(g(vec1[0]) == g(vec1[2]));
    REQUIRE(g(vec1[0]) == g(vec1[3]));
    REQUIRE(g(vec1[0]) == g(vec1[4]));
    REQUIRE(g(vec1[0]) == t_colors::pink);


}

TEST_CASE("isVertical", "[test]")
{
    target t1(position(3, 6), position(3, 5));
    REQUIRE(t1.isVertical());
    REQUIRE(!t1.isHorizontal());

    target t2(position(3, 6), position(4, 6));
    REQUIRE(!t2.isVertical());
    REQUIRE(t2.isHorizontal());
}
TEST_CASE("bounds", "[test]") 
{
    game g;
    g.init(5);
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
    game g;
    g.init(3);
    g.show();
    auto vec = (g.max_column());
    REQUIRE(vec.size() == 2);
    REQUIRE(vec[0].x() == 3);
    REQUIRE(vec[1].x() == 4);
    REQUIRE(vec[0].y() == 5);
    REQUIRE(vec[0].y() == vec[1].y());
}
TEST_CASE("generate_garbage", "[test]")
{
    game g;
    g.init(3);
    std::cout << " before" << std::endl;
    g.show();
    std::vector<position*> cells_slide;
     g.add_garbage(cells_slide);
    std::cout << " after" << std::endl;
    g.show();
    REQUIRE(g.before(position(3,0)) == false);
    REQUIRE(g.after(position(3,0)) == true);
    REQUIRE(g.before(position(4,0)) == true);
    REQUIRE(g.after(position(4,0)) == false);

}
/**/
TEST_CASE("is_garbage", "[test]")
{
    game g;
    g.init(3);
    g.show();
    std::vector<position*> cells_slide;
    g.add_garbage(cells_slide);
    g.show();
    REQUIRE(g.is_garbage(position(3,0)) == 1);
    REQUIRE(g.is_garbage(position(4,0)) == 1);
    REQUIRE(g.is_garbage(position(4,3)) == 0); //teste sur une cell "simple"
}


TEST_CASE("getsize", "[test]")
{
    game g;
    g.init(3);
    std::vector<position*> cells_slide;
    g.add_garbage(cells_slide);   
    g.show();
    REQUIRE(g.getsize(position(2, 4)) == 1); //taille d'une case "simple" = 1
    REQUIRE(g.getsize(position(3, 0)) == 2);
    REQUIRE(g.getsize(position(4, 0)) == 2);
}
TEST_CASE("first", "[test]")
{
    game g;
    g.init(3);
    std::vector<position*> cells_slide;
    g.add_garbage(cells_slide); 
    g.show();
    REQUIRE(g.firstMalus(position(4, 0)) == position(3, 0));
}

TEST_CASE("path", "[ai]")
{   //deux teste sont fait ici cas special  1 et 2
    ai g;
    g.init(5);
    // g.rotate_target(); //cas special 1
    g.move_target(t_direction::right); // cas special 2
    g.move_target(t_direction::right); // cas special 2
    g.show();

    std::cout << "cell target 1 : " << g.getcell1target().x() << " , " << g.getcell1target().y() << std::endl;
    std::cout << "cell target 2 : " << g.getcell2target().x() << " , " << g.getcell2target().y() << std::endl;
    // auto v(g.chemin(position(5,10),position(5,11))); //cas special 1
    auto v(g.getPath(position(3, 11), position(4, 11))); // cas special 2
    for (auto x : v)
    {
        switch (x)
        {
        case t_action::go_right:
        {
            std::cout << "Right ";
            break;
        }
        case t_action::go_left:
        {
            std::cout << "left ";
            break;
        }
        case t_action::go_up:
        {
            std::cout << "up ";
            break;
        }
        case t_action::go_down:
        {
            std::cout << "Down ";
            break;
        }
        case t_action::change_direction:
        {
            std::cout << "Rotate ";
            break;
        }
        case t_action::exchange:
        {
            std::cout << "swicth ";
            break;
        }
        }
    }
    // REQUIRE(v.size()==8); //cas special 1
      REQUIRE(v.size()==9); //cas special 2
}

TEST_CASE("best_blow", "[ai]")
{
    ai a;
    a.init(3);
    a.move_target(t_direction::up);
    a.move_target(t_direction::up);
    a.move_target(t_direction::up);
    a.move_target(t_direction::up);
    a.show();
    auto c(a.best_blow(0));
    std::cout << "le meilleur coup a jouer : (" << c[0].p1.x() << "," << c[0].p1.y() << ") ; (" << c[0].p2.x() << "," << c[0].p2.y() << ") \n";
}
