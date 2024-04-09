#include "arbitre.h"
#include<iostream>
using dimension = u_int16_t;


class interface{
public:
    interface();
    void play(t_number ind=0);
    void menu(t_number ind=0);
private:
    dimension _width;
    t_number_color _difficulty ;
    sf::Font _font;

};