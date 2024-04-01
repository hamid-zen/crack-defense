#include "game.h"
#include "timer.h"

const t_number default_tick_duration = 33;

class arbitre
{
public:
    arbitre();
    void play();

private:
    std::unique_ptr<game> _joueur1;
    timer _timer;
};
