#include <iostream>
#include "src/grid.h"
#include "src/game.h"
using namespace std;

//TODO: tout traduire en une seule langue
int main(){
    mysrand(5);
    game g;
    g.show();
    g.rotate_target();
    g.move_target(t_direction::up);
    g.move_target(t_direction::left);
    g.move_target(t_direction::left);
    g.show();
    g.switch_cells_target();
        g.move_target(t_direction::up);

        g.show();


    return 0;}
