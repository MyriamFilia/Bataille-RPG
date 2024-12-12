#ifndef ARME_HPP
#define ARME_HPP


#include "../Headers/objets/Objet.hpp"
#include <iostream>
using namespace std;


class Arme : public Objet {
    public:
        Arme(string nom, string description, int durabilite);
        ~Arme();

        //void utiliser() override; // Méthode pour utiliser l'arme ( inflige des dégâts en se basant sur l'effet)

    private:
        int durabilite; // Durabilité de l'arme
};

#endif // ARME_HPP