#pragma once
#include <string>
#include <vector>
#include <memory>
#include <cstdint>
#include "position.h"



const uint16_t  nombre_couleurs=4;
using cordinate =uint16_t ;


enum class t_colors {
    blue, pink, yellow, orange,all, empty_cell
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
    virtual bool estmalus()const{return false;}
    virtual cordinate getsize() const{return 0;}
private:
    t_colors _color;
    delta _dx;
    delta _dy;
};

class malusCell : public cell {
public:
    malusCell(t_colors color,std::vector<std::shared_ptr<cell>>  vec) ;
    void addMalus(std::shared_ptr<cell> newMalus);
    const std::vector<std::shared_ptr<cell>>& getMalus() const;
    bool estmalus() const override{return true;}
    cordinate getsize() const override {return _malus.size();}

private:
    std::vector<std::shared_ptr<cell>> _malus; // Vecteur de pointeurs vers les malus associés à cette cellule}; pour qu'on puissen tles modifier a parit d'une seul acse
};