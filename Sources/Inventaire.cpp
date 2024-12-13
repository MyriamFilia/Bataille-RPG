#include "../Headers/Inventaire.hpp"
#include "../Headers/objets/Objet.hpp"  
#include "../Headers/personnages/Personnage.hpp"



#include <iostream>
using namespace std;

Inventaire::Inventaire() {}

void Inventaire::ajouterObjet(Objet *objet)
{
    objets.push_back(objet);
    cout << objet->getNom() << " a été ajouté à l'inventaire." << endl;
}

void Inventaire::retirerObjet(Objet *objet)
{
    for (auto it = objets.begin(); it != objets.end(); ++it) {
        if (*it == objet) {
            delete *it;
            objets.erase(it);
            cout << objet->getNom() << " a été retiré de l'inventaire." << endl;
            return;
        }
    }
    cout << "Objet introuvable." << endl;
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
    objet->utiliser(joueur);
    retirerObjet(objet);
}

Objet* Inventaire::getObjet(int index)
{
    if (index < 0 || index >= static_cast<int>(objets.size())) return nullptr;
    return objets[index];
}

int Inventaire::getNbObjets()
{
    return objets.size();
}
