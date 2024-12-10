#ifndef OGRE_HPP
#define OGRE_HPP

#include "../Headers/personnages/Personnage.hpp"

class Ogre : public Personnage {
    public:
        Ogre();
        int attaquer(Personnage &cible);
        void coupEcrasant(); //consomme la force brute et la resistance capacite speciale

    private:
        int forceBrute;
        int resistance;
    
};

#endif // OGRE_HPP