#ifndef ARENE_HPP
#define ARENE_HPP

#include <vector>
#include "Guerrier.hpp"

class Arene {
    public:
        Arene();
        void commencerCombat();
        void tourDeCombat();
        void finDeCombat();
        
    private:
        std::vector<Personnage> personnages;
};

#endif // ARENE_HPP