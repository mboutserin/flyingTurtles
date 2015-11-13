//Pour compiler à partir du terminal:
//$ g++ -I `root-config --incdir` -o MyExec mainCLIC.cpp `root-config --libs` -std=c++11
//$ ./MyExec

#include <time.h>
#include <math.h>
#include <thread>
#include <chrono>
#include <fstream>
#include <stdlib.h>
#include <TBox.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <TLine.h>
#include <TPoints.h>
#include <TEllipse.h>
#include <TArrow.h>
#include <TMarker.h>
#include <TSystem.h>
#include "simulationphy.h"
#include "objet.h"
#include "interface.h"

using namespace std;



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
*/
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
*/
                this_thread::sleep_for(chrono::milliseconds{dt/4});             // attend dt/4 millisecondes
                Update();                                                       //  Mise à jour de la fenêtre c (dessin de la balle)
            }

             Update();                                                          //  Mise à jour de la fenêtre c


        if(compte == Nshots-1)      cout << "Attention, c'est votre dernier tire. A vous !" << endl;
        if(compte < Nshots-1)       cout << "A vous !" << endl;
        compte++;

        }   //  end if (event==1)

    }       //  ExecuteEvent

};


int main(int argc, char **argv)
{

    //  Initialisation de root
    TApplication theApp("App", &argc, argv);

    Interface menu = Interface();
    menu.menu();

    cout << "CLIQUEZ avec la souris dans la fenêtre afin de faire voler les tortues." << endl;

    SimulationPhy simuLancerBalle = SimulationPhy();

    //  Création de la fenêtre nommé c
    Fenetre c("c","fenetre",400,400, simuLancerBalle);
    //  Coordonnées de la fenetre
    c.Range(0,0,300,300);

    //  Données concernant le choix du sol choisis aléatoirement
    //  typeSol = 0 --> herbe
    //  typeSol = 1 --> boue
    //  typeSol = 2 --> béton
    //  La boue et le béton se dessine après l'ennemi car l'ennemi ne peut écraser le béton (simple soucis de logique)
    srand(time(NULL)); // initialise le hasard (1 seule fois)
    int S = 2;
    typeSol = rand()%(S+1);

    if(typeSol == 0)
    {
        coeffRebond = 0.6;
        for(x = 0 ; x < 300 ; x += 5)
        {
        TLine *herbe=new TLine(x,0,x+1,5); // x1,y1,x2,y2
        herbe->SetLineColor(kGreen+1);
        herbe->SetLineWidth(2);
        herbe->Draw();
        }
    }
    if(typeSol == 1)
    {
        coeffRebond = 0.4;
        for(x = 0 ; x < 300 ; x += 6)
        {
            TEllipse *boue= new TEllipse(x,0,3);    	// Centre (x,y) et rayon r
            boue->SetFillColor(kRed+2);
            boue->Draw();
        }
    }

    //  Données concernant l'ennemi généré aléatoirement dans une zone défini
    //  150 < x < 300   et   0 < y < 100
    //  De taille 10 < tailleX < 50  et  10 < tailleY < 30
    int A = 150;
    positionEnnemiX = 150 + rand()%(A+1); 		// entier aléatoire entre 150 et 150 + A compris.
    int B = 100;
    positionEnnemiY = rand()%(B+1); 			// entier aléatoire entre 0 et B compris.
    int C = 40;
    tailleEnnemiX = 10 + rand()%(C+1);			// entier aléatoire entre 10 et 10 + C compris.
    int D = 20;
    tailleEnnemiY = 10 + rand()%(D+1); 			// entier aléatoire entre 10 et 10 + D compris.

    //  Dessin de l'ennemi
    TBox *Ennemi=new TBox(positionEnnemiX-tailleEnnemiX,positionEnnemiY-tailleEnnemiY,positionEnnemiX,positionEnnemiY);
    Ennemi->SetFillColor(kRed);
    Ennemi->Draw();

    if(typeSol == 2)
    {
        coeffRebond = 0.95;
        TBox *beton=new TBox(0,0,300,2);            	// On précise les coins bas-gauche (x1,y1) et haut droit (x2,y2)
        beton->SetFillColor(kGray+2);
        beton->Draw();
    }


        //  Données concernant le vent            	// entier aléatoire entre -25 et +25 compris.
    TArrow vecteurVent = TArrow(245,290,245 + 2*simuLancerBalle.getVent(),290);
    vecteurVent.SetLineColor(kBlack);
    vecteurVent.Draw();

    c.Update();                                     	// Dessin de l'herbe, ennemi, béton, boue, vent

    theApp.Run();

    return 0;
}
