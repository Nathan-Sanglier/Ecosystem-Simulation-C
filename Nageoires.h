#ifndef _NAGEOIRES_H_
#define _NAGEOIRES_H_


#include <random>
#include <iostream>
#include "Constantes.h"
#include <memory>

class Nageoires {

    private:

        double                          vitesseBoost;

    public:

        Nageoires();
        ~Nageoires() {};

        static const double             VITESSE_BOOST_MIN;
        static const double             VITESSE_BOOST_MAX; 
        
        double                          getVitesseBoost()   const {return vitesseBoost;};
        std::unique_ptr<Nageoires>      clone()             const {return std::make_unique<Nageoires>(*this);}; // méthode pour cloner l'accessoire nageoire
};

#endif 