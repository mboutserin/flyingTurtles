#include "trace.h"

Trace::Trace()
{
    active = false;
}


void Trace::activer()
{
    active = true;
}
void Trace::couper()
{
    active = false;
}

void Trace::setFichier(string nom)
{
    fichier = nom;
}

void Trace::ecrire(string texte)
{
    if(active){
        ofstream f(fichier,ios::app); // ouvre le nouveau fichier en ecriture. On lui associe l'objet: f
        f<<texte<<endl; // permet d'ecrire dans le fichier.
        f.close(); // fermeture du fichier f
    }
}
