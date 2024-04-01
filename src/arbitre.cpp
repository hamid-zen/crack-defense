#include "arbitre.h"

arbitre::arbitre()
    : _joueur1(std::make_unique<game>())
    , _timer(default_tick_duration)
{}

void arbitre::play()
{
    //recuperer les paramettre
    _joueur1->init();

    while (_timer.get_tick() < 6000) // Running for a minute
    {
        if (_timer.updated()) // If the tick value has changed
        {
            std::cout << _timer.get_tick() << std::endl; // Printing the current tick
        }
    }
}
