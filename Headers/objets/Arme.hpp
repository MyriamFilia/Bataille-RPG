#ifndef ARME_HPP
#define ARME_HPP

#include "Objet.hpp"

class Arme : public Objet {
    public:
        Arme();
        /*Arme(string nom, string description, int puissance);*/
        void utiliser(); //en diminuant la durabilite

    private:
        int durabilite;
};

#endif // ARME_HPP