#include "game.h"

class arbiter{
public:
arbiter();
void play();
private:
std::unique_ptr<game> _joueur1;
};