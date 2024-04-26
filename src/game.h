#pragma once
#include "grid.h"
#include "cell.h"
#include "target.h"
#include <algorithm>
#include <iostream>
#include <cmath>

using score = u_int16_t;
using t_num=u_int16_t;
enum class t_action{
    go_right, go_left, go_up, go_down, change_direction, accelerate, exchange, nothing, generate_malus
};

enum class t_direction{
    up,
    down,
    right,
    left
};

struct coup{
    position p1;
    position p2;
};

class game{
friend class ai; //ai doit pouvoir acceder a tout les attribus de game surtt grid

public:
    game(cordinate _max_height=12,cordinate _max_width=6,int colors=4);
    bool is_lost();
    void move_target(t_direction dir);
    void show() const;
    bool switch_cells_position(position p1 ,position p2);
    void switch_cells_fall(position p1 ,position p2);
    bool switch_cells_target();
    bool one_case_empty(position p1,position p2) const;
    bool one_case_empty() const; //return true si une deux cases du target est vide utilie pour determiner ce qui doit ou non etre fait apres le switch
    bool target_cells_empty() const; //return true si le viseur est sur deux cases vides (il n'ya pas de switch a faire alors)
    position drop_position(position const & p) const ; // recupere la position ou doit tomber la case qui est suspendu
    void drop();
    void drop(position p1,position p2); 
    bool cells_above() const;//il y'a des cases au dessus de la cases au dessus du target
    bool cells_above(position p1,position p2) const;
    std::vector<position>  vertical_alignment();
    std::vector<position> horizontal_alignment();
    std::vector<position> horizontal_alignment(std::vector<position> const & p); //retourne les alignement horizontale qui sont adjacetn a l'align vertical prit en paramettre
    std::vector<position>  alignment();
    void delete_alignement(std::vector<position>  const & v);
    position getcell1target() const; //recupere la position de la premiere case du viseur
    position getcell2target() const;
    t_colors getColor(position const & p) const; //recupere la couleur de la case qui a pour position pair
    t_colors operator()(position const & p)const;
    void rotate_target();
    void slideColumn(cordinate x,std::vector<position *> & cells);
    std::vector<position> slidecolumn_start_position(cordinate const & x); //recupere les position des des cases qui doivent tomber
    void delete_cell(position const &x);
    void add_new_row(int frame=0);
    void setGrid_dy(float newGrid_dy);
    void place_new_case(position p,std::vector<cell> v);
    float grid_dy()const;
    void inc_dy(delta const & d);
    void setWidth(size const & x);
    void setHeight(size const & x);
    size height() const;
    size width() const;
    void setColors_numbers(t_number_color const & x);
    void init();
    bool target_verticale()const;
    delta cellDx(position p)const ;
    delta cellDy(position p)const ; 
    void setCellDx(position p,delta d);
    void setCellDy(position p,delta d);
    void resetCellDelta(position p);
    std::vector<position>  max_column() const;
    std::vector<int>  highest_column() const;
    void add_garbage(std::vector<position*> & malus);
    bool hanging_malus(position p);
    bool not_hanging(position const & p) const;
    score get_score()const;
    void inc_score(score x);
    void reset_score();
    bool is_garbage (position const & p)const;
    void update_garbage_height();
    void transform_malus_to_cell(std::vector<position> const & align_cell,std::vector<position *> &pos_cells);
    size getsize(position const & p) const{return _grid.getSize(p);}
    bool after(position const & p) const{return _grid.after(p);}
    bool before(position const & p) const{return _grid.before(p);}
    position firstMalus(position const & p) const {return _grid.first(p);}
    bool under_bounds(position const & p) const { return _grid.under_bounds(p); }
    virtual bool is_ai() const {return false;}
private:
    grid _grid;
    target _target;
    float _grid_dy;
    score _score ;
    
};

class ai : public game{
public:
    ai(cordinate _max_height=12,cordinate _max_width=6,int colors=4);
    std::vector<t_action> chemin(position const & p1,position const & p2);
    t_num color_distances(position const & p1,position const & p2) const;
    t_num sum_color_distance() const;
    int estimation()  ;
    std::vector<coup> lawful_blow() const; //retourne tout les coups licites sauf si deux cases vides aucun interet
    int minMax(int profondeur);
    coup best_blow(int profondeur) ;
    std::vector<t_action> play_what();
    bool is_ai() const override{return false;}
private:

};

// remote_game
sf::Packet &operator <<(sf::Packet& packet, const t_action& action);
sf::Packet& operator >>(sf::Packet& packet, t_action& action);

enum class t_remote_game
{
    server,
    client
};

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
