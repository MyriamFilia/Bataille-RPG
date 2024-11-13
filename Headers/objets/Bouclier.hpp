#ifndef BOUCLIER_HPP
#define BOUCLIER_HPP

#include "Objet.hpp"

class Bouclier : public Objet {
    public:
        Bouclier();
        /*virtual ~Bouclier();*/
        void utiliser(); //en utilisant la defense

    private:
        int defense;
};

#endif // BOUCLIER_HPP