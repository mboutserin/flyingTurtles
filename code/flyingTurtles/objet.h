#ifndef OBJET_H
#define OBJET_H

#include <math.h>
#include <armadillo>
using namespace arma;
#include "trace.h"
#include <sstream>

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

        void enregistrer(string nom);
        void stopEnregistrer();

    private:
        vec2 position;
        // quand l'objet est un rectangle, x et y définissent le coin inférieur gauche
        double masse;
        vec2 vitesse;
        double energie;
        double hauteur;
        double longueur;
        // quand l'objet est un rectangle, ces valeurs définissent la hauteur et la largeur

        Trace trace;
};

#endif // OBJET_H
