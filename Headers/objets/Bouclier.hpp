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
    Bouclier(string nom, string description, int defense);
    void utiliser(Personnage *joueur) override;
};

#endif // BOUCLIER_HPP
