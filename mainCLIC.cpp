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
#include <TMarker.h>

using namespace std;


//====Ma Classe Fenetre================================
class Fenetre: public TCanvas
{
    public:
    // constructeur ......
    Fenetre(Text_t* name, Text_t* title, Int_t ww, Int_t wh) : TCanvas(name,title,ww,wh)
    { }
    //—- Cette fonction est appelle si la souris s'agitte. ——
    void ExecuteEvent(Int_t event, Int_t px, Int_t py)
    {
        //– affiche l'etat de la souris ——–
        cout<<" position: px="<<px<<" py="<<py<<" code du bouton="<<event<<endl;
        //– convertit la position en pixel px,py en coordonnees (x,y) ——
        double x = gPad->AbsPixeltoX(px);
        double y = gPad->AbsPixeltoY(py);
        // si bouton gauche appuye dessine un point —
        if(event==1)
        {
            TMarker *m=new TMarker(x,y,8);
            cout << "x=" << x << " et y=" << y <<endl;

            m->Draw();
            Update();
        }

        //—————— Event clavier ——————–
        if (event==kKeyPress) // touche appuyée
        {
            cout<<"touche px="<<px<<endl;
            switch (px)
            {
                //——— change de mode (tempéré <-> juste) ——–
                case 'm':
                cout<<"Touche m appuyée"<<endl;
                break;
            }; // switch px
        } // if event
    }
};


int main(int argc, char **argv)
{
    double px,py;
    //  initialisation de root
    TApplication theApp("App", &argc, argv);
    //  création de la fenêtre
    Fenetre c("c","fenetre",400,400);
    //  coordonnées de la fenetre
    c.Range(0,0,300,300);


    for(int i=0;i<3;i++)
    {
        cout <<i<<endl;
    }
    theApp.Run();
    return 0;
}
