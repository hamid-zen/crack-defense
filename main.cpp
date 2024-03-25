#include <iostream>
#include "grid.h"
using namespace std;

int main()
{
    srand(time(0));
    grid g;
    g.init();
    g.afficher();
    return 0;
}
