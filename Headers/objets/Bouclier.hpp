#ifndef BOUCLIER_HPP
#define BOUCLIER_HPP

#include <string>
#include "../Headers/objets/Objet.hpp"
#include "../Headers/personnages/Personnage.hpp"

using namespace std;

class Bouclier : public Objet
{
protected:
    int defense;

public:
    Bouclier(string nom, string description, int effet, int defense);
    virtual ~Bouclier();

    // Garder la méthode avec les paramètres
    virtual void utiliser(Personnage &joueur, Personnage &cible); // Ajout des paramètres
};

#endif // BOUCLIER_HPP
