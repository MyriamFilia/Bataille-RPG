#ifndef OBJET_HPP
#define OBJET_HPP

class Personnage;
#include <string>
#include <iostream>
using namespace std; 

class Objet {

    protected:
        string nom;
        string description;

    public:
        Objet(string nom, string description);
        virtual ~Objet();
        virtual void utiliser(Personnage *joueur);
        string getNom() ;
};

#endif // OBJET_HPP