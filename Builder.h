#ifndef _BUILDER_H_
#define _BUILDER_H_


#include <random>
#include <iostream>
#include <memory>
#include "Bestiole.h"

/*
Interface pour construire les bestioles; fait partie du DP Builder
Ici, on a qu'un seul type de bestiole, donc pas forcément nécessaire,
mais c'est en prévision de si on ajoute d'autres types de bestioles
*/
class Builder {

    protected :

        std::unique_ptr<Bestiole>           bestiole;

    public:
        virtual void                        reset()                                 = 0;
        virtual void                        initBestiole(int numComportement)       = 0;
        virtual void                        addYeux()                               = 0;
        virtual void                        addOreilles()                           = 0;
        virtual void                        addCamouflage()                         = 0;
        virtual void                        addCarapace()                           = 0;
        virtual void                        addNageoires()                          = 0;
        virtual std::unique_ptr<Bestiole>   getBestioleFinale()                     = 0;
        virtual                             ~Builder(){};
        
};

#endif 