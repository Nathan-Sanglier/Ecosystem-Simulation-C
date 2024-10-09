#ifndef _OREILLES_H_
#define _OREILLES_H_


#include <random>
#include <iostream>
#include "Constantes.h"
#include <memory>

class Oreilles {

    private:

        int                         rangeVal;
        int                         detectionVal;

    public:

        Oreilles();
        ~Oreilles() {};

        static const double         RANGE_MIN;
        static const double         RANGE_MAX;
        
        static const double         DETECTION_MIN;
        static const double         DETECTION_MAX;
        
        int                         getRangeVal()       const {return rangeVal;};
        int                         getDetectionVal()   const {return detectionVal;};
        std::unique_ptr<Oreilles>   clone()             const {return std::make_unique<Oreilles>(*this);}; // méthode pour cloner le capteur oreilles
        
};

#endif 