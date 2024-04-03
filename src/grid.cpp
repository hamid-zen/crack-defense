#include "grid.h"



grid::grid(cordinate height, cordinate width,t_number_color colors)
    : _board((height+1)*width),_max_height(height),_max_width(width),nbr_colors(colors){}

/**
 * @brief grid::couleurAleatoire
 * @return une couleur aleatoire
 */
// TODO: rajouter les autres couleurs
t_colors grid::randomColor() const
{
    int k =nombreAleatoire(nbr_colors);
    switch (k) {
    case 0:{
        return t_colors::blue;
    }
    case 1:{
        return t_colors::yellow;
    }
    case 2:{
        return t_colors::orange;
    }
    case 3:{
        return t_colors::pink;
    }
    default:{
         return t_colors::pink;
    }
    };
}

/**
 * @brief grid::adjacent
 * @param i
 * @param j
 * @param clr
 * @return si la case ajdacente (gauce, droite, bas, haut) est de la meme couleur
 */
bool grid::neighbours_same_color(position p, t_colors clr) const
{
    return ((p.x()-1>=0 && _board[p.y()*_max_width+p.x()-1] != nullptr && _board[p.y()*_max_width+p.x()-1]->color()==clr) || //verif à gauche
            (p.y()-1>=0 && _board[(p.y()-1)*_max_width+p.x()] != nullptr && _board[(p.y()-1)*_max_width+p.x()]->color()==clr) || //verif au dessus
            (p.x()+1<_max_width && _board[p.y()*_max_width+p.x()+1] != nullptr && _board[p.y()*_max_width+p.x()+1]->color()==clr) || //verif à droite
            (p.y()+1<_max_width && _board[(p.y()+1)*_max_width+p.x()] != nullptr && _board[(p.y()+1)*_max_width+p.x()]->color()==clr )) ; //verif en dessous

}

/**
 * @brief nombreAleatoire
 * @param k
 * @return une nombre aleatoire entre 0 et k (inclu)
 */
int nombreAleatoire(int k) {
    return myrand() % (k + 1);
}

/**
 * @brief grid::_init
 * initialise la grille
 */
void grid::init() // on initialisse une grille aleatoire de max 7 ligne (+1 ligne caché)
{   for(cordinate i(0);i<_max_width;i++){ //colone
        // pour chaque colone on genere un nbr de case pour la colonne
        int nbr=nombreAleatoire((_max_height+1)/2)+1; //nbr aleatoire entre  2 et 8 si MAx_hauteur=12 sachant que 1 sera caché au debut
        for(cordinate j(_max_height-nbr);j<_max_height+1;j++){ //ligne
            t_colors color;
            do{
                color=randomColor();
            }while(neighbours_same_color(position(i,j),color));

            _board[i+j*_max_width]=std::make_unique<cell>(color);
        }

    }
}

t_colors grid::operator()(position p) const
{
    if(p.x() < _max_width && p.y() <= _max_height && _board[ p.x() + p.y() *_max_width ])
        return _board[ p.x() + p.y() * _max_width ] -> color();
    else return t_colors::empty_cell;

}

cordinate grid::max_width() const
{
    return _max_width;
}

cordinate grid::max_height() const
{
    return _max_height;
}

/**
 * @brief grid::echange
 * @param x1
 * @param y1
 * @param x2
 * @param y2
 * Echange les pointeur dans (x1, y1) avec celui de (x2, y2)
 */
bool grid::switch_cell(position p1,position p2)
{
   //if((_board[p1.x()+_max_width*p1.y()]==nullptr || (_board[p1.x()+_max_width*p1.y()]->dx()==0 && _board[p1.x()+_max_width*p1.y()]->dy()==0 ))&& ( (_board[p2.x()+_max_width*p2.y()]==nullptr )||(_board[p2.x()+_max_width*p2.y()]->dx()==0 && _board[p2.x()+_max_width*p2.y()]->dy()==0) )  )
   { //si les deux case ne sont pas en train de bouger on peut les echanger
        std::swap(_board[p1.x()+_max_width*p1.y()], _board[p2.x()+_max_width*p2.y()]);
        return true;
    } 
        return false;
}
void grid::delete_cell(position p)
{
    _board[p.x()+ p.y()*_max_width].reset();
    
}
void grid::place_cell(cell c,position p){
    _board[p.x()+p.y()*_max_width] = std::make_unique<cell>(c);
}
void grid::Setmax_width(cordinate const & x) {
    this->_max_width=x;
}
void grid::Setmax_height(cordinate const & x) {
    _max_height=x;
}
void grid::SetNbr_colors(t_number_color const & x) {
    nbr_colors=x;
}

std::vector<cell> grid::generate_random_line(size t) const
{
    std::vector<cell> v;
    for (size i(0); i < t; i++) {
        v.push_back(cell(randomColor()));
    }
    return v;
}
delta grid::cellDx(position p) const
{
    if(_board[p.x() + p.y() * _max_width])
        return _board[p.x() + p.y() * _max_width]->dx();
    else 
        return 0;
}

delta grid::cellDy(position p) const
{
    if(_board[p.x() + p.y() * _max_width])
        return _board[p.x() + p.y() * _max_width]->dy();
    else return 0;
}
void grid::setCellDy(position p, delta d)
{
    if(_board[p.x() + p.y() * _max_width])
        _board[p.x() + p.y() * _max_width]->setDy(cellDy(p)+d);
}
void grid::setCellDx(position p, delta d)
{
    if(_board[p.x() + p.y() * _max_width])
        _board[p.x() + p.y() * _max_width]->setDx(cellDx(p)+d);
}
void grid::resetCellDelta(position p)
{
    if(_board[p.x() + p.y() * _max_width]){
        _board[p.x() + p.y() * _max_width]->setDx(0);
        _board[p.x() + p.y() * _max_width]->setDy(0);
    }
}



void grid::new_row()
{
    for (cordinate i(0); i < _max_width; i++) {
        for (cordinate j(0); j < _max_height; j++) { //on s'arrete a max height et non maxheight+1
            _board[i + j * _max_width] = std::move(_board[i + (j + 1) * _max_width]);
        }
    }

    //apres avoir decaler toutes les lignes d'une case vers le haut
    //il faut regenerer un nvl ligne aleatoire
    auto vec(generate_random_line(_max_width));
    for (cordinate i(0); i < _max_width; i++) {
        _board[i + _max_height * _max_width] = std::make_unique<cell>(
            vec[i]); //ici j=max_height car on remplie la toute premiere ligne(celle qui est caché pour l'insatnt)
    }
}

std::vector<position>  grid::max_column() const{
    std::vector<position> vec;
    cordinate  i,j;
    for(cordinate i(0);i<(max_height()*max_width());i++){
        if(_board[i]!=nullptr){
            vec.push_back(position(i%max_width(),max_height()- ((i/max_width())+1 )));
            j=max_height()- ((i/max_width())+1 );
            i=i%max_width()+1;

            while( i<max_width()) //on ajoute les autres cases qui  ont la mm hauteur donc qui son sur la meme ligne
            {
                if(_board[i + j * _max_width]!=nullptr){
                    vec.push_back(position(i,j));
                }
                i++;
            }
            return vec;
        }
    }

}
