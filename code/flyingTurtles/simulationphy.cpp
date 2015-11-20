#include "simulationphy.h"

SimulationPhy::SimulationPhy()
{
    gravitation=-9.81; // m.s-2
    srand(time(NULL)); // initialise le hasard (1 seule fois)
    vent = rand()%(10+1) - 10; //de [-10,10] m/s-2
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

void SimulationPhy::setRebond(double r)
{
    coefRebond = r;
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
    //cout << "accélération simu : x=" << acceleration(0) << " et y=" << acceleration(1) << endl;
    vec2 vitesse1;
    vitesse1(0) = objet.getVx() + acceleration(0)*delta_t/1000.00;
    vitesse1(1) = objet.getVy() + acceleration(1)*delta_t/1000.00;
    //2) si on est au sol, il faut appliquer le coef de rebond
    //  sur la vitesse résultante
    // la modélisation du rebond est basique :
    // ici, on inverse la vitesse et on multiplie par le coef de rebond
    if(objet.getY() <= 0){
        vitesse1(1) *= -1.0*coefRebond;
    //cout << "coef rebond =" << coefRebond << endl;
    }
//    cout << "vitesse simu : x=" << vitesse1(0) << " et y=" << vitesse1(1) << endl;
    // mise à jour de la vitesse de l'objet
    objet.setVx(vitesse1(0));
    objet.setVy(vitesse1(1));

    //3) évolution de la position : p1 = p0 + v*delta_t
    objet.bouger((double)(delta_t/1000.00));

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
    vec2 acceleration = {vent, gravitation};
    return acceleration;
}


