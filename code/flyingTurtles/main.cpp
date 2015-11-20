//Pour compiler à partir du terminal:
//$ g++ -I `root-config --incdir` -o MyExec mainCLIC.cpp `root-config --libs` -std=c++11
//$ ./MyExec

#include "TApplication.h"
#include "fenetre.h"
#include "jeu.h"
#include <iostream>

using namespace std;


/*
//  Déclaration de toute les constantes et variables utiles dans tout le programme
int Nshots=5;                   //  Nshots corresponds au nombre de tir maximum quand on lance l'executable
double x0;                      //  x0 = déplacement du repère pour le rebond de la balle
double coeffRebond;             //  coeffRebond est le coeff qui varie selon le matériau sur lequel on rebondit
int compte=1;                    //  ?!?!?!?!?!
//  Déclaration des variables Ennemi
int positionEnnemiX,positionEnnemiY;
int tailleEnnemiX,tailleEnnemiY;
//  Déclaration des variables Sol
int typeSol,x;
//  Déclaration des variables vent
int vitesseVent;
//  Dessin du vecteur vent
TArrow vecteurVent;

*/

/*
//============================== Ma Classe Fenetre ==============================
class Fenetre: public TCanvas
{


    public:

    SimulationPhy simuLancerBalle;
    // constructeur ......
    Fenetre(TString name, TString title, Int_t ww, Int_t wh, SimulationPhy &simu) : TCanvas(name,title,ww,wh)
    {
        simuLancerBalle = simu;
    }
    //————————————— Cette fonction est appelle si la souris s'agitte —————————————
    void ExecuteEvent(Int_t event, Int_t px, Int_t py)
    {
        //  Déclaration içi seulement des variables de départ pour lancer la boule :
        //  - v0 : vitesse initial
        //  - thetarad = theta0 en rad
        double v0,thetarad;

        //  Déclaration des variables temporelles ( dt en ms )
        double t;
        int dt;
        t = 0;
        dt = 10;

        //  Dessin de la balle à t=0
        TEllipse balle(0,0,5);
        balle.SetLineColor(kGreen+3);
        balle.Draw();
        Update();


        //———————————————————— Affiche l'état de la souris ————————————————————

        //–––– Convertit la position en pixel (px,py) en coordonnees (x,y) ——––
        Double_t x = gPad->AbsPixeltoX(px);
        Double_t y = gPad->AbsPixeltoY(py);

        //––––––––––––– Si bouton gauche appuyé dessine un point ––––––––––––––
        if(event==1 && compte<Nshots+1)
        {
            thetarad = atan((y)/(x));
            v0=sqrt(x*x+y*y);


            Objet tortue = Objet(0,10);

            if(v0 > 75)                        //  Vitesse limite v0 sinon jeu trop facile
            {
                v0 = 75;
                x = v0*cos(thetarad);          //  Permet d'avoir le vecteur v0 correct
                y = v0*sin(thetarad);
            }

            tortue.setVx(x);
            tortue.setVy(y);

            //  Dessin du vecteur v0
            TArrow *vecteurV0=new TArrow(0,0,x,y);
            vecteurV0->SetLineColor(kBlack);
            vecteurV0->SetLineWidth(2);
            vecteurV0->Draw();
            Update();          //  Mise à jour de la fenêtre c (dessin du vecteur V0)

            /*
            //  Déclaration de la position
            double x1,y1;
            double *coord = SimulationPhy::sansFrottement(v0,thetarad,t,x0);
            y1 = coord[1];
            x0 = 0;
* /
            while(tortue.getVitesse() > 3 && tortue.getVx() > 0 && tortue.getX() < 300)
//            while(x1 < 300)        //  Tant que on est pas sortie de la fenêtre (x > 300) on exécute
            {
                simuLancerBalle.bouger(tortue,dt);

                balle.SetX1(tortue.getX());
                balle.SetY1(tortue.getY());
                balle.Draw();

              //  cout << "x=" << tortue.getX() << " et y=" << tortue.getY() << endl;
 /*               if(y1 < 0)          //  Modélisation du rebond
                {
                    t = 0;
                    x0 = x1;
                    v0 *= coeffRebond;
                }

                /*if((positionEnnemiX-tailleEnnemiX<x1<tailleEnnemiX)&&(positionEnnemiY-tailleEnnemiY<y1<tailleEnnemiY))        //  Si on touche l'ennemi on a gagné
                {
                    cout << "Beau gosse" << endl;
                    break;
                }*/
/*
                coord = SimulationPhy::sansFrottement(v0,thetarad,t,x0);           //  |
                t += dt;                                            //  |
                x1 = coord[0];                                      //  |
                y1 = coord[1];                                      //   >  Mise à jour de la position et dessin de la balle
                balle.SetX1(coord[0]);                              //  |
                balle.SetY1(coord[1]);                              //  |
                balle.Draw();                                       //  |
* /
                this_thread::sleep_for(chrono::milliseconds{dt/4});             // attend dt/4 millisecondes
                Update();                                                       //  Mise à jour de la fenêtre c (dessin de la balle)
            }

             Update();                                                          //  Mise à jour de la fenêtre c


        if(compte == Nshots-1)      cout << "Attention, c'est votre dernier tire. A vous !" << endl;
        if(compte < Nshots-1)       cout << "A vous !" << endl;
        compte++;

        }   //  end if (event==1)

    }       //  ExecuteEvent

};*/


int main(int argc, char **argv)
{

//cout << "main lancé" << endl;
    //  Initialisation de root
    TApplication theApp("App", &argc, argv);

//cout << "theApp construit ; construction de jeu" << endl;
    //Interface menu = Interface();
    //menu.menu();
    Jeu jeu = Jeu();
//cout << "jeu construit ; initialisation de jeu" << endl;

    jeu.init();
    //Options options = Options();
cout << "jeu initialisé" << endl;

    // d'abord, il nous faut la fenêtre
    Fenetre c("c","fenetre",400,400, jeu);
    //  Coordonnées de la fenetre
    c.Range(0,0,300,300);
cout << "fenetre construite ; lancement de la partie" << endl;

    jeu.partie();


cout << "partie lancée" << endl;

/*    //  Création de la fenêtre nommé c
    Fenetre c("c","fenetre",400,400, simuLancerBalle);
    //  Coordonnées de la fenetre
    c.Range(0,0,300,300);



        //  Données concernant le vent            	// entier aléatoire entre -25 et +25 compris.
    TArrow vecteurVent = TArrow(245,290,245 + 2*simuLancerBalle.getVent(),290);
    vecteurVent.SetLineColor(kBlack);
    vecteurVent.Draw();

*/



    theApp.Run();

    return 0;
}
