#pragma once
#include "grid.h"
#include "cell.h"
#include "target.h"
#include <SFML/Network.hpp>
#include <algorithm>
#include <iostream>
#include <cmath>

using score = u_int16_t;
using t_num=u_int16_t;
enum class t_action{
    go_right, go_left, go_up, go_down, change_direction, accelerate, exchange, nothing, generate_malus, pause, resume
};

enum class t_direction{
    up,
    down,
    right,
    left
};

struct blow{
    position p1;
    position p2;
};

class game{

public:
    game(cordinate _max_height=12,cordinate _max_width=6,int colors=4);
    game(game const & g)=default;
   	game & operator=(game const & g);
    bool is_lost(); //teste si le joueur a perdu
    void move_target(t_direction dir);
    void show() const; //affichage de la grille
    bool switch_cells_position(position p1 ,position p2); //echange deux position aprés avoir fait une verification
    void switch_cells_fall(position p1 ,position p2); //
    bool switch_cells_target();
    bool one_case_empty(position p1,position p2) const;
    bool one_case_empty() const; //return true si une deux cases du target est vide utilie pour determiner ce qui doit ou non etre fait apres le switch
    bool target_cells_empty() const; //return true si le viseur est sur deux cases vides (il n'ya pas de switch a faire alors)
    bool cells_above() const;//il y'a des cases au dessus de la cases au dessus du target
    bool cells_above(position p1,position p2) const;
    std::vector<position>  vertical_alignment() const;
    std::vector<position> horizontal_alignment() const;
    std::vector<position> horizontal_alignment(std::vector<position> const & p) const; //retourne les alignement horizontale qui sont adjacetn a l'align vertical prit en paramettre
    std::vector<position>  alignment() const;
    position getcell1target() const; //recupere la position de la premiere case du viseur
    position getcell2target() const;
    t_colors getColor(position const & p) const; //recupere la couleur de la case qui a pour position pair
    t_colors operator()(position const & p)const;
    void rotate_target(); //change le sense de la target
    void slideColumn(cordinate x,std::vector<position *> & cells);//ajoute la colonne a la coordonné x au vecteur qui est chargée de faire tomber les cases 
    void delete_cell(position const &x); //supprimer une case
    void add_new_row(int frame=0);//genere une nouvelle ligne
    void setGrid_dy(float newGrid_dy);
    void place_new_case(position p,std::vector<cell> v);
    float grid_dy()const;
    void inc_dy(delta const & d);
    void setWidth(size const & x);
    void setHeight(size const & x);
    size height() const;
    size width() const;
    void setColors_numbers(t_number_color const & x);
    void init(t_number seed = 0);
    bool target_verticale()const; //retourne vrai si la target est vertical
    delta cellDx(position p)const ;
    delta cellDy(position p)const ; 
    void setCellDx(position p,delta d);
    void setCellDy(position p,delta d);
    void resetCellDelta(position p);
    std::vector<position>  max_column() const; //retourne les position des cases les plus hautes dans la grille
    std::vector<int>  highest_column() const; //retourne les indices des colones les plus hautes
    void add_garbage(std::vector<position*> & malus); //genere un malus
    bool hanging_malus_slide(position p,std::vector<position *> const &slide); //retourne vrai si le mlus est suspendu
    bool not_hanging(position const & p) const; //retourne vrai si la case à la position p n'est pas suspendu
    score get_score()const;
    void inc_score(score x);
    void reset_score();
    bool is_garbage (position const & p)const; //retourne vrai si la case à la position p ets un malus
    void transform_malus_to_cell(std::vector<position> const & align_cell,std::vector<position *> &pos_cells);  //transforme tout les malus adjacent au vecteur d'alignment en case normal et les ajoute à pos_cell pour les faire tomber 
    size getsize(position const & p) const{return _grid.getSize(p);} // retourne la taille de la case qui a pour position p (1 si c'est une case normal) 
    bool after(position const & p) const{return _grid.after(p);} //retourne vrai si la case a un suivnt rataché
    bool before(position const & p) const{return _grid.before(p);}
    position firstMalus(position const & p) const {return _grid.first(p);} //pour une case du malsu donné elle retourne la position de la 1 ere case du meme malus
    bool under_bounds(position const & p) const { return _grid.under_bounds(p); }
    virtual bool is_ai() const {return false;}
    virtual bool is_remote() const {return false;} 
    const grid &   getGrid() const{return _grid;}
    virtual void setAction(t_action const & a){_next_action=a;}
    virtual t_action getBlow(t_num frame)  { return _next_action;} //retourne le prochain coup à jouer
    virtual void print_container(){ std::cout<<"joueur \n";};
private:
    t_action _next_action;
    grid _grid;
    target _target;
    float _grid_dy;
    score _score ;
    
};

class ai : public game{
public:
    ai(cordinate _max_height=12,cordinate _max_width=6,int colors=4,t_num frame=15,t_num depth=0);
    std::vector<t_action> getPath(position const & p1,position const & p2); //retourne le chemin d'action pour arriver à p2 à partir de p1
    t_num color_distances(position const & p1,position const & p2) const; //la distance entre deux position
    t_num sum_color_distance(grid const & grille) const; //calcule le nombre de cases qui ont des case de meme couleur adjacente
    int estimation(game const &g)  ; //donne une evalution de la qualité de la config de jeu de G
    std::vector<blow> lawful_blow(grid const &grille) const; //retourne tout les coups licites sauf si deux cases vides aucun interet
    int  Max(int profondeur,game const &g);  
    std::vector<blow> best_blow(int profondeur) ; //retourne les meilleur coup à jouer
    std::vector<t_action> play_what() ; //retourne le chemin d'action pour executer le meilleur coup
    bool is_ai() const override{return true;}
    void setAction(t_action const & a) override;
    t_action getBlow(t_num frame) override ;
    void print_container() override; //affiche path
private:
    std::vector<t_action> path;
    t_num frequence_frame;
    t_num _depth;
};


// remote_game
sf::Packet &operator <<(sf::Packet& packet, const t_action& action);
sf::Packet& operator >>(sf::Packet& packet, t_action& action);
std::string actionToString(t_action action);

enum class t_remote_game
{
    server,
    client
};

class remote_game : public game {
public:
    remote_game(cordinate _max_height = 12, cordinate _max_width = 6, t_number_color colors = 4);
    sf::Socket::Status recieve_action(t_action &action);
    sf::Socket::Status send_action(const t_action &action);
    sf::Socket::Status recieve_number(t_number &number);
    sf::Socket::Status send_number(const t_number &number);
    sf::Socket::Status recieve_string(std::string &message);
    sf::Socket::Status send_string(const std::string &message);
    bool connected() const { return _socket.getRemoteAddress() != sf::IpAddress::None; }
    virtual t_remote_game type() const =0;
    bool is_remote() const override {return true;}

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
