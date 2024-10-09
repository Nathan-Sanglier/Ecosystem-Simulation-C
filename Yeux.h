#ifndef _YEUX_H_
#define _YEUX_H_


#include <random>
#include <iostream>
#include "Constantes.h"
#include <memory>

class Yeux {

    private :

        double                      angleVal;
        double                      rangeVal;
        double                      detectionVal;

    public :

        Yeux();
        ~Yeux() {};

        static const double         RANGE_MIN;
        static const double         RANGE_MAX ;

        static const double         ANGLE_MIN;
        static const double         ANGLE_MAX ;

        static const double         DETECTION_MIN;
        static const double         DETECTION_MAX;
        
        double                      getAngleVal()       const {return angleVal;};
        double                      getRangeVal()       const {return rangeVal;};
        double                      getDetectionVal()   const {return detectionVal;};
        std::unique_ptr<Yeux>       clone()             const {return std::make_unique<Yeux>(*this);}; // méthode pour cloner le capteur yeux
        
};

#endif 