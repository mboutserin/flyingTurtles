#include <iostream>
#include <math.h>
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

using namespace std;

const double g = 9.81;

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

double *avecFrottement(double v0, double thetarad, double t, double tau)
{
    double x,y;
    x = tau*v0*cos(thetarad)*(1-exp(-t/(1000*tau)));
    y = -g*t*tau/1000+tau*(v0*sin(thetarad)+g*tau)*(1-exp(-t/(tau*1000)));
    double *u = new double[2];
    u[0] = x;
    u[1] = y;
    return u;
}

int main(int argc, char **argv)
{
    //  Déclaration içi seulement des variables de départ pour lancer la boule :
    //  - v0 : vitesse initial
    //  - theta0 : angle initial en degré entre l'axe x et v0
    //  - thetarad = theta0 en rad
    //  - tau : coefficient de frottement (rapport m/k)
    //  - xv = v0.cos(theta0)
    //  - yv = v0.sin(theta0)
    //  - x0 = déplacement du repère pour le rebond de la balle
    double v0,theta0,thetarad,tau,xt,yt,x0=0;

    // - Coefficient de rebondissement
    double coeffRebond;

    //  Déclaration des variables temporelles
    double t;
    int dt;
    t = 0;
    dt = 100;       //  dt en ms

    //  Déclaration de la position
    double x1,y1;

    //  Déclaration des vitesses v1
    double v1,v1x,v1y,v1ynew;

    //  initialisation de root
    TApplication theApp("App", &argc, argv);
    //  création de la fenêtre
    TCanvas c("c","fenetre",400,400);
    //  coordonnées de la fenetre
    c.Range(0,0,300,300);

    while(1)
    {
        //  dessin de la balle à t=0
        TEllipse balle(10,10,5);
        balle.SetFillColor(kBlack);
        balle.Draw();
        //  dessin du vecteur v0
        TArrow *l=new TArrow(10,10,xt,yt); // x1,y1,x2,y2
        l->SetLineColor(kBlue);
        l->Draw();

        //  Création du menu
        int choix;
        cout << "Bienvenue dans le menu de flyingTurtles !!" << endl;
        cout << endl << "Choisissez votre mode !" << endl;
        cout << "1) Lancer simple d'une tortue sans frottement du à l'air mais avec des rebonds" << endl;
        cout << "2) Lancer simple d'une tortue avec frottement du à l'air ou à un fluide" << endl;
        cin >> choix;

        if(choix==1)
        {
            cout << "Rentrez la vitesse initial (en m/s) de la boule !" << endl;
            cin >> v0;
            cout << "A quelle angle voulez vous lancer la balle"<< endl <<"(angle en degré par rapport à l'horizontal donc entre 0 et 90°) ?" << endl;
            cin >> theta0;
            cout << "Donner le coefficient de rebondissement du sol"<< endl <<"(entre 0 et 1; 1 rebond sans frottement) ?" << endl;
            cin >> coeffRebond;

            thetarad = theta0*2*M_PI/360;
            xt = v0*cos(thetarad);
            yt = v0*sin(thetarad);

            double precedente[2];

            //cout << "on entre dans la boucle while" << endl;

            while(x1<300)
            {
                if(y1 < 0)
                {
                    v0 *= coeffRebond;
                    t = 0;
                    x0 = x1;
                }
                double *coord = sansFrottement(v0,thetarad,t,x0);
                t += dt;
                x1 = coord[0];
                y1 = coord[1];
                balle.SetX1(coord[0]);
                balle.SetY1(coord[1]);
                balle.Draw();

                this_thread::sleep_for(chrono::milliseconds{dt/2});   // attend dt millisecondes
                c.Update();                                           // mise à jour de la fenêtre c
            }

            c.Closed();
        }

        if(choix==2)
        {
            cout << "Rentrez la vitesse initial (en m/s) de la boule !" << endl;
            cin >> v0;
            cout << "A quelle angle voulez vous lancer la balle (angle en degré par rapport à        l'horizontal donc entre 0 et 90°) ?" << endl;
            cin >> theta0;
            cout << "Donner le rapport m/k qui représente le coefficient de frottement ?" << endl;
            cin >> tau;

            thetarad = theta0*2*M_PI/360;
            xt = v0*cos(thetarad);
            yt = v0*sin(thetarad);

            while(y1>=0)
            {
                double *coord = avecFrottement(v0,thetarad,t,tau);
                t += dt;
                y1 = coord[1];
                balle.SetX1(coord[0]);
                balle.SetY1(coord[1]);
                balle.Draw();

                this_thread::sleep_for(chrono::milliseconds{dt/2});   // attend dt millisecondes
                c.Update();                                           // mise à jour de la fenêtre c
            }

            c.Closed();
        }

    }

    return 0;
}
