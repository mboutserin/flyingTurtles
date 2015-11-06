#ifndef SIMULATIONPHY_H
#define SIMULATIONPHY_H

#include <math.h>
#include <armadillo>
using namespace arma;

#include "objet.h"

static double Gravitation = 9.81;


class SimulationPhy
{
    public:
        SimulationPhy();
        ~SimulationPhy();

        static double *sansFrottement(double v0, double thetarad, double t, double x0);
        //double getGravitation();
        double getVent();

        void bouger(Objet &objet, double delta_t);

    private:
        double gravitation;
        double vent;
        double coefRebond;

        vec2 newton2(Objet &objet);
};

#endif // SIMULATIONPHY_H
