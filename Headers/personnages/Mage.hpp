#ifndef MAGE_HPP
#define MAGE_HPP

#include "../Headers/personnages/Personnage.hpp"

class Mage : public Personnage {
    public:
        Mage(string nom);
        void attaquer(Personnage &cible);
        void lancerSort(); 
        void rechargerPuissanceMagique(int quantite);
        void utiliserCapaciteSpeciale(Personnage &cible, int index) override;
        //méthode pour lancer un sort en utilisant de la puissance magique capacite speciale

    private:
        int puissanceMagique; 
        /*Liste de capacités magique -- sorts ???*/

};

#endif // MAGE_HPP