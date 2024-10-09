#ifndef _BESTIOLEBUILDER_H_
#define _BESTIOLEBUILDER_H_


#include <random>
#include <iostream>
#include <memory>
#include "Builder.h"

/*
BestioleBuilder implémente l'interface Builder; fait partie du DP Builder
Met à disposition les méthodes pour créer une bestiole via Director
*/
class BestioleBuilder : public Builder {

    public:
    
        void                            reset()                                 override;
        void                            initBestiole(int numComportement)       override;
        void                            addYeux()                               override;
        void                            addOreilles()                           override;
        void                            addCamouflage()                         override;
        void                            addCarapace()                           override;
        void                            addNageoires()                          override;
        std::unique_ptr<Bestiole>       getBestioleFinale()                     override;       
        
};

#endif 