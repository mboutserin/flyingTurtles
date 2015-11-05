#include "../include/simulationphy.h"
#include <math.h>

SimulationPhy::SimulationPhy()
{
    //ctor
}

SimulationPhy::~SimulationPhy()
{
    //dtor
}

double* SimulationPhy::sansFrottement(double v0, double thetarad, double t, double x0)
{
    double x,y;
    x = x0+v0*cos(thetarad)*t/1000;
    y = 10-Gravitation*t*t/(2*1000*1000)+v0*sin(thetarad)*t/1000;
    double *u = new double[2];
    u[0] = x;
    u[1] = y;
    return u;
}

Objet::Objet(double x0,double y0)
{
    x=x0;
    y=y0;
}
