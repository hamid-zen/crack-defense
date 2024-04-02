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
    bool one_case_empty() const; //return true si une deux cases du target est vide utilie pour determiner ce qui doit ou non etre fait apres le switch
    bool target_cells_empty() const; //return true si le viseur est sur deux cases vides (il n'ya pas de switch a faire alors)
    position drop_position(position const & p) const ; // recupere la position ou doit tomber la case qui est suspendu
    void drop(); 
    bool cells_above() const;//il y'a des cases au dessus de la cases au dessus du target
    std::vector<position>  vertical_alignment();
    std::vector<position> horizontal_alignment();
    //std::vector<position> horizontal_alignment(std::vector<position> const & );
    std::vector<position>  alignment();


    void delete_alignement(std::vector<position>  const & v);
    position getcell1target() const; //recupere la position de la premiere case du viseur
    position getcell2target() const;
    t_colors getColor(position const & p) const; //recupere la couleur de la case qui a pour position pair
    t_colors operator()(position const & p)const;
    void rotate_target();
    void slideColumn(cordinate x);
    std::vector<position> slidecolumn_start_position(cordinate const & x); //recupere les position des des cases qui doivent tomber
    void delete_cell(position const &x);
    void add_new_row();
    void setGrid_dy(delta newGrid_dy);
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


