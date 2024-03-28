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
std::pair<unsigned int, unsigned int> jeu::faire_tomber(coordonne x, coordonne y)
{   unsigned int j(y);
    while((j+1)<_grille.max_hauteur() && _grille(x,j+1)==t_colors::empty_cell){
        j++;
    }
    return std::pair<unsigned int, unsigned int>(x,j);
}

std::vector<std::pair<unsigned int, unsigned int> > jeu::alignement_vertical()
{
    std::vector<std::pair<unsigned int, unsigned int> > vec;

        //alignement verticale
        for(unsigned int i(0);i<_grille.max_largeur();i++){
            t_colors clr=_grille(i,0);
            vec.clear();
            vec.push_back(std::pair<unsigned int, unsigned int>(i,0)); //on ajoute la position de cette case au vecteur
            for(unsigned int j(1);j<_grille.max_hauteur();j++){
                if(vec.size()==3){ //cad on a trouvé un alignement verticale
                    unsigned int k(j);
                    //on ajoute tant que c'est la meme couleur
                    while(_grille(i,k)==clr && k<_grille.max_hauteur()){
                        vec.push_back(std::pair<unsigned int, unsigned int>(i,k));
                        k++;
                    }
                    return vec;
                }
                else if(clr==t_colors::empty_cell || (_grille(i,j)!=clr )) //si c'est une case vide ou que c'est pas la meme couleur on remet le vec d'alignement  vide et on met a jour la couleur courante
                {  vec.clear();
                    vec.push_back(std::pair<unsigned int, unsigned int>(i,j));
                    clr=_grille(i,j);
                }
                 
                else{  //si c'est la meme couleur on ajoute la position de la case au vecteur
                       vec.push_back(std::pair<unsigned int, unsigned int>(i,j));
                    }
                }

            }
        if(vec.size()==3){ //alignement a la fin
           return vec;
        }
        vec.clear();
        return vec;
}

std::vector<std::pair<unsigned int, unsigned int> > jeu::alignement_horizontale()
{
    std::vector<std::pair<unsigned int, unsigned int> > vec;

   for(unsigned int j(0);j<_grille.max_hauteur();j++) {
        t_colors clr=_grille(0,j);
        vec.clear();
        vec.push_back(std::pair<unsigned int, unsigned int>(0,j)); //on ajoute la position de cette case au vecteur
        for(unsigned int i(1);i<_grille.max_largeur();i++){
            if(vec.size()==3){ //cad on a trouvé un alignement verticale
                unsigned int k(i);
                //on ajoute tant que c'est la meme couleur
                while(_grille(k,j)==clr && k<_grille.max_largeur()){
                    vec.push_back(std::pair<unsigned int, unsigned int>(k,j));
                    k++;
                }
                return vec;
            }
            else if(clr==t_colors::empty_cell || (_grille(i,j)!=clr )) //si c'est une case vide ou que c'est pas la meme couleur on remet le vec d'alignement  vide et on met a jour la couleur courante
            {  vec.clear();
                vec.push_back(std::pair<unsigned int, unsigned int>(i,j));
                clr=_grille(i,j);
            }else{  //si c'est la meme couleur on ajoute la position de la case au vecteur
                   vec.push_back(std::pair<unsigned int, unsigned int>(i,j));

                }
            }

    }
    if(vec.size()==3){ //alignement a la fin
       return vec;
    }
    vec.clear();
    return vec;
}

std::vector<std::pair<unsigned int, unsigned int> > jeu::alignement()
{
    if(alignement_vertical().size()>0)
        return alignement_vertical();
    else return alignement_horizontale();
}

void jeu::changer_sense_viseur(){
    if(_viseur.estVerticale() && _viseur.x1()<_grille.max_largeur()-1)
        _viseur.setSense();
    else if(_viseur.estHorizontale() && _viseur.y1()<_grille.max_hauteur()-1)
        _viseur.setSense();
        //sinn le changement de sense est impossible on en fait rien
}

void jeu::faire_glisser_colone(coordonne x){ //x la colone
            int j(_grille.max_hauteur()-1);
            while(_grille(x,j)!=t_colors::empty_cell){ //on cherche en partant du bas la premiere case vide
                    j--;
            }
            while(_grille(x,j)!=t_colors::empty_cell){ //on cherche la premiere case suspendu au dessus du vide
                j--;
            }
                        for(unsigned int k(j);j>0;j--){
                if(_grille(x,j)==t_colors::empty_cell)
                    return;
                else{
                auto position=faire_tomber(x,j);
                _grille.echange(x,j,position.first,position.second);


                }
            }

}
