#ifndef SIMULATIONPHY_H
#define SIMULATIONPHY_H

#include <math.h>
#include <armadillo>
using namespace arma;

#include "objet.h"


class SimulationPhy
{
    public:
        SimulationPhy();
        SimulationPhy(double rebond);
        ~SimulationPhy();

//        static double *sansFrottement(double v0, double thetarad, double t, double x0);
        //double getGravitation();
        double getVent();
        void setRebond(double r);

        void bouger(Objet &objet, double delta_t);
//        bool collision(Objet &objet1,Objet &objet1);

    private:
        double gravitation;
        double vent;
        double coefRebond;

        vec2 newton2(Objet &objet);
};

#endif // SIMULATIONPHY_H
