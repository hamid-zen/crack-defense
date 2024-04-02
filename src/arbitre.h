#include "game.h"
#include "timer.h"
#include <SFML/Graphics.hpp>

enum class t_action{
    go_right,go_left,go_up,go_down,change_direction,accelerate,exchange,nothing
};

//TODO: Pourrait prendre le srand
class arbitre
{
public:
    arbitre();
    void update(t_action x);
    float getVerticalSpeed() const{return _vertical_speed;}
    void incVerticalSpeed(float x=0.000001){_vertical_speed+=x;}
    game& getJoueur() const;
    void init ();
private:
    std::unique_ptr<game> _joueur1;
    float _vertical_speed;
    t_number _nb_frame;
};
