#ifndef FENETRE_H
#define FENETRE_H

#include "TCanvas.h"
#include "jeu.h"

//============================== Ma Classe Fenetre ==============================
class Fenetre: public TCanvas
{
    public:
    Jeu jeu;
    // constructeur ......
    Fenetre(TString name, TString title, Int_t ww, Int_t wh, Jeu &j);// : TCanvas(name,title,ww,wh);
    //————————————— Cette fonction est appelle si la souris s'agitte —————————————
    void ExecuteEvent(Int_t event, Int_t px, Int_t py);

};


#endif // FENETRE_H
