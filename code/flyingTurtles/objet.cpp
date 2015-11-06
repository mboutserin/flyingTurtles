#include "objet.h"

Objet::Objet(double x0,double y0,double v0x, double v0y)
{
    position(0)=x0;
    position(1)=y0;
    masse=50;
    vitesse(0)=v0x;
    vitesse(1)=v0y;
    energie=0;
}

double Objet::getX()
{
    return position(0);
}
double Objet::getY()
{
    return position(1);
}
void Objet::setX(double x0)
{
    position(0) = x0;
}
void Objet::setY(double y0)
{
    position(1) = y0;
}
double Objet::getVx()
{
    return vitesse(0);
}
void Objet::setVx(double v0)
{
    vitesse(0) = v0;
}
double Objet::getVy()
{
    return vitesse(1);
}
void Objet::setVy(double v0)
{
    vitesse(1) = v0;
}

void Objet::bouger(double delta_t)
{
    position(0)+=delta_t*vitesse(0);
    position(1)+=delta_t*vitesse(1);
}

double Objet::getVitesse()
{
    return vitesse(0)*vitesse(0) + vitesse(1)*vitesse(1);
}
