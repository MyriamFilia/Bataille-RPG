#ifndef OGRE_HPP
#define OGRE_HPP

#include "../Headers/personnages/Personnage.hpp"
#include "../Headers/objets/Objet.hpp"
class Ogre : public Personnage {
    public:
       public:
        Ogre(string nom);
        int attaquer(Personnage &cible) override; //attaque de base
        void utiliserCapaciteSpeciale(Personnage &cible , int index) override; //capacité spéciale
        void rechargerRage(int quantite); //recharge de la rage
        void reset() override; //réinitialisation des statistiques
        int getRessource() override;
        
    private:
        int rage; 
    
};

#endif // OGRE_HPP