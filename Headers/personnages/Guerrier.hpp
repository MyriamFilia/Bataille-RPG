#ifndef GUERRIER_HPP
#define GUERRIER_HPP

#include "Personnage.hpp"

class Guerrier : public Personnage
{
    public:
        Guerrier(); 
        void attaquer(Personnage &cible); //attaque de base
        void enrage(); //attaque qui va consommé de la rage capacite speciale

        
    private:
        int rage; 

};

#endif // GUERRIER_HPP