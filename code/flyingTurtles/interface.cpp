#include "interface.h"

Interface::Interface()
{

}

void Interface::menu()
{
    cout << endl;

    cout << "********************************************************************************" << endl;
    cout << "****************** Bienvenue dans le menu de flyingTurtles !! ******************" << endl;
    cout << "********************************************************************************" << endl;

    cout << endl << "Combien de tortues voulez-vous jeter ?" <<endl;
    cin >> Nshots;
}
