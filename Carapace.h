#ifndef _CARAPACE_H_
#define _CARAPACE_H_


#include <random>
#include <iostream>
#include "Constantes.h"
#include <memory>

class Carapace {

    private:

        double                      mortReduc;
        double                      vitesseReduc;

    public:

        // Cf "Constantes.cpp"

        static const double         MORT_REDUC_MIN;
        static const double         MORT_REDUC_MAX;

        static const double         VITESSE_REDUC_MIN;
        static const double         VITESSE_REDUC_MAX;

        Carapace();
        ~Carapace() {};
        double getMortReduc()       const   {return mortReduc;};
        double getVitesseReduc()    const   {return vitesseReduc;};
        std::unique_ptr<Carapace> clone() const {return std::make_unique<Carapace>(*this);}; // méthode pour cloner l'accessoire carapace
};

#endif 