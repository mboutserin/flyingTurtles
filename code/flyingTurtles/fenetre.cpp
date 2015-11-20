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


    int compteTirs=0;
    //––––––––––––– Si bouton gauche appuyé dessine un point ––––––––––––––
    if(event==1 && compteTirs<jeu.getOptions().getNombreTirs())
    {
//cout << "position souris : x=" << x << ", y=" << y << endl;
        jeu.initTortue(x,y);
//cout << "vitesse tortue après clic : x=" << jeu.getTortue().getVx() << " et y=" << jeu.getTortue().getVy() << endl;

        //  Dessin du vecteur v0
        TArrow *vecteurV0=new TArrow(0,0,x,y);
        vecteurV0->SetLineColor(kBlack);
        vecteurV0->SetLineWidth(2);
        vecteurV0->Draw();
        Update();

        while(jeu.lancerDeTortue())
        {
            //  Mise à jour de la fenêtre c (dessin de la balle)
            Update();
        }
        if(compteTirs == jeu.getOptions().getNombreTirs()){ cout << "Attention, c'est votre dernier tire. A vous !" << endl;}
        if(compteTirs < jeu.getOptions().getNombreTirs()){ cout << "A vous !" << endl;}
        compteTirs++;
    }   //  end if (event==1)

}       //  ExecuteEvent

