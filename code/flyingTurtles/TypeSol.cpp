#include "TypeSol.h"
#include <math.h>
#include <thread>
#include <TLine.h>
#include <TEllipse.h>
#include <TBox.h>


TypeSol::TypeSol()
{
    srand(time(NULL)); // initialise le hasard (1 seule fois)
    S = 2;
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

    if(typeSol == 2)
    {
        coeffRebond = 0.95;
        TBox *beton=new TBox(0,0,300,2);            	// On précise les coins bas-gauche (x1,y1) et haut droit (x2,y2)
        beton->SetFillColor(kGray+2);
        beton->Draw();
    }
    //ctor
}

TypeSol::~TypeSol()
{
    //dtor
}


//  Données concernant le choix du sol choisis aléatoirement
//  typeSol = 0 --> herbe
//  typeSol = 1 --> béton
//  typeSol = 2 --> boue
//  La boue et le béton se dessine après l'ennemi car l'ennemi ne peut écraser le béton (simple soucis de logique)




