#include "options.h"

//public:
Options::Options()
{
    nombreTirs = 1;
    // ennemi par défaut (normalement inutile) : x=150, y=0, h=10, l=10
    ennemi = Objet(150, 0);
    ennemi.setLongueur(10);
    ennemi.setHauteur(10);
}

void Options::setNombreTirs(int nb)
{
    nombreTirs = nb;
}

int Options::getNombreTirs()
{
    return nombreTirs;
}

Objet Options::getEnnemi()
{
    return ennemi;
}

//private:
