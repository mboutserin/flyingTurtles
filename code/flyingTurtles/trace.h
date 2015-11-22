#ifndef TRACE_H
#define TRACE_H

#include <iostream>
using namespace std;
#include <fstream> // utilisation des fichiers

class Trace
{
    public:
        Trace();
        void ecrire(string texte);
        void activer();
        void couper();
        void setFichier(string nom);

    private:
        string fichier;
        bool active;

};

#endif // OBJET_H
