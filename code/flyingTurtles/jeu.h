#ifndef JEU_H
#define JEU_H
#include "objet.h"
#include "interface.h"
#include "options.h"
#include <armadillo>
using namespace arma;


class Jeu
{
    public:
        Jeu();
        void init();
        void partie();
        void avancer();
        bool lancerDeTortue();
        bool autorisationTir();

        Options getOptions();
        Objet getTortue();

        void initTortue(double vx = 0, double vy = 0);

    private:
        // les éléments du jeu
        SimulationPhy simu;
        Interface interface;
        Options options;
        // interval de temps
        double dt;

        int compteTirs;

        // les objets du monde du jeu
        Objet tortue;
        Objet ennemi;
        int sol;

        // initialisation des éléments
        void initEnnemi();
        void initSol();
};

#endif // JEU_H
