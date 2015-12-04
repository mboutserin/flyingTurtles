#include "interface.h"

Interface::Interface()
{
    modeleTortue = TEllipse(0,0,5);
    modeleTortue.SetLineColor(kGreen+3);
}

void Interface::menu(Options &options)
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
    TBox *dessinEnnemi = new TBox(ennemi.getX()-ennemi.getLongueur(),ennemi.getY()-ennemi.getHauteur(),ennemi.getX(),ennemi.getY());
    dessinEnnemi->SetFillColor(kRed);
    dessinEnnemi->Draw();
}

void Interface::dessinVent(double vent)
{
    if(vent != 0){
        TArrow *vecteurVent = new TArrow(245,290,245 + 5*vent,290);
        vecteurVent->SetLineColor(kBlack);
        vecteurVent->Draw();
    }

}

// à l'initialisation, la tortue est ainsi.
void Interface::dessinTortue(Objet t)
{
    modeleTortue.SetX1(t.getX());
    modeleTortue.SetY1(t.getY());
    modeleTortue.Draw();
}

void Interface::dessinMonde(int sol, Objet ennemi, double vent, Objet tortue)
{
    dessinSol(sol);
    dessinEnnemi(ennemi);
    dessinVent(vent);
    dessinTortue(tortue);
}

void Interface::dessinV0(double x, double y)
{
        //  Dessin du vecteur v0
        vecteurV0=TArrow(0,0,x,y);
        vecteurV0.SetLineColor(kBlack);
        vecteurV0.SetLineWidth(2);
        vecteurV0.Draw();
}

void Interface::avertirTirs(int tirRestants)
{
    if(tirRestants < 1)
    {
        cout << "Terminé !" << endl;
    }
    else if(tirRestants == 1)
    {
        cout << "Attention, c'est votre dernier tire. A vous !" << endl;
    }
    else
    {
        cout << "A vous !" << endl;
    }
}

void Interface::victoire()
{
    cout << "Vous avez gagné !" << endl;
}
