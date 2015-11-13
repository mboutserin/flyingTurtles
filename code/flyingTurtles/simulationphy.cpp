#include "simulationphy.h"

SimulationPhy::SimulationPhy()
{
    gravitation=9.81; // m.s-2
    srand(time(NULL)); // initialise le hasard (1 seule fois)
    vent = rand()%(30+1) - 15; //m/s
    coefRebond = 0.95; // niet
}

SimulationPhy::SimulationPhy(double rebond)
{
    SimulationPhy();
    coefRebond = rebond;
}

SimulationPhy::~SimulationPhy()
{}

double SimulationPhy::getVent()
{
    return vent;
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

/**
 *  Méthode d'Euler

 *  Pour le moment, on ne fait pas vraiment de bilan des forces
 *  on constate juste la force de réaction en y=0, le poid et le vent.
 *  Le vent est en outre considéré comme une force constante
 *  (un champ de potentiel constant donc)
 */
void SimulationPhy::bouger(Objet &objet, double delta_t)
{
    //1) évolution de la vitesse : dv/dt = a => v1 = V0+a*delta_t
    // bilan des forces : on a le vent et la gravité
    vec2 acceleration = newton2(objet);
    vec2 vitesse1;
    vitesse1(0) = objet.getVx() + acceleration(0)*delta_t/1000;
    vitesse1(1) = objet.getVy() + acceleration(1)*delta_t/1000;
    //2) si on est au sol, il faut appliquer le coef de rebond
    //  sur la vitesse résultante
    // la modélisation du rebond est basique :
    // ici, on inverse la vitesse et on multiplie par le coef de rebond
    if(objet.getY() <= 0){
        vitesse1(1) = -1*vitesse1(1)*coefRebond;
    }
    // mise à jour de la vitesse de l'objet
    objet.setVx(vitesse1(0));
    objet.setVy(vitesse1(1));
    //3) évolution de la position : p1 = p0 + v*delta_t
    objet.bouger(delta_t/1000);

}

/**
  *  On ne fait pas ici la véritable somme des forces,
  *  on se contente du poid et du vent.
  *  Donc on a :
  *  -gravitation = ay
  *  vent = ax
 */
vec2 SimulationPhy::newton2(Objet &objet)
{
    vec2 acceleration;

    acceleration(0) = vent;
    //acceleration(1) = 0;
    acceleration(1) = -gravitation;

    return acceleration;
}


