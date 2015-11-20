//Pour compiler à partir du terminal:
//$ g++ -I `root-config --incdir` -o MyExec mainCLIC.cpp `root-config --libs` -std=c++11
//$ ./MyExec

#include "TApplication.h"
#include "fenetre.h"
#include "jeu.h"
#include <iostream>

using namespace std;


int main(int argc, char **argv)
{

//cout << "main lancé" << endl;
    //  Initialisation de root
    TApplication theApp("App", &argc, argv);

//cout << "theApp construit ; construction de jeu" << endl;
    Jeu jeu = Jeu();
//cout << "jeu construit ; initialisation de jeu" << endl;

    jeu.init();
//cout << "jeu initialisé" << endl;

    // d'abord, il nous faut la fenêtre
    Fenetre c("c","fenetre",400,400, jeu);
    //  Coordonnées de la fenetre
    c.Range(0,0,300,300);
//cout << "fenetre construite ; lancement de la partie" << endl;
    // lance la partie
    jeu.partie();


//cout << "partie lancée" << endl;

    // donne la main à l'utilisateur
    theApp.Run();

    return 0;
}
