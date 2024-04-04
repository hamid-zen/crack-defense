#include "game.h"

game::game(cordinate _max_height, cordinate _max_width, int colors)
    : _grid(_max_height, _max_width, colors), _target(position(_max_width / 2, _max_height / 2), position(_max_width / 2, _max_height / 2 + 1)), _grid_dy(0) { _grid.init(); /* TODO: Enlever */ }

/**
 * @brief check si le game est perdu
 *
 * @return true perdu
 * @return false non-perdu
 */
bool game::is_lost()
{
    for (unsigned int i(0); i < _grid.max_width(); i++)
    {
        if (_grid(position(i, 0)) != t_colors::empty_cell)
            return true;
    }
    return false;
}
position game::getcell1target() const
{
    return position(_target.x1(), _target.y1());
}
position game::getcell2target() const
{
    return position(_target.x2(), _target.y2());
}
t_colors game::getColor(position const &p) const
{
    return _grid(p);
}

t_colors game::operator()(position const &p) const
{
    return _grid(p);
}

/**
 * @brief deplace le viseur dans une direction donnée en checkant les bounds
 *
 * @param dir direction du deplaçement
 */
void game::move_target(t_direction dir)
{
    switch (dir)
    {
    case t_direction::down:
    {
        if (_target.y1() < _grid.max_height() - 1 && _target.y2() < _grid.max_height() - 1)
        {
            _target.setY1(_target.y1() + 1);
            _target.setY2(_target.y2() + 1);
        }
        break;
    }
    case t_direction::up:
    {
        if (_target.y1() > 0 && _target.y2() > 0)
        {
            _target.setY1(_target.y1() - 1);
            _target.setY2(_target.y2() - 1);
        }
        break;
    }
    case t_direction::left:
    {
        if (_target.x1() > 0 && _target.x2() > 0)
        {
            _target.setX1(_target.x1() - 1);
            _target.setX2(_target.x2() - 1);
        }
        break;
    }
    case t_direction::right:
    {
        if (_target.x1() < _grid.max_width() - 1 && _target.x2() < _grid.max_width() - 1)
        {
            _target.setX1(_target.x1() + 1);
            _target.setX2(_target.x2() + 1);
        }
        break;
    }
    }
}

/**
 * @brief affiche la table
 *
 */
void game::show() const
{
    for (unsigned int j(0); j < _grid.max_height(); j++)
    {
        std::cout << std::endl;
        for (unsigned int i(0); i < _grid.max_width(); i++)
        {
            if ((_target.x1() == i && _target.y1() == j) || (_target.x2() == i && _target.y2() == j))
            {
                std::cout << "|F";
                continue;
            }
            if (_grid(position(i, j)) == t_colors::empty_cell)
            {
                std::cout << "| ";
            }
            
            else
            {
                if(_grid.estMalus(position(i,j))){
                std::cout << "|M";
                }else{
                std::cout << "|" << toString_color(_grid(position(i, j)));
                }
            }
        }
        std::cout << "|";
    }
    std::cout << "\n"
              << " ";
    for (unsigned int k(0); k < _grid.max_width(); k++)
    {
        std::cout << "_"
                  << " ";
    }
    std::cout << std::endl;
    for (unsigned int i(0); i < _grid.max_width(); i++)
    {
        if (_grid(position(i, _grid.max_height())) == t_colors::empty_cell)
        {
            std::cout << "| ";
        }
        else
        {
            std::cout << "|" << toString_color(_grid(position(i, _grid.max_height())));
        }
    }
    std::cout << "|" << std::endl;
}

bool game::switch_cells_position( position p1 , position p2)
{
    // On echange dans la grille
    if(target_verticale() and one_case_empty(p1,p2))
        return false;
    return _grid.switch_cell(p1, p2);
}
position game::drop_position(position const &p) const
{
    unsigned int j(p.y());
    while ((j + 1) < _grid.max_height() && _grid(position(p.x(), j + 1)) == t_colors::empty_cell)
    {
        j++;
    }
    return position(p.x(), j);
}

bool game::one_case_empty() const{
    return ((getColor(this->getcell1target())==t_colors::empty_cell)&&(getColor(this->getcell2target())!=t_colors::empty_cell))|| ((getColor(this->getcell2target())==t_colors::empty_cell)&&(getColor(this->getcell1target())!=t_colors::empty_cell));
}
bool game::one_case_empty(position p1, position p2) const
{
    return getColor(p1)==t_colors::empty_cell or getColor(p2)==t_colors::empty_cell ;
}
bool game::target_cells_empty() const{
    return (getColor(this->getcell1target())==t_colors::empty_cell)&&(getColor(this->getcell2target())==t_colors::empty_cell);
}

bool game::cells_above() const{
    return( (getcell1target().y()-1>0 &&  (getColor(position(getcell1target().x(),getcell1target().y()-1))!=t_colors::empty_cell) )  || (getcell2target().y()-1>0 &&  (getColor(position(getcell2target().x(),getcell2target().y()-1))!=t_colors::empty_cell) )  );
}
bool game::cells_above(position p1, position p2) const
{
    return p1.y()-1>0 && (getColor(position(p1.x(),p1.y()-1))==t_colors::empty_cell or getColor(position(p2.x(),p2.y()-1))==t_colors::empty_cell );
}
void game::drop()
{
    if(getColor(getcell1target())==t_colors::empty_cell){
            position p(getcell2target()); //la position ou se troyve la case qui doit tomber
            auto position_final(drop_position(p));
    _grid.switch_cell(p, position_final);
    }else{
        position p(getcell1target());
        auto position_final(drop_position(p));
    _grid.switch_cell(p, position_final);
    }
    
}
void game::drop(position p1, position p2)
{
   if(one_case_empty(p1,p2)){
        if(_grid(p1)==t_colors::empty_cell){
            auto fall_pos = drop_position(p1);
            _grid.switch_cell(p1,fall_pos);
        }
        else {
            auto fall_pos = drop_position(p2);
            _grid.switch_cell(p2,fall_pos);
        }    
   }
}
bool game::switch_cells_target()
{
    // On echange dans la grille
   return _grid.switch_cell(position(_target.x1(), _target.y1()), position(_target.x2(), _target.y2()));
}

std::vector<position> game::vertical_alignment()
{
    std::vector<position > vec;

        //alignement verticale
        for(unsigned int i(0);i<_grid.max_width();i++){
            t_colors clr=_grid(position( i,0));
            vec.clear();
            vec.push_back(position(i,0)); //on ajoute la position de cette case au vecteur
            for(unsigned int j(1);j<_grid.max_height();j++){
                
                if(vec.size()==3){ //cad on a trouvé un alignement verticale
                    unsigned int k(j);
                    //on ajoute tant que c'est la meme couleur
                    while( k<_grid.max_height() && _grid(position( i,k))==clr ){
                        vec.push_back(position(i,k));
                        k++;
                    }
                    return vec;
                }
                else if(clr==t_colors::empty_cell || (_grid(position( i,j))!=clr )) //si c'est une case vide ou que c'est pas la meme couleur on remet le vec d'alignement  vide et on met a jour la couleur courante
                {  vec.clear();
                    vec.push_back(position(i,j));
                    clr=_grid(position( i,j));
                }
                 
                else{  //si c'est la meme couleur on ajoute la position de la case au vecteur
                       vec.push_back(position(i,j));
                    }
                }
            if(vec.size()==3){ //alignement a la fin
           return vec;
        }

            }
        if(vec.size()==3){ //alignement a la fin
           return vec;
        }
        vec.clear();
        return vec;
}

std::vector<position> game::horizontal_alignment()
{
    std::vector<position> vec;

   for(unsigned int j(0);j<_grid.max_height();j++) {
        t_colors clr=_grid(position( 0,j));
        vec.clear();
        vec.push_back(position(0,j)); //on ajoute la position de cette case au vecteur
        for(unsigned int i(1);i<_grid.max_width();i++){
            if(vec.size()==3){ //cad on a trouvé un alignement verticale
                unsigned int k(i);
                //on ajoute tant que c'est la meme couleur
                while(k<_grid.max_width() && _grid(position( k,j))==clr ){
                    vec.push_back(position(k,j));
                    k++;
                }
                return vec;
            }
            else if(clr==t_colors::empty_cell || (_grid(position( i,j))!=clr )) //si c'est une case vide ou que c'est pas la meme couleur on remet le vec d'alignement  vide et on met a jour la couleur courante
            {  vec.clear();
                vec.push_back(position(i,j));
                clr=_grid(position( i,j));
            }else{  //si c'est la meme couleur on ajoute la position de la case au vecteur
                   vec.push_back(position(i,j));

                }
            }
        if(vec.size()==3){ //alignement a la fin
       return vec;
    }

    }
    if(vec.size()==3){ //alignement a la fin
       return vec;
    }
    vec.clear();
    return vec;
}

std::vector<position> game::horizontal_alignment(std::vector<position> const & p){
  std::vector<position> vec;
  bool trouve(false); 
  t_colors clr=_grid(p[0]);

   for(unsigned int j(p[0].y());j<p[p.size()-1].y();j++) {//on parcours seulement les lignes de l'alignement verticale
        vec.clear();
        for(unsigned int i(0);i<_grid.max_width();i++){
            //vec.size()=2 et non 3 
            if(trouve && vec.size()>=2){ //on est passee par une case de l'align1 et on a trouvee un alignement
                unsigned int k(i);
                while(k<_grid.max_width() && _grid(position( k,j))==clr){
                    vec.push_back(position(k,j));
                    k++;
                }
                return vec;
            }
            else if((_grid(position(i,j))!=clr )) 
            {  vec.clear();
            }else if(std::find(p.begin(),p.end(),position(i,j))!=p.end()){ 
                //on trouve une case qui est deja dans le premiere alignement 
                trouve=true;
            }else{//==clr
            vec.push_back(position(i,j));
            }
        }
      } 

    if(trouve && vec.size()>=2){ //alignement a la fin
       return vec;
    }
    vec.clear();
    return vec;
  
}


std::vector<position > game::alignment()
{
    auto vec(vertical_alignment());
    if(vec.size()>0){
        auto vec1(horizontal_alignment(vec));
        if(vec1.size()>0) //concat
            vec.insert(vec.end(), vec1.begin(), vec1.end());
        return vec;
    }
    else return horizontal_alignment();
}


void game::delete_alignement(std::vector<position>  const & v){
    for(auto i(v.size()-1);i>0;i--){
        _grid.delete_cell(v[i]);
    }

}

void game::rotate_target()
{
    if (_target.isVertical() && _target.x1() < _grid.max_width() - 1)
        _target.setSense();
    else if (_target.isHorizontal() && _target.y1() < _grid.max_height() - 1)
        _target.setSense();
    // sinn le changement de sense est impossible on en fait rien
}

void game::slideColumn(cordinate x)
{ // x la colone
    int j(_grid.max_height() - 1);
    while (_grid(position(x, j)) != t_colors::empty_cell)
    { // on cherche en partant du bas la premiere case vide
        j--;
    }
    while (_grid(position(x, j)) == t_colors::empty_cell)
    { // on cherche la premiere case suspendu au dessus du vide
        j--;
    }
    for (unsigned int k(j); k >= 0; k--)
    {                                                      // on parcours toutes les cases restantes au dessus
        if (_grid(position(x, k)) == t_colors::empty_cell) // jusqu'a qu'il n'y en ai plus
            break;
        else{
            auto pst = drop_position(position(x, k)); // on prend la pposition ou la case doit tomber (forcement une case vide)
            _grid.switch_cell(position(x, k), pst);   // on les fait s'echanger
        }
    }
}
void game::delete_cell(position const &x)
{
    _grid.delete_cell(x);
}


void game::add_new_row(){
 // On ajoute une nouvelle ligne en faisant monter les cellules
    _grid.new_row();

    // On fait remonter la target d'un cran
    move_target(t_direction::up);
}

void game::setGrid_dy(float newGrid_dy)
{
    _grid_dy = newGrid_dy;
}


void game::place_new_case(position p, std::vector<cell> v)
{
    for (std::size_t c(0); c < v.size(); c++)
    {
        
         _grid.place_cell(v[c], position(p.x(), p.y() + c));
    }
}



float game::grid_dy() const
{
    return _grid_dy;
}

void game::inc_dy(delta const & d){
    _grid_dy+=d;
}

void game::setWidth(size const & x){
    _grid.Setmax_width(x);
}
void game::setHeight(size const & x){
    _grid.Setmax_height(x);
}

size game::height() const
{
    return _grid.max_height();
}

size game::width() const
{
    return _grid.max_width();
}

void game::setColors_numbers(t_number_color const & x){
    _grid.SetNbr_colors(x);
}
void game::init(){
    _grid.init();
}

bool game::target_verticale() const
{
    return _target.isVertical();
}

delta game::cellDx(position p) const
{
    return _grid.cellDx(p);
}

delta game::cellDy(position p) const
{
    return _grid.cellDy(p);
}

void game::setCellDy(position p, delta d)
{
    _grid.setCellDy(p,d);
}
void game::resetCellDelta(position p)
{
    _grid.resetCellDelta(p);
}
void game::setCellDx(position p, delta d)
{
    _grid.setCellDx(p,d);
}
std::vector<position>  game::max_column() const{
    return _grid.max_column();
}

void game::add_garbage(){
    _grid.generate_garbage();
}
