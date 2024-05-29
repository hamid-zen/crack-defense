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
    std::cout<<"horizontallllllllllllllllllllll"<<std::endl;
    g.move_target(t_direction::right);
    g.move_target(t_direction::down);
    g.move_target(t_direction::down);
    g.switch_cells_target();
    g.move_target(t_direction::up);
    g.move_target(t_direction::up);
    g.show();

    std::vector<position> vec = g.horizontal_alignment();
    REQUIRE(vec.size()== 3); //le vecteur devrait contenir les 3 posisition des cases qui forme l'alignement
    REQUIRE(g(vec[0])== g(vec[1]) );
    REQUIRE(g(vec[0])== g(vec[2])) ; // et ces trois cases devrait avoir la meme couleur
    REQUIRE(g(vec[0]) == t_colors::blue); //et devrait etre la couleur rouge
}

TEST_CASE("Alignement_verticale", "[alignement][test]") {
    mysrand(3);
    game g;
   
    std::cout<<"verticallllllllllllllllllllll"<<std::endl;

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
    REQUIRE(vec[0].y()==5);
    REQUIRE(vec[0].y()==vec[1].y());
    REQUIRE(vec[0].y()==vec[2].y());
}
TEST_CASE("generate_garbage", "[test]")
{
    mysrand(3);
    game g;
    std::cout<<" before"<<std::endl;
    g.show();
    //g.add_garbage();
    std::cout<<" l'after'"<<std::endl;
    g.show();
    REQUIRE(g.before(position(3,4))==false);
    REQUIRE(g.after(position(3,4))==true);
    REQUIRE(g.before(position(4,4))==true);
        REQUIRE(g.after(position(4,4))==true);

    REQUIRE(g.before(position(5,4))==true);
        REQUIRE(g.after(position(5,4))==false);

}
/**/
TEST_CASE("est_malus", "[test]")
{
    mysrand(3);
    game g;
    g.show();
   // g.add_garbage();
    g.show();
    REQUIRE(g.is_garbage(position(3,4))==1);
    REQUIRE(g.is_garbage(position(4,4))==1);
    REQUIRE(g.is_garbage(position(5,4))==1);
}
TEST_CASE("adjacent", "[test]")
{
    mysrand(3);
    grid g;
    g.init();
    
     auto vec(g.garbage_adjacent(position(0,g.max_height() - 1 )));

    REQUIRE(vec.size()==2);
}
TEST_CASE("transform_to_cell", "[test]")
{
        mysrand(3);
    game g;
    g.rotate_target();
    g.move_target(t_direction::up);
    g.move_target(t_direction::right);
    g.switch_cells_target();
    g.move_target(t_direction::down);
    g.move_target(t_direction::down);
    g.rotate_target();
    g.move_target(t_direction::right);
    g.switch_cells_target();
    g.move_target(t_direction::left);
    g.move_target(t_direction::left);
    //g.add_garbage();
    std::cout<<"avant transformation\n";
    g.show();
    std::vector<position> vec = g.alignment();
    std::vector<position*> pos_cells;
    g.transform_malus_to_cell(vec,pos_cells);
    g.show();
   REQUIRE(pos_cells.size()==3);
}
TEST_CASE("getsize", "[test]")
{
    mysrand(3);
    game g;
    g.show();
   // g.add_garbage();
    g.show();
    REQUIRE(g.getsize(position(2,4))==0);
    REQUIRE(g.getsize(position(3,4))==3);
    REQUIRE(g.getsize(position(4,4))==3);
    REQUIRE(g.getsize(position(5,4))==3);
}
TEST_CASE("first", "[test]")
{
    mysrand(3);
    game g;
    g.show();
    //g.add_garbage();
    g.show();
    REQUIRE(g.firstMalus(position(5,4))==position(3,4));

}

TEST_CASE("chemin", "[ai]")
{
    mysrand(5);
    ai g;
    //g.rotate_target(); //cas special 1
    g.move_target(t_direction::right); //cas special 2
    g.move_target(t_direction::right); //cas special 2
    g.show();


    std::cout<<"cell target 1 : "<<g.getcell1target().x()<<" , "<<g.getcell1target().y()<<std::endl;
    std::cout<<"cell target 2 : "<<g.getcell2target().x()<<" , "<<g.getcell2target().y()<<std::endl;
   // auto v(g.chemin(position(5,10),position(5,11))); //cas special 1
    auto v(g.getPath(position(3,11),position(4,11))); //cas special 2
    for (auto x : v){
        switch (x)
        {
        case t_action::go_right:
        {
            std::cout<<"Right ";
            break;
        }
        case t_action::go_left:
        {
            std::cout<<"left ";
            break;
        }
        case t_action::go_up:
        {
            std::cout<<"up ";
            break;
        }
        case t_action::go_down:
        {
            std::cout<<"Down ";
            break;
        }
        case t_action::change_direction:
        {
            std::cout<<"Rotate ";
            break;
        }
        case t_action::exchange:
        {
            std::cout<<"swicth ";
            break;
        }
        }
    }
   // REQUIRE(v.size()==8); //cas special 1

}

 TEST_CASE("meilleur_coup", "[ai]")
{
    mysrand(3);
    ai a;
    a.move_target(t_direction::up);
    a.move_target(t_direction::up);
    a.move_target(t_direction::up);
    a.move_target(t_direction::up);

    std::cout<<"sum_color_distance() : "<<a.sum_color_distance(a.getGrid())<<std::endl;
        a.show();
    auto c (a.best_blow(1));
    std::cout<<"le meilleur coup a jouer : ("<<c[0].p1.x()<<","<<c[0].p1.y()<<") ; ("<<c[0].p2.x()<<","<<c[0].p2.y()<<") \n";

}
