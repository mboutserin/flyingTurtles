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

double *sansFrottement(double v0, double thetarad, double t)
{
    double x,y;
    x = v0*cos(thetarad)*t/1000;
    y = 10-g*t*t/(2*1000*1000)+v0*sin(thetarad)*t/1000;
    double *u = new double[2];
    u[0] = x;
    u[1] = y;
    return u;
}

double *avecFrottement(double v0, double thetarad, double t, double tau)
{
    double x,y;
    x = tau*v0*cos(thetarad)*(1-exp(-t/(1000*tau)));
    y = 10-g*t*tau/1000+tau*(v0*sin(thetarad)+g*tau)*(1-exp(-t/(tau*1000)));
    double *u = new double[2];
    u[0] = x;
    u[1] = y;
    return u;
}

int main(int argc, char **argv)
{
    //  Création du menu
    int choix;
    cout << "Bienvenue dans le menu de flyingTurtles !!" << endl;
    cout << endl << "Choisissez votre mode !" << endl;
    cout << "1) Lancer simple d'une tortue sans frottement du à l'air" << endl;
    cout << "2) Lancer simple d'une tortue avec frottement du à l'aire ou à un fluide" << endl;
    cin >> choix;

    //  Déclaration içi seulement des variables de départ pour lancer la boule :
    //  - v0 : vitesse initial
    //  - theta0 : angle initial en degré entre l'axe x et v0
    //  - thetarad = theta0 en rad
    //  - tau : coefficient de frottement (rapport m/k)
    //  - xv = v0.cos(theta0)
    //  - yv = v0.sin(theta0)
    double v0,theta0,thetarad,tau,xv,yv;

    //  Déclaration des variables temporelles
    double t;
    int dt;
    t = 0;
    dt = 100;       //  dt en ms

    //  Déclaration de la position
    double x,y,y1;

    while(1)
    {

        if(choix==1)
        {
            cout << "Rentrez la vitesse initial (en m/s) de la boule !" << endl;
            cin >> v0;
            cout << "A quelle angle voulez vous lancer la balle (angle en degré par rapport à        l'horizontal) ?" << endl;
            cin >> theta0;

            thetarad = theta0*2*M_PI/360;
            xv = v0*cos(thetarad);
            yv = v0*sin(thetarad);

            //  initialisation de root
            TApplication theApp("App", &argc, argv);

            //  création de la fenêtre
            TCanvas c("c","fenetre",400,400);

            //  coordonnées de la fenetre
            c.Range(0,0,300,300);

            //  dessin de la balle à t=0
            TEllipse balle(10,10,5);
            balle.SetFillColor(kBlack);
            balle.Draw();

            //  dessin du vecteur v0
            TArrow *l=new TArrow(10,10,xv,yv); // x1,y1,x2,y2
            l->SetLineColor(kBlue);
            l->Draw();

            while(y1>0)
            {
                double *coord = sansFrottement(v0,thetarad,t);
                t += dt;
                y1 = coord[1];
                balle.SetX1(coord[0]);
                balle.SetY1(coord[1]);
                balle.Draw();

                this_thread::sleep_for(chrono::milliseconds{dt/2});   // attend dt millisecondes
                c.Update();                                         // mise à jour de la fenêtre c
            }

            c.Update();
            theApp.Run();
        }

        if(choix==2)
        {
            cout << "Rentrez la vitesse initial (en m/s) de la boule !" << endl;
            cin >> v0;
            cout << "A quelle angle voulez vous lancer la balle (angle en degré par rapport à        l'horizontal) ?" << endl;
            cin >> theta0;
            cout << "Donner le rapport m/k qui représente le coefficient de frottement ?" << endl;
            cin >> tau;

            thetarad = theta0*2*M_PI/360;
            xv = v0*cos(thetarad);
            yv = v0*sin(thetarad);

            //  initialisation de root
            TApplication theApp("App", &argc, argv);

            //  création de la fenêtre
            TCanvas c("c","fenetre",400,400);

            //  coordonnées de la fenetre
            c.Range(0,0,300,300);

            //  dessin de la balle à t=0
            TEllipse balle(10,10,5);
            balle.SetFillColor(kBlack);
            balle.Draw();

            //  dessin du vecteur v0
            TArrow *l=new TArrow(10,10,xv,yv); // x1,y1,x2,y2
            l->SetLineColor(kBlue);
            l->Draw();

            while(y1>0)
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

            c.Update();
            theApp.Run();
        }

    }

    return 0;
}
