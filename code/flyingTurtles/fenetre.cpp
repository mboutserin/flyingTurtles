#include "fenetre.h"


Fenetre::Fenetre(TString name, TString title, Int_t ww, Int_t wh, Jeu &j) : TCanvas(name,title,ww,wh)
{
    jeu = j;
}

void Fenetre::ExecuteEvent(Int_t event, Int_t px, Int_t py)
{

    //———————————————————— Affiche l'état de la souris ————————————————————


    //–––– Convertit la position en pixel (px,py) en coordonnees (x,y) ——––
    Double_t x = gPad->AbsPixeltoX(px);
    Double_t y = gPad->AbsPixeltoY(py);

    //––––––––––––– Si bouton gauche appuyé dessine un point ––––––––––––––
    if(event==1 && jeu.autorisationTir())
    {
//cout << "position souris : x=" << x << ", y=" << y << endl;
        jeu.initTortue(x,y);
//cout << "vitesse tortue après clic : x=" << jeu.getTortue().getVx() << " et y=" << jeu.getTortue().getVy() << endl;
        Update();

        while(jeu.lancerDeTortue())
        {
            //  Mise à jour de la fenêtre c (dessin de la balle)
            Update();
            if(jeu.isVictoire())
            {
                exit(0);
            }
        }
    }else if(!jeu.autorisationTir())   //  end if (event==1)
    {
        exit(0);
    }

}       //  ExecuteEvent

