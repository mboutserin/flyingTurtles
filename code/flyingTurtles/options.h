#ifndef OPTIONS_H
#define OPTIONS_H
#include "objet.h"

class Options
{
    public:
        Options();
        void setNombreTirs(int nb);
        int getNombreTirs();
        Objet getEnnemi();

    private:
        int nombreTirs;
        Objet ennemi;


};

#endif // OPTIONS_H
