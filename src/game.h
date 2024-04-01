#pragma once
#include "grid.h"
#include "cell.h"
#include "target.h"
#include <algorithm>
#include <iostream>

enum class t_direction{
    up,
    down,
    right,
    left
};


class game{

public:
    game(cordinate _max_height=12,cordinate _max_width=6,int colors=4);
    bool is_lost();
    void move_target(t_direction dir);
    void show() const;
    bool switch_cells_target();
    position drop_position(position const & p) const ;
    void drop(position const &p);
    std::vector<position>  vertical_alignment();
    std::vector<position> horizontal_alignment();
    std::vector<position>  alignment();
    position getcell1target() const; //recupere la position de la premiere case du viseur
    position getcell2target() const;
    t_colors getColor(position const & p) const; //recupere la couleur de la case qui a pour position pair
    t_colors operator()(position const & p)const;
    void rotate_target();
    void slideColumn(cordinate x);
    std::vector<position> slidecolumn_start_position(cordinate const & x); //recupere les position des des cases qui doivent tomber
    void delete_cell(position const &x);
    std::vector<cell> generate_random_line(size t)const;
    void place_new_case(position p,std::vector<cell> v);
    delta grid_dy()const;
    void inc_dy(delta const & d);
    void setWidth(size const & x);
    void setHeight(size const & x);
    size height() const;
    size width() const;
    void setColors_numbers(t_number_color const & x);
    void init();

private:
    grid _grid;
    target _target;
    delta _grid_dy;
};


