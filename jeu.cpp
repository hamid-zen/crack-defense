#include "jeu.h"
#include <algorithm>

jeu::jeu(coordonne _max_hauteur, coordonne _max_largeur, int colors) //le viseur est positionné au millieu en debut de jeu
    :_grille1(_max_hauteur,_max_largeur,colors),_viseur(_max_largeur/2,_max_hauteur/2,_max_largeur/2+1,_max_hauteur/2+1),_score(0){}

bool jeu::perdu()
{  for(unsigned int i(0);i<_grille1.max_largeur();i++){
            if(_grille1(i,0)!=t_colors::empty_cell)
                return  true;
    }
    return false;
}

void jeu::deplacer_viseur(tdirection dir)
{   switch (dir) {
    case tdirection::bas:{
        _viseur.setY1(_viseur.y1()+1);
        _viseur.setY2(_viseur.y2()+1);
    }
    case tdirection::haut:{
        _viseur.setY1(_viseur.y1()-1);
        _viseur.setY2(_viseur.y2()-1);
    }
    case tdirection::gauche:{
        _viseur.setX1(_viseur.x1()+1);
        _viseur.setX2(_viseur.x2()+1);
    }
    case tdirection::droite:{
        _viseur.setX1(_viseur.x1()-1);
        _viseur.setX2(_viseur.x2()-1);

    }
    }
}
std::pair<unsigned int, unsigned int> jeu::faire_tomber(coordonne x, coordonne y)
{   unsigned int j(y);
    while((j+1)<_grille1.max_hauteur() && _grille1(x,j+1)==t_colors::empty_cell){
        j++;
    }
    return std::pair<unsigned int, unsigned int>(x,j);
}

std::vector<std::pair<unsigned int, unsigned int> > jeu::alignement_vertical()
{
    std::vector<std::pair<unsigned int, unsigned int> > vec;

        //alignement verticale
        for(unsigned int i(0);i<_grille1.max_largeur();i++){
            t_colors clr=_grille1(i,0);
            vec.push_back(std::pair<unsigned int, unsigned int>(i,0)); //on ajoute la position de cette case au vecteur
            for(unsigned int j(1);j<_grille1.max_hauteur();j++){
                if(clr==t_colors::empty_cell || (_grille1(i,j)!=clr )) //si c'est une case vide ou que c'est pas la meme couleur on remet le vec d'alignement  vide et on met a jour la couleur courante
                {  vec.clear();
                    vec.push_back(std::pair<unsigned int, unsigned int>(i,j));
                    clr=_grille1(i,j);
                }
                else  if(vec.size()==3){ //cad on a trouvé un alignement verticale
                    unsigned int k(j);
                    //on ajoute tant que c'est la meme couleur
                    while(_grille1(i,k)==clr && k<_grille1.max_hauteur()){
                        vec.push_back(std::pair<unsigned int, unsigned int>(i,k));
                        k++;
                    }
                    return vec;
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

   for(unsigned int j(0);j<_grille1.max_hauteur();j++) {
        t_colors clr=_grille1(0,j);
        vec.push_back(std::pair<unsigned int, unsigned int>(0,j)); //on ajoute la position de cette case au vecteur
        for(unsigned int i(1);i<_grille1.max_largeur();i++){
            if(clr==t_colors::empty_cell || (_grille1(i,j)!=clr )) //si c'est une case vide ou que c'est pas la meme couleur on remet le vec d'alignement  vide et on met a jour la couleur courante
            {  vec.clear();
                vec.push_back(std::pair<unsigned int, unsigned int>(i,j));
                clr=_grille1(i,j);
            }
            else  if(vec.size()==3){ //cad on a trouvé un alignement verticale
                unsigned int k(i);
                //on ajoute tant que c'est la meme couleur
                while(_grille1(k,j)==clr && k<_grille1.max_largeur()){
                    vec.push_back(std::pair<unsigned int, unsigned int>(k,j));
                    k++;
                }
                return vec;
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

std::vector<std::pair<unsigned int, unsigned int> > jeu::alignement()
{
    if(alignement_vertical().size()>0)
        return alignement_vertical();
    else return alignement_horizontale();
}




