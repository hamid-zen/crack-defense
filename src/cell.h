#pragma once
#include <string>
#include <vector>
#include <memory>
#include <cstdint>
#include "position.h"



const uint16_t  nombre_couleurs=4;
using cordinate =uint16_t ;


enum class t_colors {
    blue, pink, yellow, orange, sky_blue, white, purple, green, all, empty_cell, garbage
};
std::string toString_color(t_colors color);

class cell {

public:
    cell(t_colors color) ;
    t_colors color() const;

    void setColor(t_colors newColor);
    delta dx() const;
    delta dy() const ;

    void setDx(delta newDx);
    void setDy(delta newDy);
    virtual bool estmalus() const {return (_color == t_colors::garbage);} //TODO: Bonne pratique de la mettre en virtuel ?

private:
    t_colors _color;
    delta _dx;
    delta _dy;
};

class malusCell : public cell {
public:
    malusCell(t_colors color,bool const &  bfr,bool const & aftr) ;
    bool next_left() const {return _before;}
    bool next_right() const {return _after;}
    bool estmalus() const override {return (color() == t_colors::garbage);}

private:
    bool _before;
    bool _after;
};
