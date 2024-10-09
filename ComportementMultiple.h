#ifndef _COMPORTEMENTMULTIPLE_H
#define _COMPORTEMENTMULTIPLE_H

#include "Comportement.h"
#include "Constantes.h"

class ComportementMultiple : public Comportement {

    private : 

        static const int                        NB_STEPS_COMPORTEMENT; 

        int                                     cumulSteps; // pour track la durée courante du comportement 

        // ComportementMultiple a son propre comportement et celui-ci va changer au cours du temps
        shared_ptr<Comportement>                comportement; 
        vector< shared_ptr<Comportement>>       listeComportements;

        // (R,G,B) pour la couleur associée au comportement
        int                                     rougeCouleur;
        int                                     vertCouleur;
        int                                     bleuCouleur;

    
    public :

        ComportementMultiple();
        ComportementMultiple(const ComportementMultiple &compMul);
        void                                    setBougeProprietes(Bestiole &b)     override;
        void                                    setCouleur(Bestiole &b)             override;
        std::string                             getComportementType()               override;
        int*                                    getCouleurSecondaire()              override;
        std::unique_ptr<Comportement>           clone()                       const override; 
};

#endif 
