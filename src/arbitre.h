#include "game.h"
#include "timer.h"
#include <SFML/Graphics.hpp>

//TODO: Pourrait prendre le srand
class arbitre
{
public:
    arbitre();
    void play();

private:
    std::unique_ptr<game> _joueur1;
    float _vertical_speed;
};
