//Pour compiler à partir du terminal:
//$ g++ -I `root-config --incdir` -o MyExec mainCLIC.cpp `root-config --libs` -std=c++11
//$ ./MyExec

#include <iostream>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <TBox.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <TLine.h>
#include <TPoints.h>
#include <TEllipse.h>
#include <TArrow.h>
#include <thread>
#include <chrono>
#include <fstream>
#include <TMarker.h>
#include <TSystem.h>

using namespace std;
const double g = 9.81;          //  constante gravitationnelle
int Nshots=10;
double x0;
double coeffRebond;
int count=1;
//  Déclaration des variables Ennemi
int positionEnnemiX,positionEnnemiY;
int tailleEnnemiX,tailleEnnemiY;
//  Déclaration des variables Sol
int typeSol,x;




double *sansFrottement(double v0, double thetarad, double t, double x0)
{
    //cout << "fonction sans frottement" << endl;
    double x,y;
    x = v0*cos(thetarad)*t/1000+x0;
    y = -g*t*t/(2*1000*1000)+v0*sin(thetarad)*t/1000;
    double *u = new double[2];
    u[0] = x;
    u[1] = y;
    //cout << "coordonnées x:" << u[0] << " et y:" << u[1] << endl;
    return u;
}


//====Ma Classe Fenetre================================
class Fenetre: public TCanvas
{
    public:
    // constructeur ......
    Fenetre(TString name, TString title, Int_t ww, Int_t wh) : TCanvas(name,title,ww,wh)
    { }
    //—- Cette fonction est appelle si la souris s'agitte. ——
    void ExecuteEvent(Int_t event, Int_t px, Int_t py)
    {
    //  Déclaration içi seulement des variables de départ pour lancer la boule :
    //  - v0 : vitesse initial
    //  - thetarad = theta0 en rad
    //  - tau : coefficient de frottement (rapport m/k)
    //  - x0 = déplacement du repère pour le rebond de la balle
    double v0,thetarad;


    //  Déclaration des variables temporelles
    double t;
    int dt;
    t = 0;
    dt = 10;       //  dt en ms


    //  dessin de la balle à t=0
    TEllipse balle(0,0,5);
    balle.SetFillColor(kBlack);
    balle.Draw();



        //– affiche l'etat de la souris ——–

        //– convertit la position en pixel px,py en coordonnees (x,y) ——
        Double_t x = gPad->AbsPixeltoX(px);
        Double_t y = gPad->AbsPixeltoY(py);
        // si bouton gauche appuye dessine un point —

        if(event==1 && count<Nshots+1)
        {


            TMarker *m=new TMarker(x,y,3);
            m->Draw();

            thetarad = atan((y)/(x));
            v0=sqrt(x*x+y*y);

            //  dessin du vecteur v0
            TArrow *vecteurV0=new TArrow(0,0,x,y);
            vecteurV0->SetLineColor(kBlack);
            vecteurV0->SetLineWidth(2);
            vecteurV0->Draw();
            Update();         // mise à jour de la fenêtre c


            //  Déclaration de la position
            double x1,y1;
            double *coord = sansFrottement(v0,thetarad,t,x0);
            y1 = coord[1];
            x0 = 0;

            while(x1 < 300)
            {
                if(y1 < 0)
                {
                    t = 0;
                    x0 = x1;
                    v0 *= coeffRebond;

                }

                /*if((positionEnnemiX-tailleEnnemiX<x1<tailleEnnemiX)||(positionEnnemiY-tailleEnnemiY<y1<tailleEnnemiY))
                {
                    cout << "Beau gosse" << endl;
                    break;
                }*/


                coord = sansFrottement(v0,thetarad,t,x0);
                t += dt;
                x1 = coord[0];
                y1 = coord[1];
                balle.SetX1(coord[0]);
                balle.SetY1(coord[1]);
                balle.Draw();

                this_thread::sleep_for(chrono::milliseconds{dt/4});   // attend dt millisecondes
                Update();
            }

             Update();


        if(count == Nshots-1)      cout<<"Attention, c'est votre dernier tire. A vous!"<<endl;
        if(count < Nshots-1)       cout<<"A vous!"<<endl;
        count++;
        }//end if (event==1)

    }//ExecuteEvent

};


int main(int argc, char **argv)
{

    //  initialisation de root
    TApplication theApp("App", &argc, argv);
    cout << endl;

    cout << "********************************************************************************" << endl;
    cout << "****************** Bienvenue dans le menu de flyingTurtles !! ******************" << endl;
    cout << "********************************************************************************" << endl;

    cout << endl << "Combien de tortues voulez-vous jeter ?" <<endl;
    cin >> Nshots;

    cout << "CLIQUEZ avec la souris dans la fenêtre afin de faire voler les tortues." << endl;


    //  création de la fenêtre
    Fenetre c("c","fenetre",400,400);
    //  coordonnées de la fenetre
    c.Range(0,0,300,300);

    //  Données concernant le choix du sol choisis aléatoirement
    //  typeSol = 0 --> herbe
    //  typeSol = 1 --> béton
    //  typeSol = 2 --> boue
    //  La boue et le béton se dessine après l'ennemi car l'ennemi ne peut écraser le béton ou la boue (simple soucis de logique)
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

    //  Données concernant l'ennemi généré aléatoirement dans une zone défini
    //  150 < x < 300   et   0 < y < 100
    //  De taille 10 < tailleX < 50  et  10 < tailleY < 30

    int A = 150;
    positionEnnemiX = 150 + rand()%(A+1); // entier aléatoire entre 150 et 150 + A compris.

    int B = 100;
    positionEnnemiY = rand()%(B+1); // entier aléatoire entre 0 et B compris.

    int C = 40;
    tailleEnnemiX = 10 + rand()%(C+1); // entier aléatoire entre 10 et 10 + C compris.

    int D = 20;
    tailleEnnemiY = 10 + rand()%(D+1); // entier aléatoire entre 10 et 10 + D compris.

    //  Dessin de l'ennemi
    TBox *Ennemi=new TBox(positionEnnemiX-tailleEnnemiX,positionEnnemiY-tailleEnnemiY,positionEnnemiX,positionEnnemiY);
    Ennemi->SetFillColor(kRed);
    Ennemi->Draw();


    if(typeSol == 1)
    {
        coeffRebond = 0.4;
        for(x = 0 ; x < 300 ; x += 6)
        {
            TEllipse *boue= new TEllipse(x,0,3); // (centre (x,y) et rayon r
            boue->SetFillColor(kRed+2);
            boue->Draw();
        }
    }
    if(typeSol == 2)
    {
        coeffRebond = 0.95;
        // on precise les coins bas-gauche (x1,y1) et haut droit (x2,y2) :
        TBox *beton=new TBox(0,0,300,2);
        beton->SetFillColor(kGray+2);
        beton->Draw();
    }


    c.Update();

    theApp.Run();

    return 0;
}
