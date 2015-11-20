#include "objet.h"

Objet::Objet(double x0,double y0,double v0x, double v0y)
{
    position = vec(2);
    position(0)=x0;
    position(1)=y0;
    masse=50;
    vitesse = vec(2);
    vitesse(0)=v0x;
    vitesse(1)=v0y;
    energie=0;
}

double Objet::getHauteur()
{
    return hauteur;
}

void Objet::setHauteur(double h)
{
    hauteur = h;
}

double Objet::getLongueur()
{
    return longueur;
}

void Objet::setLongueur(double l)
{
    longueur = l;
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
//cout << "objet dt=" << delta_t << endl;
//cout << "vitesse objet =" << vitesse(0) << "," << vitesse(1) << endl;
    position(0)+=delta_t*vitesse(0);
    position(1)+=delta_t*vitesse(1);
}

double Objet::getVitesse()
{
    return sqrt(vitesse(0)*vitesse(0) + vitesse(1)*vitesse(1));
}

void Objet::setVitesse(double vx, double vy)
{
    vitesse(0) = vx;
    vitesse(1) = vy;
}
