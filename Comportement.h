#ifndef _COMPORTEMENT_H_
#define _COMPORTEMENT_H_

#include "Bestiole.h"
#include <cmath>

class Bestiole;


class Comportement  {

public :

   // tous les comportements vont modifier la vitesse et/ou orientation de la bestiole; on peut voir ça comme un DP Strategy
   virtual void                              setBougeProprietes(Bestiole &b)     = 0; 
   virtual void                              setCouleur(Bestiole &b)             = 0; // tous les comportements sont identifiés par une couleur 
   virtual std::string                       getComportementType()               = 0; // pour l'extraction des données (cf Aquarium.cpp)
   virtual int*                              getCouleurSecondaire()              = 0; // pour comportement multiple
   virtual ~Comportement() {};
   virtual std::unique_ptr<Comportement>     clone()                       const = 0; // méthode pour cloner le comportement; DP Prototype
};


#endif
