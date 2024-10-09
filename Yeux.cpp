#include "Yeux.h"

const double Yeux::RANGE_MAX        = Constantes::YEUX_RANGE_MAX; 
const double Yeux::ANGLE_MAX        = Constantes::YEUX_ANGLE_MAX;
const double Yeux::DETECTION_MAX    = Constantes::YEUX_DETECTION_MAX;

const double Yeux::RANGE_MIN        = Constantes::YEUX_RANGE_MIN; 
const double Yeux::ANGLE_MIN        = Constantes::YEUX_ANGLE_MIN;
const double Yeux::DETECTION_MIN    = Constantes::YEUX_DETECTION_MIN;

/*
Constructeur de camouflage
Initialisation de la distance max de detection par la vue, via une loi uniforme
Initialisation de la valeur de la detection de la vue (i.e. performance de la detection), via une loi uniforme
Initialisation de l'angle de detection de la vue, via une loi uniforme
*/
Yeux::Yeux() {
    std::random_device                  rd;
    std::mt19937                        gen(rd()); 
    std::uniform_real_distribution<>    rangeDis(RANGE_MIN, RANGE_MAX);
    std::uniform_real_distribution<>    angleDis(ANGLE_MIN, ANGLE_MAX);
    std::uniform_real_distribution<>    detectionDis(DETECTION_MIN, DETECTION_MAX);

    rangeVal        =                   rangeDis(gen);
    angleVal        =                   angleDis(gen);
    detectionVal    =                   detectionDis(gen);
}
