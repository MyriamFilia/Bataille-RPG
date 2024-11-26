#ifndef OBJET_HPP
#define OBJET_HPP

#include <string>
#include <iostream>
using namespace std; 

class Objet {

    protected:
        string nom;
        string description;
        int effet;

    public:
        Objet(string nom, string description, int effet);
        virtual ~Objet();
        virtual void utiliser();
        int getEffet() ;
        string getNom() ;
};

#endif // OBJET_HPP