#ifndef MAGE_HPP
#define MAGE_HPP

#include "Personnage.hpp"

class Mage : public Personnage {
    public:
        Mage();
        void attaquer(Personnage &cible);
        void lancerSort(); //méthode pour lancer un sort en utilisant de la puissance magique capacite speciale

    private:
        int puissanceMagique; 
        /*Liste de capacités magique -- sorts ???*/

};

#endif // MAGE_HPP