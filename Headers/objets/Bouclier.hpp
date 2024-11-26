#ifndef BOUCLIER_HPP
#define BOUCLIER_HPP

#include "../Headers/objets/Objet.hpp"
#include <iostream>
using namespace std;

class Bouclier : public Objet {
    public:
        Bouclier(string nom, string description, int effet, int defense);
        ~Bouclier();

        void utiliser() override; // Méthode pour utiliser le bouclier (augmente la défense)

    private:
        int defense;
};

#endif // BOUCLIER_HPP