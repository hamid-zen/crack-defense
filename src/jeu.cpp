#include "jeu.h"

jeu::jeu(coordonne _max_hauteur, coordonne _max_largeur, int colors)
    : _grille(_max_hauteur, _max_largeur, colors), _viseur(_max_largeur / 2, _max_hauteur / 2, _max_largeur / 2, _max_hauteur / 2 + 1) { _grille.init(); /* TODO: Enlever */ }

/**
 * @brief check si le jeu est perdu
 *
 * @return true perdu
 * @return false non-perdu
 */
bool jeu::perdu()
{
    for (unsigned int i(0); i < _grille.max_largeur(); i++)
    {
        if (_grille(i, 0) != t_colors::empty_cell)
            return true;
    }
    return false;
}
 std::pair<coordonne,coordonne> jeu::getcase1viseur() const{
    return std::pair<coordonne,coordonne>(_viseur.x1(),_viseur.y1());
 }
 std::pair<coordonne,coordonne> jeu::getcase2viseur() const{
    return std::pair<coordonne,coordonne>(_viseur.x2(),_viseur.y2());
 }
 t_colors jeu::getColor( std::pair<coordonne,coordonne> pair) const{
        return _grille(pair.first,pair.second);
}

/**
 * @brief deplace le viseur dans une direction donnée en checkant les bounds
 *
 * @param dir direction du deplaçement
 */
void jeu::deplacer_viseur(t_direction dir)
{
    switch (dir)
    {
    case t_direction::bas:
    {
        if (_viseur.y1() < _grille.max_hauteur() - 1 && _viseur.y2() < _grille.max_hauteur() - 1)
        {
            _viseur.setY1(_viseur.y1() + 1);
            _viseur.setY2(_viseur.y2() + 1);
        }
        break;
    }
    case t_direction::haut:
    {
        if (_viseur.y1() > 0 && _viseur.y2() > 0)
        {
            _viseur.setY1(_viseur.y1() - 1);
            _viseur.setY2(_viseur.y2() - 1);
        }
        break;
    }
    case t_direction::gauche:
    {
        if (_viseur.x1() > 0 && _viseur.x2() > 0)
        {
            _viseur.setX1(_viseur.x1() - 1);
            _viseur.setX2(_viseur.x2() - 1);
        }
        break;
    }
    case t_direction::droite:
    {
        if (_viseur.x1() < _grille.max_largeur() - 1 && _viseur.x2() < _grille.max_largeur() - 1)
        {
            _viseur.setX1(_viseur.x1() + 1);
            _viseur.setX2(_viseur.x2() + 1);
        }
        break;
    }
    }
}

/**
 * @brief affiche la table
 *
 */
void jeu::afficher() const
{
    for (unsigned int j(0); j < _grille.max_hauteur(); j++)
    {
        std::cout << std::endl;
        for (unsigned int i(0); i < _grille.max_largeur(); i++)
        {
            if ((_viseur.x1() == i && _viseur.y1() == j) || (_viseur.x2() == i && _viseur.y2() == j))
            {
                std::cout << "|F";
                continue;
            }
            if (_grille(i, j) == t_colors::empty_cell)
            {
                std::cout << "| ";
            }
            else
            {
                std::cout << "|" << toString_color(_grille(i, j));
            }
        }
        std::cout << "|";
    }
    std::cout << "\n"
              << " ";
    for (unsigned int k(0); k < _grille.max_largeur(); k++)
    {
        std::cout << "_"
                  << " ";
    }
    std::cout << std::endl;
    for (unsigned int i(0); i < _grille.max_largeur(); i++)
    {
        if (_grille(i, _grille.max_hauteur()) == t_colors::empty_cell)
        {
            std::cout << "| ";
        }
        else
        {
            std::cout << "|" << toString_color(_grille(i, _grille.max_hauteur()));
        }
    }
    std::cout << "|" << std::endl;
}

void jeu::echanger_cases_viseur() {
    // On echange dans la grille
    _grille.echange(_viseur.x1(), _viseur.y1(), _viseur.x2(), _viseur.y2());

    // On check si on doit faire descendre
    coordonne i = _viseur.x1(), j = _viseur.y1();
    while (j < _grille.max_hauteur()-1 && _grille(i, j) == t_colors::empty_cell)
    {
        _grille.echange(i, j, i, j-1);
        j++;
    }
    i = _viseur.x2();
    j = _viseur.y2();
    while (j < _grille.max_hauteur()-1 && _grille(i, j) == t_colors::empty_cell)
    {
        _grille.echange(i, j, i, j-1);
        j++;
    }
}
