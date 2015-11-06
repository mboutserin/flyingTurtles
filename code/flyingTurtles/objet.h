#ifndef OBJET_H
#define OBJET_H

#include <armadillo>
using namespace arma;

class Objet
{
    public:
        Objet(double x0=0,double y0=0,double v0x=0, double v0y=0);

        double getX();
        double getY();
        void setX(double x0);
        void setY(double y0);
        double getVx();
        void setVx(double v0);
        double getVy();
        void setVy(double v0);
        double getVitesse();

        void bouger(double delta_t);


    private:
        vec2 position;
        double masse;
        vec2 vitesse;
        double energie;
};

#endif // OBJET_H
