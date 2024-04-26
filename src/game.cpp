#include "game.h"

game::game(cordinate _max_height, cordinate _max_width, int colors)
    : _grid(_max_height, _max_width, colors), _target(position(_max_width / 2, _max_height / 2), position(_max_width / 2, _max_height / 2 + 1)), _grid_dy(0), _score(0) { _grid.init(); /* TODO: Enlever */ }

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
position game::drop_position(position const &p) const
{
    unsigned int j(p.y());
    while ((j + 1) < _grid.max_height() && _grid(position(p.x(), j + 1)) == t_colors::empty_cell)
    {
        j++;
    }
    return position(p.x(), j);
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
void game::drop()
{
    if (getColor(getcell1target()) == t_colors::empty_cell)
    {
        position p(getcell2target()); // la position ou se troyve la case qui doit tomber
        auto position_final(drop_position(p));
        _grid.switch_cell(p, position_final);
    }
    else
    {
        position p(getcell1target());
        auto position_final(drop_position(p));
        _grid.switch_cell(p, position_final);
    }
}
void game::drop(position p1, position p2)
{
    if (one_case_empty(p1, p2))
    {
        if (_grid(p1) == t_colors::empty_cell)
        {
            auto fall_pos = drop_position(p1);
            _grid.switch_cell(p1, fall_pos);
        }
        else
        {
            auto fall_pos = drop_position(p2);
            _grid.switch_cell(p2, fall_pos);
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
    std::vector<position> vec;
    t_colors clr;
    // alignement verticale
    for (unsigned int i(0); i < _grid.max_width(); i++)
    {
        for (unsigned int j(0); j < _grid.max_height()-2; j++)
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

std::vector<position> game::horizontal_alignment()
{
   std::vector<position> vec;
    t_colors clr;
    for (unsigned int j(0); j < _grid.max_height(); j++)
        {
        for (unsigned int i(0); i < _grid.max_width()-2; i++)
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

std::vector<position> game::horizontal_alignment(std::vector<position> const &p)
{
    std::vector<position> vec;
    bool trouve(false);
    t_colors clr = _grid(p[0]);

    for (unsigned int j(p[0].y()); j < p[p.size() - 1].y(); j++)
    { // on parcours seulement les lignes de l'alignement verticale
        vec.clear();
        for (unsigned int i(0); i < _grid.max_width(); i++)
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
                { //==clr
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

std::vector<position> game::alignment()
{
    auto vec(vertical_alignment());
    if (vec.size() >=3)
    {
        auto vec1(horizontal_alignment(vec));
        if (vec1.size()>=3) // concat
            vec.insert(vec.end(), vec1.begin(), vec1.end());
        //inc_score(vec.size());
        return vec;
    }
    else
    {
        auto vec2(horizontal_alignment());
       // inc_score(vec2.size());
        return vec2;
    }
}

void game::delete_alignement(std::vector<position> const &v)
{
    for (auto i(v.size() - 1); i > 0; i--)
    {
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

void game::slideColumn(cordinate x, std::vector<position *> &cells)
{ // x la colone
    // x la colone
    u_int16_t y = _grid.max_height() - 1;
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
        auto position_to_add(new position(x, y));
        if (std::find(cells.begin(), cells.end(), position_to_add) == cells.end()){
            if ((_grid(position(x, y)) != t_colors::empty_cell) && !is_garbage(position(x, y)))
                cells.push_back(new position(x, y));
            else if (is_garbage(position(x,y))) {
                std::cout << "position: x= " << x << ", y= "<< y << "\n";
                std::cout << "garbage: " << is_garbage(position(x,y)) << ", hanging: "<< hanging_malus(position(x,y)) << "\n";
            }
            if(is_garbage(position(x,y)) and hanging_malus(position(x,y))){
                std::cout << "garbage: x= " << x << ", y= "<< y << "\n";
                auto x_first_malus = firstMalus(position(x,y)).x();
                auto malus_size = getsize(position(x,y));
                for(t_number i(x_first_malus);i < malus_size+x_first_malus;i++){
                    std::cout << "added: " << toString_color(_grid(position(i,y))) << ", at position " << i << ", " << y << "\n";
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
void game::init()
{
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

bool game::hanging_malus(position p)
{
    return _grid.hanging_garbage(p);
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

void game::update_garbage_height() 
{
    _grid.update_garbage();
}

void game::transform_malus_to_cell(std::vector<position> const &align_cell, std::vector<position *> &pos_cells)
{
    _grid.transform_to_cell(align_cell, pos_cells);
}

ai::ai(cordinate _max_height ,cordinate _max_width ,int colors )
    :game(_max_height,_max_width,colors){}



std::vector<t_action> ai::chemin(position const & p1,position const & p2){

std::vector<t_action> vec;
bool rotate(false);
if(under_bounds(p1) && under_bounds(p2)){
    auto difX(p1.x()-getcell1target().x());
    auto difY(p1.y()-getcell1target().y());
    //ajuster la la colone
    if(difX>0){ //il faut se deplacer vers la droite
        if(! under_bounds(position(p2.x()+difX,p2.y()))) //on verifie si la deuxieme case du target depassent pas
        {   vec.push_back(t_action::change_direction);
            vec.insert(vec.end(), difX, t_action::go_right);
            rotate=true;
        }
        else vec.insert(vec.end(), difX, t_action::go_right);
    }
    else if(difX<0) //si =0 pas besoin de se deplacer en largeur 
        vec.insert(vec.end(), -1*difX, t_action::go_left);
    //ajuster la rotation du target
    if(target_verticale() != target(p1,p2).isVertical() && !rotate){ //si le sense du target actuelle et du target pour faire switch les deux position sont different 
        vec.push_back(t_action::change_direction);
    }
    //ajuster la ligne
    if(difY>0) //il faut descendre
        vec.insert(vec.end(), difY, t_action::go_down);
    else if(difX<0) //si =0 pas besoin de se deplacer en hauteur 
        vec.insert(vec.end(), -1*difY, t_action::go_up);

    vec.push_back(t_action::exchange);
}else {
    std::cout<<"changement impossible à faire "<<std::endl;
}
return vec;
}


t_num ai::color_distances(position const & p1,position const & p2) const{
    return (abs(p2.x()-p1.x())+abs(p2.y()-p1.y()));
}

t_num ai::sum_color_distance() const{ //+ la somme est petite + les cases de meme couleur sont proches
    int cpt(0);
    std::vector<std::vector<position>> vec_colors(8);
    for (unsigned int j(0); j < _grid.max_height(); j++)
    {
        for (unsigned int i(0); i < _grid.max_width(); i++)
        {
            switch(_grid(position(i, j))){
                case t_colors::empty_cell: break; //l'odre des couleur dans le vec est important (difficulty)
                case t_colors::blue: vec_colors[0].push_back(position(i, j)); break;
                case t_colors::sky_blue : vec_colors[1].push_back(position(i, j));break;
                case t_colors::purple : vec_colors[2].push_back(position(i, j));break;
                case t_colors::orange : vec_colors[3].push_back(position(i, j));break;
                case t_colors::yellow : vec_colors[4].push_back(position(i, j));break;
                case t_colors::white : vec_colors[5].push_back(position(i, j));break;
                case t_colors::pink : vec_colors[6].push_back(position(i, j));break;
                case t_colors::green : vec_colors[7].push_back(position(i, j));break;
            }
        }
    }
    // on a recuperé les vecteur avec pour chaque couleur toutes les positions
    for(auto const & vec : vec_colors ){//pour chaque vec de couleures
    //pour chaque position son calcule sa distance avec toutes les autre positions de meme couleur
        for(unsigned int i(0) ; i <vec.size() ; i++){
            for(unsigned int j(i+1);j<vec.size();j++){
                cpt+=color_distances(vec[j],vec[i]);
            }
        }
    } 
    return cpt;
}

int ai::estimation() {
    int count(0);
    auto vec(alignment());
    //parcourir les alignement et voir si il y'a des alignement sur les colones les plus haute si c'est le cas maximiser l'estimation
    auto colonnes_hautes (highest_column());
    for(auto const & pst : vec){
       if( std::find(colonnes_hautes.begin(),colonnes_hautes.end(),pst.x()) != colonnes_hautes.end()){
            count += 100;
       }
    }
    count += vec.size();
    count += static_cast<int>(1/sum_color_distance())*100;

    return count;
}

std::vector<coup> ai::lawful_blow() const{
  std::vector<coup> vec;  
    for (unsigned int j(0); j < _grid.max_height()-1; j++)
        {
        for (unsigned int i(0); i < _grid.max_width()-1; i++){
            if(_grid(position(i, j))!=t_colors::empty_cell || _grid(position(i+1, j))!=t_colors::empty_cell)
            {
                vec.push_back(coup{position(i, j),position(i+1, j)});
            }
            if(_grid(position(i, j))!=t_colors::empty_cell || _grid(position(i,j+1))!=t_colors::empty_cell)
            {
                vec.push_back(coup{position(i, j),position(i, j+1)});
            }
        }
    }
    return vec;
}

int ai::minMax(int profondeur) {
    if (profondeur == 0) {
        return estimation();
    }
    auto coups (lawful_blow());
    int meilleurEstimation =  std::numeric_limits<int>::min();

    // Parcours de tous les coups possibles
    for (auto coup : coups) {
        // Simulation du coup
        switch_cells_position(coup.p1,coup.p2);
        // Récursion pour évaluer les coups possibles
        int estimationCoup = minMax(profondeur - 1);
        // Annulation de la simulation du coup
        switch_cells_position(coup.p1,coup.p2);
        // Mise à jour de la meilleure estimation
        meilleurEstimation = std::max(meilleurEstimation, estimationCoup);
    }

    return meilleurEstimation; // Retourne l'estimation optimale pour le joueur actuel
}
coup ai::best_blow(int profondeur) {
    auto coups (lawful_blow());
    coup meilleurCoup {position(0,0),position(0,0)}; //car doit étre initialisé
    int meilleureEstimation = std::numeric_limits<int>::min();
    for (auto cp : coups) {
        switch_cells_position(cp.p1,cp.p2);
        int estimationCoup = minMax(profondeur);
        switch_cells_position(cp.p1,cp.p2); //annuler le coup

        if (estimationCoup > meilleureEstimation) {
            meilleurCoup = cp;
            meilleureEstimation = estimationCoup;
        }
    }

    return meilleurCoup;
}

std::vector<t_action> ai::play_what(){
    auto coup (best_blow(1));
    return chemin(coup.p1,coup.p2);
}

class remote_game : public game {
public:
    remote_game(cordinate _max_height = 12, cordinate _max_width = 6, t_number_color colors = 4);
    void recieve_action();
    void send_action(const t_action &action);
    void recieve_number();
    void send_number(const t_number &number);
    bool connected() const { return _socket.getRemoteAddress() != sf::IpAddress::None; }
    virtual t_remote_game type() const =0;

protected:
    sf::TcpSocket _socket;
};

class server : public remote_game {
public:
    server(unsigned int port, cordinate _max_height = 12, cordinate _max_width = 6, t_number_color colors = 4);
    t_remote_game type() const override {return t_remote_game::server;}
    void connect_client();

private:
    sf::TcpListener _listner;
    unsigned int _port;
};

class client : public remote_game {
public:
    client(cordinate _max_height = 12, cordinate _max_width = 6, t_number_color colors = 4);
    t_remote_game type() const override {return t_remote_game::client;}
    void connect(const sf::IpAddress &server_ip, unsigned int port);

};
