#ifndef OBJET_H
#define OBJET_H

#include <math.h>
#include <armadillo>
using namespace arma;

class Objet
{
    public:
        Objet(double x0=0,double y0=0,double v0x=0, double v0y=0);

        // position
        double getX();
        double getY();
        void setX(double x0);
        void setY(double y0);

        //vitesse
        double getVx();
        void setVx(double v0);
        double getVy();
        void setVy(double v0);
        double getVitesse();
        void setVitesse(double vx, double vy);

        // taille
        double getHauteur();
        void setHauteur(double h);
        double getLongueur();
        void setLongueur(double l);

        // fonctions
        void bouger(double delta_t);


    private:
        vec2 position;
        double masse;
        vec2 vitesse;
        double energie;
        double hauteur;
        double longueur;
};

#endif // OBJET_H
