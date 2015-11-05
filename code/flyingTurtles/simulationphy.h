#ifndef SIMULATIONPHY_H
#define SIMULATIONPHY_H


static double Gravitation = 9.81;

class SimulationPhy
{
    public:
        SimulationPhy();
        ~SimulationPhy();

        static double *sansFrottement(double v0, double thetarad, double t, double x0);
        //double getGravitation();

    private:
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
