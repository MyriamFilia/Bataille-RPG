#ifndef POTION_HPP
#define POTION_HPP

#include "../Headers/objets/Objet.hpp"
#include "../Headers/personnages/Personnage.hpp"


class Potion : public Objet {
    public:
        Potion(string nom, string description,int point);
        void utiliser(Personnage *joueur); // Méthode pour utiliser la potion ( rajoute dees PV en utilisant la puissance)
        
    private:
        int point; // Puissance de la potion
};

#endif // POTION_HPP