#include "game.h"
#include "timer.h"
#include <SFML/Graphics.hpp>
#include<utility>

using frame = int16_t ;


struct delay {
    position * cells_switch1 ;
    position * cells_switch2 ;
    delta cell1Dx ;
    delta cell2Dx;
    delta cellDxbase;
    bool newline = false;
    float oldspeed ;
    frame last_frame_alignment;
    frame last_garbage;
    t_number angle;
    float scale;
    std::vector<position *> cells_slide ;
    std::vector<position > cells_align ;
};

enum class t_action{
    go_right, go_left, go_up, go_down, change_direction, accelerate, exchange, nothing, generate_malus
};

//TODO: Pourrait prendre le srand
class arbitre
{
public:
    arbitre(t_number ind,bool jeu_duo=false);
    void update(t_action x, bool first_player=true);
    void updateFirstPlayer(t_action x);
    void updateSecondPlayer(t_action x);
    float getVerticalSpeed() const{return _vertical_speed;}
    void incVerticalSpeed(float x=0.000001){_vertical_speed+=x;}
    game& getJoueur() const;
    void init ();
    delay & getDelays(bool first_player=true);
    t_number getFrame() const {return _nb_frame;}
    void setVerticalSpeed_Med(){_vertical_speed = 1.5;};  
    void setVerticalSpeed_Hard(){_vertical_speed = 2;};
    bool jeu_duo() const ;
private:
    std::unique_ptr<game> _joueur1;
    std::unique_ptr<game> _joueur2;

    float _vertical_speed;
    t_number _nb_frame;
    delay delays ;
    delay delays2 ;
};

