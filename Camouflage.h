#ifndef _CAMOUFLAGE_H_
#define _CAMOUFLAGE_H_

#include <random>
#include <iostream>
#include "Constantes.h"
#include <memory>

using namespace std;

class Camouflage {

    private:

        double                  camouflageVal;

    public:

        // cf "Constantes.cpp"
        static const double     CAMOUFLAGE_MIN;
        static const double     CAMOUFLAGE_MAX;

        Camouflage();
        ~Camouflage() {};
        double getCamouflageVal() const {return camouflageVal;};
        std::unique_ptr<Camouflage> clone() const {return std::make_unique<Camouflage>(*this);}; // méthode pour cloner l'accessoire camouflage
};

#endif 