#include "interface.h"

Interface::Interface()
{
}

void Interface::menu(Options options)
{
    int Nshots;
    cout << endl;

    cout << "********************************************************************************" << endl;
    cout << "****************** Bienvenue dans le menu de flyingTurtles !! ******************" << endl;
    cout << "********************************************************************************" << endl;

    cout << endl << "Combien de tortues voulez-vous jeter ?" <<endl;
    cin >> Nshots;
    options.setNombreTirs(Nshots);
    cout << "CLIQUEZ avec la souris dans la fenêtre afin de faire voler les tortues." << endl;

}


void Interface::dessinSol(int typeSol)
{

    if(typeSol == 0)
    {
        for(int x = 0 ; x < 300 ; x += 5)
        {
            TLine *herbe=new TLine(x,0,x+1,5); // x1,y1,x2,y2
            herbe->SetLineColor(kGreen+1);
            herbe->SetLineWidth(2);
            herbe->Draw();
        }
    }
    else if(typeSol == 1)
    {
        for(int x = 0 ; x < 300 ; x += 6)
        {
            TEllipse *boue= new TEllipse(x,0,3);    	// Centre (x,y) et rayon r
            boue->SetFillColor(kRed+2);
            boue->Draw();
        }
    }
    else if(typeSol == 2)
    {
        TBox *beton=new TBox(0,0,300,2);            	// On précise les coins bas-gauche (x1,y1) et haut droit (x2,y2)
        beton->SetFillColor(kGray+2);
        beton->Draw();
    }
}

void Interface::dessinEnnemi(Objet ennemi)
{
    //  Dessin de l'ennemi
    TBox *dessinEnnemi=new TBox(ennemi.getX()-ennemi.getLongueur(),ennemi.getY()-ennemi.getHauteur(),ennemi.getX(),ennemi.getY());
    dessinEnnemi->SetFillColor(kRed);
    dessinEnnemi->Draw();
}

void Interface::dessinVent(double vent)
{
    TArrow vecteurVent = TArrow(245,290,245 + 2*vent,290);
    vecteurVent.SetLineColor(kBlack);
    vecteurVent.Draw();
}

// à l'initialisation, la tortue est ainsi.
void Interface::dessinTortue(Objet t)
{
    TEllipse balle(0,0,5);
    balle.SetLineColor(kGreen+3);
    balle.SetX1(t.getX());
    balle.SetY1(t.getY());
    balle.Draw();
}

void Interface::dessinMonde(int sol, Objet ennemi, double vent, Objet tortue)
{
    dessinSol(sol);
    dessinEnnemi(ennemi);
    dessinVent(vent);
    dessinTortue(tortue);
}
