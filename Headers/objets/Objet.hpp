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
        void utiliser();  /* utiliser dans le sens afficher sa description, son nom, son effet ?/*

};

#endif // OBJET_HPP
