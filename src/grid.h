#pragma once
#include "cell.h"
#include "rand.h" 
#include <iostream>
#include<algorithm>

using t_mat = std::vector<std::unique_ptr<cell>>;
using t_number_color=uint16_t ;

class grid {
public:
    grid( cordinate _max_height=12, cordinate _max_width=6,t_number_color colors=4);
    grid(grid const & g) ;
    ~grid()=default;
	grid & operator=(grid const & g);
    t_colors randomColor() const;
    bool neighbours_same_color(position p,t_colors clr ) const; //retourne vrai si il ya des case adjacente à la position p qui ont la couleur clr
    void init(t_number seed = 0);
    t_colors operator() (position p) const;
    cordinate max_height() const;
    cordinate max_width() const;
    void Setmax_width(cordinate const & x) ;
    void Setmax_height(cordinate const & x) ;
    void SetNbr_colors(t_number_color const & x) ;
    bool switch_cell(position p1, position p2); //echange les pointeur des deux cases
    void place_cell(cell c,position p);
    void delete_cell(position p);
    void new_row(int frame);
    std::vector<cell> generate_random_line(size t) const; //genere un vecteur de cell de couleur aléatoire de taille t
    delta cellDx(position p)const ;
    delta cellDy(position p)const ; 
    void setCellDx(position p,delta d);
    void setCellDy(position p,delta d);
    void resetCellDelta(position p);
   std::vector<position>  max_column() const;
   std::vector<int>  highest_column() const;
    void generate_garbage(std::vector<position*> & malus); //genere un malus
    bool estMalus(position const & p) const;
    bool not_hanging(position const & p) const; //teste si la case à la position p est suspendu dans le vide
    bool not_hanging_malus(position const & p,std::vector<position *>slide) const;
    bool hanging_garbage_slide(position const & p,std::vector<position *>slide)const;
    cordinate first_empty_line(position const & fst_cell,int size) const; //premiere ligne vide en partant du bas
    std::vector<position >  garbage_adjacent(position const & p) const ; //retourne les malus adjacent a la position p
    void transform_to_cell(std::vector<position> const & align_cell,std::vector<position* > &pos_cells); 
    t_number getSize(position const & p)const;
    bool before(position const & p) const;
    bool after(position const & p) const;
    position first(position const & p) const;
    bool under_bounds(position const & p) const; //verifie que p respecte les limites de la grille
    t_number getNbrColors() const {return nbr_colors;}
    
private:
    t_mat _board;
    cordinate _max_height;
    cordinate _max_width; 
    t_number_color nbr_colors; 
};

int nombreAleatoire(int k);
