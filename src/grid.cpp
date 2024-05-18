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
    int k =nombreAleatoire(nbr_colors - 1);
    switch (k) {
    case 0:
        return t_colors::blue;
    case 1:
        return t_colors::yellow;
    case 2:
        return t_colors::orange;
    case 3:
        return t_colors::pink;
    case 4:
        return t_colors::sky_blue;
    case 5:
        return t_colors::white;
    case 6:
        return t_colors::purple;
    case 7:
        return t_colors::green;
    default:
        return t_colors::pink;
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
void grid::init(t_number seed) // on initialisse une grille aleatoire de max 7 ligne (+1 ligne caché)
{
    if (seed != 0) // seed choisie
        mysrand(seed);

    for(cordinate i(0);i<_max_width;i++){ //colone
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
    if(p.x() < _max_width && p.y() <= _max_height && _board[ p.x() + p.y() *_max_width])
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
    //si les deux case ne sont pas en train de bouger on peut les echanger
    std::swap(_board[p1.x()+_max_width*p1.y()], _board[p2.x()+_max_width*p2.y()]);
    return true;
    
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



void grid::new_row(int frame)
{
    for (cordinate i(0); i < _max_width; i++) {
        for (cordinate j(0); j < _max_height; j++) { //on s'arrete a max height et non maxheight+1
            _board[i + j * _max_width] = std::move(_board[i + (j + 1) * _max_width]);
        }
    }

    //apres avoir decaler toutes les lignes d'une case vers le haut
    //il faut regenerer un nvl ligne aleatoire
    auto x(nombreAleatoire(_max_width-1)); //colone de la case special
    auto vec(generate_random_line(_max_width));
    for (cordinate i(0); i < _max_width; i++) {
        // if(frame==150 && i==x)
        //     _board[i + _max_height * _max_width] = std::make_unique<cell>(t_colors::all);
        // else
            _board[i + _max_height * _max_width] = std::make_unique<cell>(vec[i]); //ici j=max_height car on remplie la toute premiere ligne(celle qui est caché pour l'insatnt)
    }
}

std::vector<position>  grid::max_column() const{
    std::vector<position> vec;
    cordinate  i,j;
    for(cordinate i(0);i<(max_height()*max_width());i++){
        if(_board[i]!=nullptr){
            vec.push_back(position(i%max_width(),i/max_width()));
            j=(i/max_width()) ;
            i=i%max_width()+1;

            while( i<max_width()) //on ajoute les autres cases qui  ont la mm hauteur donc qui son sur la meme ligne
            {
                if(_board[i + j * _max_width]!=nullptr){
                    vec.push_back(position(i,j));
                }
                i++;
            }return vec;
        }
    }
    return vec; //juste a cause du warning

}

std::vector<int>  grid::highest_column() const{
std::vector<int> vec;
    cordinate  i,j;
    for(cordinate i(0);i<(max_height()*max_width());i++){
        if(_board[i]!=nullptr){
            vec.push_back(i%max_width());
            j=(i/max_width()) ;
            i=i%max_width()+1;
            while( i<max_width()) //on ajoute les autres cases qui  ont la mm hauteur donc qui son sur la meme ligne
            {
                if(_board[i + j * _max_width]!=nullptr){
                    vec.push_back(i);
                }
                i++;
            }return vec;
        }
    }
    return vec;
}



void grid::generate_garbage(std::vector<position*> & malus){
    // auto vec(max_column());
    // int taille ;
    // int debut;
    // cordinate j(vec[0].y()-1);
    // if(vec[0].x()==max_width()-1){ //si la colone la plus haute est la derniere
    //     debut=vec[0].x()-1; //on commence le malus dans la colone d'avant
    //     taille=2;
    // }else {
    //     debut=vec[0].x();
    //     if(vec.size()>1){
    //         taille=vec[vec.size()-1].x()-vec[0].x()+1;
    //     }else{

    //         taille= nombreAleatoire(_max_width-vec[0].x())+1;
    //     }
    // }
    
    // _board[debut]=std::make_unique<malusCell>(t_colors::garbage,false,true);
    // malus.push_back(new position(debut,0));

    // for(int i(1);i<(taille-1);i++){
    //     _board[(debut+i)]=std::make_unique<malusCell>(t_colors::garbage,true,true);
    //     malus.push_back(new position(debut+i,0));
    // }
    // malus.push_back(new position(debut+taille-1,0));
    // _board[(debut+taille-1)]=std::make_unique<malusCell>(t_colors::garbage,true,false);
    _board[2]=std::make_unique<malusCell>(t_colors::garbage,false,true);
    _board[3]=std::make_unique<malusCell>(t_colors::garbage,true,true);
    _board[4]=std::make_unique<malusCell>(t_colors::garbage,true,true);
    _board[5]=std::make_unique<malusCell>(t_colors::garbage,true,false);
    malus.push_back(new position(2,0));
    malus.push_back(new position(3,0));
    malus.push_back(new position(4,0));
    malus.push_back(new position(5,0));


}

bool grid::estMalus(position const & p) const{
    if(_board[p.x() + p.y() * _max_width] !=nullptr)
        return _board[p.x() + p.y() * _max_width]->estmalus();
    else return false;
}


bool grid::not_hanging(position const & p) const{ 
    if (p.y() == max_height() - 1)
        return true;
    else if (_board[p.x()+ (p.y() + 1)*_max_width] && _board[p.x()+ (p.y() + 1)*_max_width]->dy()==0 )
    {
        return true;
    }
    else
        return false;
}

bool grid::not_hanging_malus(position const &p, std::vector<position *> slide) const
{
    auto pos_bott = position(p.x(),p.y()+1);
    if (p.y() == max_height() - 1)
        return true;
    else if (_board[p.x()+ (p.y() + 1)*_max_width] && (_board[p.x()+ (p.y() + 1)*_max_width]->dy()==0 && std::find_if(slide.begin(), slide.end(), [pos_bott](position * pos) { return *pos == pos_bott; }) == slide.end()) )
    {
        std::cout<<"x :"<<p.x()<<" y:"<<p.y()<<"\n";
        return true;
        
    }
    else
        return false;
}

bool grid::hanging_garbage(position const & p) const{

    auto y(p.y());
    auto x(first(p).x());
    auto size(getSize(position (p.x(), y)));

    for (unsigned int i(x); i < (x+size); i++)
    {
        if(_board[i + y * _max_width] && not_hanging(position(i,y))){
            return false; // ya une des cases du malus qui est "retenue"
        }
    }
    return true;
}

bool grid::hanging_garbage_slide(position const &p, std::vector<position *> slide) const
{
    auto y(p.y());
    auto x(first(p).x());
    auto size(getSize(position (p.x(), y)));

    for (unsigned int i(x); i < (x+size); i++)
    {
        if(_board[i + y * _max_width] && not_hanging_malus(position(i,y),slide)){
            //std::cout<<"hanging?"<<not_hanging_malus(position(i,y),slide)<<"\n";
            return false; // ya une des cases du malus qui est "retenue"
        }
    }
    return true;
}

cordinate grid::first_empty_line(position const & fst_cell,int size) const{
    bool vide(true);
    for(auto j(fst_cell.y());j<max_height();j++){ // pour chaque ligne on verifie si elle es completement vide si c'est le cas on retourne le y
        vide=true;
        for(auto i(fst_cell.x());i<(fst_cell.x()+size);i++){
            if(_board[i + j * _max_width]!=nullptr){
                vide=false;
                break;
            }
        }
        if(vide){
            return j;
        }

    }
}

t_number grid::getSize(position const & p)const{
    int k(0);
    if (auto malus_cell = dynamic_cast<malusCell*>(_board[p.x()+ p.y() * _max_width].get())) {
        k++;
        int i(1);
        while(malus_cell && malus_cell->next_right()){
            k++;
            malus_cell = dynamic_cast<malusCell*>(_board[p.x()+i+ p.y() * _max_width].get());
            i++; 
        }
        i=1;
        malus_cell = dynamic_cast<malusCell*>(_board[p.x()+ p.y() * _max_width].get());
        while(malus_cell && malus_cell->next_left()){
            k++;
            malus_cell = dynamic_cast<malusCell*>(_board[p.x()-i+ p.y() * _max_width].get());
            i++;
        }
        return k;
    }
    else {
        return 1;
    }
}

//modifier
// void grid::update_garbage(){
//     for (cordinate j(0); j < _max_height; j++)  {
//         auto i(0);
//         while(i < _max_width){

//             if(_board[i + j * _max_width] !=nullptr && estMalus(position(i,j))){
//                 auto size(getSize(position(i,j)));
//                 if( hanging_garbage(position (i,j))){
//                     auto m(first_empty_line(position (i,j), size));
//                     for(int n(i);n<(i+size);n++){
//                         _board[n +m  * _max_width]=std::move(_board[n +j* _max_width] );
//                     }
//                 }
//                 i=i+size;
//             }
//             i++;

//         } 
//     } 
// }


std::vector<position > grid::garbage_adjacent(position const & p) const {
    std::vector<position > vec;
    // Vérification des voisins à droite
    if(p.x() < max_width() - 1 && _board[(p.x() + 1) + p.y() * _max_width] != nullptr && _board[(p.x() + 1) + p.y() * _max_width]->estmalus()) {
        vec.push_back(position(p.x() + 1, p.y()));
        //std::cout << "Right" << std::endl;
    }

    // Vérification des voisins à gauche
    if(p.x() >= 1 && _board[(p.x() - 1) + p.y() * _max_width] != nullptr && _board[(p.x() - 1) + p.y() * _max_width]->estmalus()) {
        vec.push_back(position(p.x() - 1, p.y()));
        //std::cout << "Left" << std::endl;
    }

    // Vérification des voisins en bas
    if(p.y() < max_height() - 1 && _board[p.x() + (p.y() + 1) * _max_width] != nullptr && _board[(p.x() ) + (p.y()+1) * _max_width]->estmalus()) {
        vec.push_back(position(p.x(), p.y() + 1));
        //std::cout << "Down" << std::endl;
    }

    // Vérification des voisins en haut
    if(p.y() >= 1 && _board[p.x() + (p.y() - 1) * _max_width] != nullptr && _board[(p.x() ) + (p.y()-1) * _max_width]->estmalus()) {
        vec.push_back(position(p.x(), p.y() - 1));
        // std::cout << "Up" << std::endl;
    }
    return vec;
}

//dans le cas ou il ya deux malus qui ont la meme hauteur 
void  grid::transform_to_cell(std::vector<position> const & align_cell, std::vector<position* > & pos_cells) {
    for (auto const & e : align_cell) {
        auto v(garbage_adjacent(e));
        for (auto const & p : v) {
            auto pst(first(p));
            auto taille(getSize(p));
            auto vec (generate_random_line(taille));
            for (auto i(pst.x());i<pst.x()+taille;i++){
                if(estMalus(position(i, pst.y()))){ //est malus teste deja si cest nullptr    
                    //_board[i+ pst.y() * _max_width].reset();
                    _board[i+ pst.y() * _max_width]=std::make_unique<cell>(vec[i-pst.x()]);
                    pos_cells.push_back(new position(i, pst.y() ));
                }else break;
            }
        }

    }
}

bool grid::before(position const & p) const{ 
    if (auto malus_cell = dynamic_cast<malusCell*>(_board[p.x()+ p.y() * _max_width].get())) 
        return malus_cell->next_left();
    else return false;

}
bool grid::after(position const & p) const{ 
    if (auto malus_cell = dynamic_cast<malusCell*>(_board[p.x()+ p.y() * _max_width].get()))
        return malus_cell->next_right();
    else return false;

}

position grid::first(position const & p) const{
    int i(0);

    if (auto malus_cell = dynamic_cast<malusCell*>(_board[p.x()+ p.y() * _max_width].get())) {
        
        while(malus_cell && malus_cell->next_left()){
            i++;
            malus_cell = dynamic_cast<malusCell*>(_board[p.x()-i+ p.y() * _max_width].get());
        }

    }
    return position(p.x()-i, p.y());
}


bool grid::under_bounds(position const & p) const{
    return p.x()>=0 && p.x()<_max_width && p.y()>=0 && p.y()<_max_height;
}

grid::grid(grid const & g)  {
        for (const auto& cellPtr : g._board) {
            if (cellPtr) {
                _board.push_back(cellPtr->clone());
            } else {
                _board.push_back(nullptr);
            }
        }
        _max_height=g._max_height;
        _max_width=g._max_width;
        nbr_colors=g.nbr_colors;
}


