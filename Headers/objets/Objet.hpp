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
        Objet();
        Objet(string nom, string description, int effet);
        void utiliser();
};

#endif // OBJET_HPP