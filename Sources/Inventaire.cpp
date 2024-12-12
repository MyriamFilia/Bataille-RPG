#include "../Headers/Inventaire.hpp"  // Inclure Inventaire.hpp
#include "../Headers/personnages/Personnage.hpp"  // Inclure Personnage.hpp pour utiliser un pointeur vers Personnage
#include "../Headers/objets/Objet.hpp"  


#include <iostream>
using namespace std;

Inventaire::Inventaire() {}

void Inventaire::ajouterObjet(Objet *objet)
{
    objets.push_back(objet);
}

void Inventaire::retirerObjet(Objet *objet)
{
    for (size_t i = 0; i < objets.size(); ++i)
    {
        if (objets[i] == objet)
        {
            objets.erase(objets.begin() + i);
            break;
        }
    }
}

void Inventaire::afficherInventaire()
{
    if (objets.empty())
    {
        cout << "Inventaire vide." << endl;
    }
    else
    {
        cout << "Inventaire :\n";
        for (size_t i = 0; i < objets.size(); ++i)
        {
            cout << i + 1 << ". " << objets[i]->getNom() << endl;
        }
    }
}

void Inventaire::utiliserObjet(Personnage *joueur,Objet *objet)
{
    for (size_t i = 0; i < objets.size(); ++i)
    {
        if (objets[i] == objet)
        {
            objets[i]->utiliser(joueur);
            retirerObjet(objet);
        }
    }
}

Objet* Inventaire::getObjet(int index)
{
    if (index >= 0 && index < objets.size())
    {
        return objets[index];
    }
    return nullptr;
}
