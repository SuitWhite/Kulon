#ifndef __CCLASS_H__
#define __CCLASS_H__
#include <math.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using namespace sf;

class SomeParticle
{
private:
    double charge=1.6; // заряд
    double coorx,coory;  // Координаты
    double weight=9.1; // масса
public:
    double dx, dy; // ускорение
    CircleShape circle;
    SomeParticle()
    {
        circle.setRadius(10);
    }
    SomeParticle(int coorx1, int coory1, double charge1){
    SomeParticle::circle.setPosition(coorx1,coory1);
    SomeParticle::circle.setFillColor(sf::Color::Black);
    circle.setRadius(10);
    SomeParticle::coorx=coorx1;
    SomeParticle::coory=coory1;
    SomeParticle::charge=charge1;
    }
    void update(double time)
    {
        coorx+=dx * time; // нормальное значение для ускорения: 0.0005
        coory+=dy * time;
        if (coorx<=0) coorx-=dx*time;
        if (coorx >=1350) coorx-=dx*time;
        if (coory<=0) coory-=dy*time;
        if (coory>=685) coory-=dy*time;
        
        circle.setPosition(coorx,coory);
    }
    int GetCoorX(){
        return coorx;
    }

    int GetCoorY(){
        return coory;
    }
    double GetCharge(){
    return charge;
    };
    double GetWeight(){
        return weight;
    };
    double DistanceToAnother(SomeParticle &partcl)
    {
        return 0.1*sqrt((partcl.GetCoorX()-coorx)*(partcl.GetCoorX()-coorx)+(partcl.GetCoorY()-coory)*(partcl.GetCoorY()-coory));
    };
    double AngleToAnother(SomeParticle &partcl)
    {
        double ax=partcl.GetCoorX()-coorx;
        double ay=partcl.GetCoorY()-coory;
        double bx=partcl.GetCoorX()-coorx;
        double by=0;
        return acos((ax*bx+ay*by)/(sqrt(ax*ax+ay*ay)*sqrt(bx*bx+by*by)));
    }
};
#endif // __CCLASS_H__