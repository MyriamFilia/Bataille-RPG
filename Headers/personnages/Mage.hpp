#ifndef MAGE_HPP
#define MAGE_HPP

#include "../Headers/personnages/Personnage.hpp"
#include "../Headers/objets/Objet.hpp"

class Mage : public Personnage {
    public:
        Mage(string nom);
        int attaquer(Personnage &cible) override;
        void rechargerPuissanceMagique(int quantite);
        void utiliserCapaciteSpeciale(Personnage &cible, int index) override;
        //méthode pour lancer un sort en utilisant de la puissance magique capacite speciale
        void reset() override; //réinitialisation des statistiques

    private:
        int puissanceMagique; 
        /*Liste de capacités magique -- sorts ???*/

};

#endif // MAGE_HPP