#ifndef INTERFACE_H
#define INTERFACE_H
#include <iostream>
#include "options.h"
#include "simulationphy.h"
#include "TApplication.h"
#include "TLine.h"
#include "TEllipse.h"
#include "TBox.h"
#include "TArrow.h"
#include <thread>
#include <chrono>

using namespace std;

class Interface
{
    public:
        Interface();
        void menu(Options& options);
        void dessinEnnemi(Objet ennemi);
        void dessinSol(int typeSol);
        void dessinVent(double vent);
        void dessinTortue(Objet tortue);
        void dessinMonde(int sol, Objet ennemi, double vent, Objet tortue);
        void dessinV0(double x, double y);
        void avertirTirs(int tirRestants);

    protected:

    private:
        // éléments non statiques
        TEllipse modeleTortue;
        TArrow vecteurV0;

};

#endif // INTERFACE_H
