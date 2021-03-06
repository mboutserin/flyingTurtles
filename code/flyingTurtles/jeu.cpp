#include "jeu.h"
#include <iostream>

Jeu::Jeu()
{
    // options par défaut
    options = Options();
    dt = 50;
    simu = SimulationPhy();
    compteTirs = 0;
}

/**
 * Initialisation du jeu.
 **/
void Jeu::init()
{
    // d'abord, il faut récupérer les options
    // et pour le moment c'est ce qu'on fait avec le menu de l'interface
    interface.menu(options);
//cout <<"on peut tirer "<<options.getNombreTirs()<<" fois"<<endl;
    // ensuite, on initialise les éléments du jeu
    //initTortue();
    initEnnemi();
    initSol();

    // on remet le compte de tir à zéro.
    compteTirs = 0;
    // après tout ça, on est prêt
}



/**
 * Fonction principale : lance une partie du jeu où l'on lance des tortues
 *  pour détruire un ennemi.
 **/
void Jeu::partie()
{

    // ensuite, on dessine le monde
    interface.dessinMonde(sol, ennemi, simu.getVent(), tortue);

}

bool Jeu::lancerDeTortue()
{
//cout << "position tortue : x=" << tortue.getX() << " et y=" << tortue.getY() << endl;
//cout << "vitesse tortue : x=" << tortue.getVx() << " et y=" << tortue.getVy() << endl;


    if(tortue.getVitesse() > 3 && tortue.getVx() > 0 && tortue.getX() < 300)
    {
//    cout << "la tortue avance" << endl;
        avancer();


        this_thread::sleep_for(chrono::milliseconds{10});
        // attend dt/4 millisecondes
        return true;
    }
    compteTirs++;
    interface.avertirTirs(options.getNombreTirs() - compteTirs);
//cout << "la tortue s'arrête" << endl;
    return false;
}


/**
 * Cette fonction initialise le sol. Idéalement, elle pourra le faire
 *  à partir des options.
 */
//  Données concernant le choix du sol choisis aléatoirement
//  typeSol = 0 --> herbe
//  typeSol = 1 --> boue
//  typeSol = 2 --> béton
//  La boue et le béton se dessine après l'ennemi car l'ennemi ne peut écraser
//   le béton (simple soucis de logique)
void Jeu::initSol()
{
    srand(time(NULL)); // initialise le hasard (1 seule fois)
    int S = 2;
    int typeSol = rand()%(S+1);
    if(typeSol == 0)
    {
        simu.setRebond(0.6);
    }else if(typeSol == 1)
    {
        simu.setRebond(0.4);
    }else if(typeSol == 2)
    {
        simu.setRebond(0.95);
    }
    sol = typeSol;
}

/**
 * Cette fonction initialise l'ennemi. Idéalement, elle pourra le faire
 *  à partir des options.
 */
void Jeu::initEnnemi()
{
    ennemi = Objet();
    //  Données concernant l'ennemi généré aléatoirement dans une zone défini
    //  150 < x < 300   et   0 < y < 100
    //  De taille 10 < tailleX < 50  et  10 < tailleY < 30
    int A = 150;                            // entier aléatoire entre 150 et 150 + A compris.
    setXennemi = 150 + rand()%(A+1);
    ennemi.setX(setXennemi);

    int B = 100;                            // entier aléatoire entre 0 et B compris.
    setYennemi = rand()%(B+1);
    ennemi.setY(setYennemi);

    int C = 40;                             // entier aléatoire entre 10 et 10 + C compris.
    setLongueur = 10 + rand()%(C+1);
    ennemi.setLongueur(setLongueur);

    int D = 20;                             // entier aléatoire entre 10 et 10 + D compris.
    setHauteur = 10 + rand()%(D+1);
    ennemi.setHauteur(setHauteur);

    positionCentraleEnnemiX = (setXennemi + setLongueur)/2;
    positionCentraleEnnemiY = (setYennemi + setHauteur)/2;
}

/**
 * Initialisation de la tortue. Idéalement, les paramètres viendronts
 *  des options.
 **/
void Jeu::initTortue(double vx, double vy)
{
    tortue = Objet(0,10, vx, vy);
    //  Vitesse limite v0 sinon jeu trop facile

//cout << "vitesse tortue avant limite : " << tortue.getVitesse() << endl;
    if(tortue.getVitesse() > 75)
    {
//    cout << "modification de la vitesse de la tortue" << endl;
        double v = 75;
        //  Permet d'avoir le vecteur v0 correct
        double thetarad = atan((tortue.getVy())/(tortue.getVx()));
        tortue.setVx(v*cos(thetarad));
        tortue.setVy(v*sin(thetarad));
    }
//cout << "vitesse tortue après limite : " << tortue.getVitesse() << endl;
    interface.dessinV0(tortue.getVx(),tortue.getVy());

    //tortue.enregistrer("tortue.txt");
}

Options Jeu::getOptions()
{
    return options;
}

Objet Jeu::getTortue()
{
    return tortue;
}

void Jeu::avancer()
{
//    cout << "on avance de dt dans la simulation" << endl;
    simu.bouger(tortue, dt);
//    cout << "on redessine la tortue" << endl;
    interface.dessinTortue(tortue);
}

bool Jeu::autorisationTir()
{
//cout << "compteTir="<<compteTirs<<", tir restants="<<options.getNombreTirs()<<endl;
    if(compteTirs < options.getNombreTirs())
    {
 //       cout << "on peut tirer" << endl;
        return true;
    }
    else
    {
 //       cout << "on ne tire plus" << endl;
        return false;
    }
}

bool Jeu::isVictoire()
{
    if((tortue.getX() > (ennemi.getX()-ennemi.getLongueur()) && tortue.getX() < ennemi.getX())
        && (tortue.getY() < ennemi.getY() && tortue.getY() > (ennemi.getY()-ennemi.getHauteur())))
    {
        interface.victoire();
        return true;
    }else{
        return false;
    }
}
