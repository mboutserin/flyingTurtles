#ifndef SIMULATIONPHY_H
#define SIMULATIONPHY_H


class SimulationPhy
{
    public:
        SimulationPhy();
        ~SimulationPhy();

        double *sansFrottement(double v0, double thetarad, double t, double x0);

    private:
        const double Gravitation = 9.81;
};

class Objet
{
    public:
        Objet(double x0=0,double y0=0);

    private:
        double x;
        double y;
        double masse;
        double v;
};

#endif // SIMULATIONPHY_H
