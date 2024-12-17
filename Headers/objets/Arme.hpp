#ifndef ARME_HPP
#define ARME_HPP


#include "../Headers/objets/Objet.hpp"
#include "../Headers/personnages/Personnage.hpp"

#include <iostream>
using namespace std;


class Arme : public Objet {
    public:
        Arme(string nom, string description, int durabilite);
        void utiliser(Personnage *joueur) override;

    private:
        int durabilite; // Durabilité de l'arme
};

#endif // ARME_HPP