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
                std::cout << "|" << toString_color(_grid(position(i, j)));
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

void game::switch_cells_target()
{
    // On echange dans la grille
    _grid.switch_cell(position(_target.x1(), _target.y1()), position(_target.x2(), _target.y2()));
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
void game::drop(position const &p)
{
    auto position_final(drop_position(p));
    _grid.switch_cell(p, position_final);
}
std::vector<position > game::vertical_alignment()
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
                    while(_grid(position( i,k))==clr && k<_grid.max_height()){
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
                while(_grid(position( k,j))==clr && k<_grid.max_width()){
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

std::vector<position > game::alignment()
{
    if(vertical_alignment().size()>0)
        return vertical_alignment();
    else return horizontal_alignment();
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
    for (unsigned int k(j); j >= 0; j--)
    {                                                      // on parcours toutes les cases restantes au dessus
        if (_grid(position(x, k)) == t_colors::empty_cell) // jusqu'a qu'il n'y en ai plus
            break;
        else
        {
            auto pst = drop_position(position(x, k)); // on prend la pposition ou la case doit tomber (forcement une case vide)
            _grid.switch_cell(position(x, k), pst);   // on les fait s'echanger
        }
    }
}
void game::delete_cell(position const &x)
{
    _grid.delete_cell(x);
}

std::vector<cell> game::generate_random_line(size t) const
{
    std::vector<cell> v;
    for (size i(0); i < t; i++)
    {
        v.push_back(cell(_grid.randomColor()));
    }
    return v;
}

void game::place_new_case(position p, std::vector<cell> v)
{
    for (std::size_t c(0); c < v.size(); c++)
    {
        _grid.place_cell(v[c], position(p.x(), p.y() + c));
    }
}

delta game::grid_dy() const
{
    return _grid_dy;
}

void game::inc_dy(delta const &d)
{
    _grid_dy += d;
}