#include "game.h"

game::game(cordinate _max_height, cordinate _max_width, int colors)
    : _grid(_max_height, _max_width, colors), _target(position(_max_width / 2, _max_height / 2), position(_max_width / 2, _max_height / 2 + 1)), _grid_dy(0), _score(0) {}

game & game::operator=(game const & g){
    if (this != &g) {
    _grid=g._grid;
    _target=g._target;
    _grid_dy=g._grid_dy;
    _score=g._score;
}
return *this;
}

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
        position p = position(i,0);
        if ((_grid(p) != t_colors::empty_cell && !is_garbage(p)) || (is_garbage(p) && not_hanging(p)))
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
    std::cout << "  ";
    for (unsigned int i(0); i < _grid.max_width(); i++)
        std::cout << " " << i;
    std::cout << std::endl;
    for (unsigned int j(0); j < _grid.max_height(); j++)
    {
        std::cout << ((j < 10) ? std::to_string(j)+" " : std::to_string(j));
        for (unsigned int i(0); i < _grid.max_width(); i++)
        {   //affichage avec la target 
            /* if ((_target.x1() == i && _target.y1() == j) || (_target.x2() == i && _target.y2() == j))
             {
                 std::cout << "|F";
                 continue;
            }*/
            if (_grid(position(i, j)) == t_colors::empty_cell)
            {
                std::cout << "| ";
            }

            else
            {
                if (_grid.estMalus(position(i, j)))
                {
                    std::cout << "|M";
                }
                else
                {
                    std::cout << "|" << toString_color(_grid(position(i, j)));
                }
            }
        }
        std::cout << "|\n";
    }
 
    std::cout << "   ";
    for (unsigned int k(0); k < _grid.max_width(); k++)
        std::cout << "_ ";
    std::cout << "\n  ";
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

bool game::switch_cells_position(position p1, position p2)
{
    // On echange dans la grille
    if (target_verticale() and one_case_empty(p1, p2))
        return false;
    return _grid.switch_cell(p1, p2);
}
void game::switch_cells_fall(position p1, position p2)
{
    _grid.switch_cell(p1, p2);
}

bool game::one_case_empty() const
{
    return ((getColor(this->getcell1target()) == t_colors::empty_cell) && (getColor(this->getcell2target()) != t_colors::empty_cell)) || ((getColor(this->getcell2target()) == t_colors::empty_cell) && (getColor(this->getcell1target()) != t_colors::empty_cell));
}
bool game::one_case_empty(position p1, position p2) const
{
    return getColor(p1) == t_colors::empty_cell or getColor(p2) == t_colors::empty_cell;
}
bool game::target_cells_empty() const
{
    return (getColor(this->getcell1target()) == t_colors::empty_cell) && (getColor(this->getcell2target()) == t_colors::empty_cell);
}

bool game::cells_above() const
{
    return ((getcell1target().y() - 1 > 0 && (getColor(position(getcell1target().x(), getcell1target().y() - 1)) != t_colors::empty_cell)) || (getcell2target().y() - 1 > 0 && (getColor(position(getcell2target().x(), getcell2target().y() - 1)) != t_colors::empty_cell)));
}
bool game::cells_above(position p1, position p2) const
{
    return p1.y() - 1 > 0 && (getColor(position(p1.x(), p1.y() - 1)) == t_colors::empty_cell or getColor(position(p2.x(), p2.y() - 1)) == t_colors::empty_cell);
}
bool game::switch_cells_target()
{
    // On echange dans la grille
    return _grid.switch_cell(position(_target.x1(), _target.y1()), position(_target.x2(), _target.y2()));
}

std::vector<position> game::vertical_alignment()const
{
    std::vector<position> vec;
    // alignement verticale
    for (cordinate i(0); i < _grid.max_width(); i++)
    {
        for (cordinate j(0); j < _grid.max_height()-2; j++)
        {
            if ( _grid(position(i,j))!=t_colors::empty_cell && _grid(position(i,j+1))!=t_colors::empty_cell && _grid(position(i,j+2))!=t_colors::empty_cell)
            { 
                if( _grid(position(i,j))==_grid(position(i,j+1)) && _grid(position(i,j))==_grid(position(i,j+2)) && !is_garbage(position(i, j)) && !is_garbage(position(i, j+1)) && !is_garbage(position(i, j+2)) && not_hanging(position(i, j)) && not_hanging(position(i, j+1)) && not_hanging(position(i, j+2))){ //alignement trouvé 
                    vec.push_back(position(i,j));
                    vec.push_back(position(i,j+1));
                    vec.push_back(position(i,j+2));
                    unsigned int k(j+3);
                    auto clr(_grid(position(i,j)));
                    // on ajoute tant que c'est la meme couleur
                    while (k < _grid.max_height()&& !is_garbage(position(i,k)) && (_grid(position(i, k)) == clr || _grid(position(i,k)) == t_colors::all))
                    {
                        vec.push_back(position(i, k));
                        k++;
                    }
                    return vec;
                }
            }

        }
        
    }

    vec.clear();
    return vec;
}

std::vector<position> game::horizontal_alignment()const
{
    std::vector<position> vec;
    for (cordinate j(0); j < _grid.max_height(); j++)
    {
        for (cordinate i(0); i < _grid.max_width()-2; i++)
        {
            if ( _grid(position(i,j))!=t_colors::empty_cell && _grid(position(i+1,j))!=t_colors::empty_cell && _grid(position(i+2,j))!=t_colors::empty_cell)
            { 
                if( _grid(position(i,j))==_grid(position(i+1,j)) && _grid(position(i,j))==_grid(position(i+2,j)) && !is_garbage(position(i, j)) && !is_garbage(position(i+1, j)) && !is_garbage(position(i+2, j)) && not_hanging(position(i, j)) && not_hanging(position(i+1, j)) && not_hanging(position(i+2, j))){ //alignement trouvé 
                    vec.push_back(position(i,j));
                    vec.push_back(position(i+1,j));
                    vec.push_back(position(i+2,j));
                    unsigned int k(i+3);
                    auto clr(_grid(position(i,j)));
                    // on ajoute tant que c'est la meme couleur
                    while (k < _grid.max_width() && !is_garbage(position(k,j)) && (_grid(position(k,j)) == clr || _grid(position(k, j)) == t_colors::all))
                    {
                        vec.push_back(position(k,j));
                        k++;
                    }
                    return vec;
                }
            }

        }
        
    }

    vec.clear();
    return vec;
}

std::vector<position> game::horizontal_alignment(std::vector<position> const &p) const
{
    std::vector<position> vec;
    bool trouve(false);
    t_colors clr = _grid(p[0]);

    for (cordinate  j(p[0].y()); j < p[p.size() - 1].y(); j++)
    { // on parcours seulement les lignes de l'alignement verticale
        vec.clear();
        for (cordinate i(0); i < _grid.max_width(); i++)
        {
            if (not_hanging(position(i, j)))
            { // vec.size()=2 et non 3
                if (trouve && vec.size() >= 2)
                { // on est passee par une case de l'align1 et on a trouvee un alignement
                    unsigned int k(i);
                    while (k < _grid.max_width() && (_grid(position(k, j)) == clr || _grid(position(k, j)) == t_colors::all))
                    {
                        vec.push_back(position(k, j));
                        k++;
                    }
                    return vec;
                }
                else if (clr == t_colors::all)
                {
                    vec.push_back(position(i, j));
                    clr = _grid(position(i, j));
                }
                else if (_grid(position(i, j)) != clr && _grid(position(i, j)) != t_colors::all)
                {                    vec.clear();

                    if(i>0 && _grid(position(i-1, j))==t_colors::all){
                        vec.push_back(position(i-1, j));
                    }
                }
                else if (std::find(p.begin(), p.end(), position(i, j)) != p.end())
                {
                    // on trouve une case qui est deja dans le premiere alignement
                    trouve = true;
                }
                else
                {// ==clr
                    vec.push_back(position(i, j));
                }
            }
            else
            {
                vec.clear();
            }
        }
    }

    if (trouve && vec.size() >= 2)
    { // alignement a la fin
        return vec;
    }
    vec.clear();
    return vec;
}

std::vector<position> game::alignment() const
{
    auto vec(vertical_alignment());
    if (vec.size() >=3)
    {
        auto vec1(horizontal_alignment(vec));
        if (vec1.size()>=3) // concat
            vec.insert(vec.end(), vec1.begin(), vec1.end());
        return vec;
    }
    else
    {
        auto vec2(horizontal_alignment());
        return vec2;
    }
}


void game::rotate_target()
{
    if (_target.isVertical() && _target.x1() < _grid.max_width() - 1)
        _target.setSense();
    else if (_target.isHorizontal() && _target.y1() < _grid.max_height() - 1)
        _target.setSense();
    // sinon le changement de sense est impossible on  fait rien
}

void game::slideColumn(cordinate x, std::vector<position *> &cells)
{     u_int16_t y = _grid.max_height() - 1;
    while (_grid(position(x, y)) != t_colors::empty_cell and y > 0)
    {
        y--;
    }
    while (_grid(position(x, y)) == t_colors::empty_cell and y > 0)
    {
        y--;
    }
    while (y > 0)
    {

        position* position_to_add = new position(x, y);
        if (std::find_if(cells.begin(), cells.end(), [&](position* p){ return *p == *position_to_add; }) == cells.end()){
            if ((_grid(position(x, y)) != t_colors::empty_cell) && !is_garbage(position(x, y))){
                cells.push_back(new position(x, y));
            }
           
            if(is_garbage(position(x,y)) /* and hanging_malus(position(x,y)) */){
                auto x_first_malus = firstMalus(position(x,y)).x();
                auto malus_size = getsize(position(x,y));
                for(t_number i(x_first_malus);i < malus_size+x_first_malus;i++){
                    cells.push_back(new position(i,y));
                }
            }
        }
        delete position_to_add;
        y--;
    }
}
void game::delete_cell(position const &x)
{
    _grid.delete_cell(x);
}

void game::add_new_row(int frame)
{
    // On ajoute une nouvelle ligne en faisant monter les cellules
    _grid.new_row(frame);

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
        _grid.place_cell(v[c], position(p.x(), p.y() + c));
}

float game::grid_dy() const
{
    return _grid_dy;
}

void game::inc_dy(delta const &d)
{
    _grid_dy += d;
}

void game::setWidth(size const &x)
{
    _grid.Setmax_width(x);
}
void game::setHeight(size const &x)
{
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

void game::setColors_numbers(t_number_color const &x)
{
    _grid.SetNbr_colors(x);
}
void game::init(t_number seed)
{
    _grid.init(seed);
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
    _grid.setCellDy(p, d);
}
void game::resetCellDelta(position p)
{
    _grid.resetCellDelta(p);
}
void game::setCellDx(position p, delta d)
{
    _grid.setCellDx(p, d);
}
std::vector<position> game::max_column() const
{
    return _grid.max_column();
}
std::vector<int>  game::highest_column() const{
    return _grid.highest_column();
}

void game::add_garbage(std::vector<position*> & malus)
{
    _grid.generate_garbage(malus);
}



bool game::hanging_malus_slide(position p,std::vector<position *> const &slide)
{
    return _grid.hanging_garbage_slide(p,slide);
}

bool game::not_hanging(position const &p) const
{
    return _grid.not_hanging(p);
}

score game::get_score() const
{
    return _score;
}

void game::inc_score(score x)
{
    _score += x;
}

void game::reset_score()
{
    _score = 0;
}

bool game::is_garbage(position const &p) const
{
    return _grid.estMalus(p);
}


void game::transform_malus_to_cell(std::vector<position> const &align_cell, std::vector<position *> &pos_cells)
{
    _grid.transform_to_cell(align_cell, pos_cells);
}

// ai 


ai::ai(cordinate _max_height, cordinate _max_width, int colors, t_num frame,t_num depth)
    : game(_max_height, _max_width, colors), frequence_frame(frame),_depth(depth) {}

std::vector<t_action> ai::getPath(position const &p1, position const &p2)
{

    std::vector<t_action> vec;
    bool rotate(false);
    if (under_bounds(p1) && under_bounds(p2))
    {
        auto difX(p1.x() - getcell1target().x());
        auto difY(p1.y() - getcell1target().y());
        // ajuster la la colone
        if (difX > 0)
        {                                                       // il faut se deplacer vers la droite
            if (!under_bounds(position(p2.x() + difX, p2.y()))) // on verifie si la deuxieme case du target depassent pas
            {
                vec.push_back(t_action::change_direction);
                vec.insert(vec.end(), difX, t_action::go_right);
                rotate = true;
            }
            else
                vec.insert(vec.end(), difX, t_action::go_right);
        }
        else if (difX < 0) // si =0 pas besoin de se deplacer en largeur
            vec.insert(vec.end(), -1 * difX, t_action::go_left);
        // ajuster la rotation du target
        if (target_verticale() != target(p1, p2).isVertical() && !rotate)
        { // si le sense du target actuelle et du target pour faire switch les deux position sont different
            vec.push_back(t_action::change_direction);
        }
        // ajuster la ligne
        if (difY > 0) // il faut descendre
            vec.insert(vec.end(), difY, t_action::go_down);
        else if (difY < 0) // si =0 pas besoin de se deplacer en hauteur
            vec.insert(vec.end(), -1 * difY, t_action::go_up);

        vec.push_back(t_action::exchange);
    }
    else
    {
       // std::cout << "changement impossible à faire " << std::endl;
    }
    return vec;
}

t_num ai::color_distances(position const &p1, position const &p2) const
{
    return (abs(p2.x() - p1.x()) + abs(p2.y() - p1.y()));
}

t_num ai::sum_color_distance(grid const & grille) const
{ //+ la somme est grande + il ya des case cote à cote
    int cpt(0);
     for (cordinate j(0); j < grille.max_height()-1; j++)
    {
        for (cordinate i(0); i < grille.max_width()-1; i++)
        {
            if(grille(position(i, j)) != t_colors::empty_cell){
                if(grille(position(i, j)) ==grille(position(i+1, j)) ){
                    cpt+=1;
                } 
                if(grille(position(i, j)) ==grille(position(i, j+1)) ){
                    cpt+=1;
                }

            }
        }}
    return cpt;
}

int ai::estimation(game const &g)
{
    int count(0);
    game gm(g);
    auto vec(gm.alignment());
    bool first_bonus(false);
    bool snd_bonus(false);
    // parcourir les alignement et voir si il y'a des alignement sur les colones les plus haute si c'est le cas maximiser l'estimation
    auto colonnes_hautes(highest_column());
    for (auto const &pst : vec)
    {
        if (std::find(colonnes_hautes.begin(), colonnes_hautes.end(), pst.x()) != colonnes_hautes.end() && !first_bonus)
        {
            count += 100;
            first_bonus=true;
        }
        if((g.getGrid().garbage_adjacent(pst)).size()>0 && !snd_bonus){
            count+=200;
            snd_bonus=true;
        }
        if(first_bonus==true && snd_bonus){ //si on est rentré dans l'une des condition d'avant pas besoin de continuer de parcourir les alignement
            break;
        }
    }
    count += vec.size()*100;
    count += sum_color_distance(gm.getGrid());

    return count;
}

std::vector<blow> ai::lawful_blow(grid const &grille) const
{
    std::vector<blow> vec;
    for (unsigned int j(0); j < grille.max_height(); j++)
    {   for (unsigned int i(0); i < grille.max_width() ; i++)
        {
            // si horizontale une des deux cases ne doit pas etre vide sinn verticale les deux ne doivent pas etre vide
            //aussi sa ne sert a rien de switch deux cases de la meme couleur
            if(grille.cellDx(position(i, j))==0 && grille.cellDy(position(i, j))==0 && !is_garbage(position(i, j))){
                if (i+1< grille.max_width() && grille.cellDx(position(i+1, j))==0 && grille.cellDy(position(i+1, j))==0 && grille(position(i, j)) != grille(position(i + 1, j)) && !is_garbage(position(i+1, j)))
                {
                    vec.push_back(blow{position(i, j), position(i + 1, j)});
                }
                if(j+1<grille.max_height() && grille.cellDx(position(i, j+1))==0 && grille.cellDy(position(i, j+1))==0 &&(grille(position(i, j)) != t_colors::empty_cell && grille(position(i, j + 1)) != t_colors::empty_cell) && grille(position(i, j)) != grille(position(i, j+1)) && !is_garbage(position(i, j+1)))
                {
                    vec.push_back(blow{position(i, j), position(i, j + 1)});
                }
           }
        }
        
    }
    return vec;
}

int ai::Max(int profondeur,game const &g)
{  
    auto x(g);
    if (profondeur == 0)
    {
        return estimation(x);
    }
    auto blows(lawful_blow(x.getGrid()));
    int meilleurEstimation = std::numeric_limits<int>::min();
    // Parcours de tous les blows possibles
    for (auto blow : blows)
    {
        // Simulation du blow
        x.switch_cells_position(blow.p1, blow.p2);
        // Récursion pour évaluer les blows possibles
        int estimationblow =  Max(profondeur - 1,x);
        // Annulation de la simulation du blow
        x.switch_cells_position(blow.p1, blow.p2);
        // Mise à jour de la meilleure estimation
        meilleurEstimation = std::max(meilleurEstimation, estimationblow);
    }

    return meilleurEstimation; // Retourne l'estimation optimale pour le joueur actuel
}

std::vector<blow> ai::best_blow(int profondeur)
{   std::vector<blow> meilleursblows;
    game g(*this);
    auto psts(g.max_column());
    if(psts[0].y()<=2){//si la colone la plus haute est proche de la fin 
        if(psts[0].x()>0) //si la premiere colone la plus haute c'est pas la colone [0]
        { //on jette la case à gauche
            blow c{position (psts[0].x()-1,psts[0].y()),position(psts[0].x(),psts[0].y())};
            meilleursblows.push_back(c);
            return meilleursblows;

        }else if(psts.size()==1 || psts[1].x()!=1){ //si la 1ere colone est une max_column et que il n'ya rien à sa droite 
        //on jette la case à droite
            blow c{position (psts[0].x()+1,psts[0].y()),position(psts[0].x(),psts[0].y())};
            meilleursblows.push_back(c);
            return meilleursblows;

        }else if(psts[psts.size()-1].x()<width()-1){ //si la derniere colonnes la plus haute n'est pas la colone width-1
        //on jette la deniere  case à droite
        blow c{position (psts[psts.size()-1].x()+1,psts[psts.size()-1].y()),position(psts[psts.size()-1].x(),psts[psts.size()-1].y())};
            meilleursblows.push_back(c);
            return meilleursblows;      
        }
        
    }
    auto blows(lawful_blow(g.getGrid()));
    while(blows.size()==0){
        blows=lawful_blow(getGrid());
    }
    int meilleureEstimation = std::numeric_limits<int>::min();
    for (auto cp : blows)
    {        g.switch_cells_position(cp.p1, cp.p2);
        int estimationblow =  Max(profondeur,g);

        g.switch_cells_position(cp.p1, cp.p2); // annuler le blow

        if (estimationblow > meilleureEstimation)
        {
            meilleursblows.clear();
            meilleursblows.push_back(cp);
            meilleureEstimation = estimationblow;
        }else if(estimationblow == meilleureEstimation){
            meilleursblows.push_back(cp);
        }
    }

    if(meilleureEstimation<5){ //le coup ne vaut pas le cout d'etre jouer vaut mieux faire accelerate la grille
        meilleursblows.clear();
    }
    return meilleursblows;
}


std::vector<t_action> ai::play_what()
{ 
    auto vec(best_blow(_depth));
    std::vector<t_action> blows;

    if(vec.size()>0){ // si il y'a au moins un bon coup à jouer
    auto i(nombreAleatoire(vec.size()-1)); //on prend aleatoirement l'un des meilleur coup
    auto blow(vec[i]);
     blows=getPath(blow.p1, blow.p2); //et on retourne le chamin d'actoin pour executer ce coup
    }
    else //sinon on retourne l'action accelerate 
    {
        blows.push_back(t_action::accelerate);
    }
    return blows;
}
t_action ai::getBlow(t_num frame)
{
   
    if (frame % frequence_frame == 0)
    {
        if (path.size() == 0)
        {
            path = play_what();
        } 
        t_action act(path[0]);
        //print_container();
        path.erase(path.begin());
        return (act);
    }
    else
        return t_action::nothing;
}
void ai::setAction(t_action const & a) {
   if(a==t_action::accelerate){
        path.insert(path.begin(),a);
    }
}
void ai::print_container()
{
    std::cout << "chemin \n";
    for (auto x : path)
    {
        switch (x)
        {
        case t_action::go_right:
        {
            std::cout << "Right ";
            break;
        }
        case t_action::go_left:
        {
            std::cout << "left ";
            break;
        }
        case t_action::go_up:
        {
            std::cout << "up ";
            break;
        }
        case t_action::go_down:
        {
            std::cout << "Down ";
            break;
        }
        case t_action::change_direction:
        {
            std::cout << "Rotate ";
            break;
        }
        case t_action::exchange:
        {
            std::cout << "swicth ";
            break;
        }
        default:{} //jamais atteint
        }
    }
}
// remote_game
/**
 * @brief transforme un t_action en std::string
 * @param action a transformer
 * @return version string de l'action
 */
std::string actionToString(t_action action) {
    switch (action) {
    case t_action::go_right: return "go_right";
    case t_action::go_left: return "go_left";
    case t_action::go_up: return "go_up";
    case t_action::go_down: return "go_down";
    case t_action::change_direction: return "change_direction";
    case t_action::accelerate: return "accelerate";
    case t_action::exchange: return "exchange";
    case t_action::nothing: return "nothing";
    case t_action::generate_malus: return "generate_malus";
    case t_action::pause: return "pause";
    case t_action::resume: return "resume";
    default: return "";
    }
}

sf::Packet &operator << (sf::Packet& packet, const t_action& action) {
    packet << static_cast<unsigned int>(action);
    return packet;
}

sf::Packet &operator >> (sf::Packet& packet, t_action& action) {
    unsigned int action_value;
    packet >> action_value;
    action = static_cast<t_action>(action_value);
    return packet;
}

remote_game::remote_game(cordinate _max_height, cordinate _max_width, t_number_color colors) :
    game(_max_height, _max_width, colors), _socket()
{}

/**
 * @brief envoi une action a travers la socket
 * @param action a envoyer
 * @return status de l'envoi
 */
sf::Socket::Status remote_game::send_action(const t_action &action)
{
    sf::Packet packet;
    packet << action;

    sf::Socket::Status send_status(_socket.send(packet));
    return send_status;
}

/**
 * @brief reçoie un nombre a travers la socket
 * @param nombre reçu
 * @return status de la reception
 */
sf::Socket::Status remote_game::recieve_number(t_number &number)
{   
    sf::Packet packet;
    sf::Socket::Status recieve_status(_socket.receive(packet));

    if (recieve_status == sf::Socket::Done && packet.getDataSize() > 0)
    {
        packet >> number;
        packet.clear();
    }
    return recieve_status;
}

/**
 * @brief envoi un nombre a travers la socket
 * @param nombre a envoyer
 * @return status de l'envoi
 */
sf::Socket::Status remote_game::send_number(const t_number &number)
{
    sf::Packet packet;
    packet << number;
    sf::Socket::Status send_status(_socket.send(packet));
    return send_status;
}

/**
 * @brief reçoie une chaine de caractere a travers la socket
 * @param chaine de caractere reçue
 * @return status de la reception
 */
sf::Socket::Status remote_game::recieve_string(std::string &message)
{
    sf::Packet packet;
    sf::Socket::Status recieve_status(_socket.receive(packet));

    if (recieve_status == sf::Socket::Disconnected)
    {
        _socket.disconnect();
    }
    else if (recieve_status == sf::Socket::Done && packet.getDataSize() > 0)
    {
        packet >> message;
        packet.clear();
    }
    return recieve_status;
}

/**
 * @brief envoi une chaine de caractere a travers la socket
 * @param chaine de caractere a envoyer
 * @return status de l'envoi
 */
sf::Socket::Status remote_game::send_string(const std::string &message)
{
    sf::Packet packet;
    packet << message;
    sf::Socket::Status send_status(_socket.send(packet));
    return send_status;
}

/**
 * @brief reçoie une action a travers la socket
 * @param action reçue
 * @return status de la reception
 */
sf::Socket::Status remote_game::recieve_action(t_action &action)
{
    sf::Packet packet;
    sf::Socket::Status recieve_status(_socket.receive(packet));

    std::string statusStr;

    switch (recieve_status) {
    case sf::Socket::Status::Done:
        statusStr = "Done";
        break;
    case sf::Socket::Status::NotReady:
        statusStr = "Not Ready";
        break;
    case sf::Socket::Status::Partial:
        statusStr = "Partial";
        break;
    case sf::Socket::Status::Disconnected:
        statusStr = "Disconnected";
        break;
    case sf::Socket::Status::Error:
        statusStr = "Error";
        break;
    default:
        statusStr = "Unknown";
        break;
    }
    if (recieve_status == sf::Socket::Disconnected)
    {
        _socket.disconnect();
    }
    else if (recieve_status == sf::Socket::Done && packet.getDataSize() > 0)
    {
        packet >> action;
        packet.clear();
    }
    return recieve_status;
}

server::server(unsigned int port, cordinate _max_height, cordinate _max_width, t_number_color colors) :
    remote_game(_max_height, _max_width, colors), _listner(), _port(port)
{
    _listner.setBlocking(false);
    _listner.listen(_port);
}

/**
 * @brief accapte une connexion entrante (et la mettant en non bloquante)
 */
void server::connect_client()
{
    _socket.setBlocking(false);
    _listner.accept(_socket);
}

client::client(cordinate _max_height, cordinate _max_width, t_number_color colors) :
    remote_game(_max_height, _max_width)
{}

/**
 * @brief envoi une demande de connexion
 * @param server_ip adresse ip de la destination
 * @param port port de destination
 */
void client::connect(const sf::IpAddress &server_ip, unsigned int port)
{
    _socket.setBlocking(false);
    _socket.connect(server_ip, port);
}
