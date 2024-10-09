#ifndef _COMPORTEMENTPEUREUSE_H
#define _COMPORTEMENTPEUREUSE_H

#include "Comportement.h"
#include "Constantes.h"


class ComportementPeureuse : public Comportement {

    private : 

        // Constantes, cf Constantes.cpp
        static const int                MAX_VOISINS;
        static const double             ACC_FACTEUR;
        static const int                ACC_DUREE;

        // Pour keep track de la phase d'accélération 
        int                             cumulSteps;
        bool                            accStarted;

        // (R,G,B) pour la couleur associée au comportement
        int                             rougeCouleur;
        int                             vertCouleur;
        int                             bleuCouleur;

    public :

        ComportementPeureuse();
        void                            setBougeProprietes(Bestiole &b)     override;
        void                            setCouleur(Bestiole &b)             override;
        std::string                     getComportementType()               override;
        int*                            getCouleurSecondaire()              override;
        std::unique_ptr<Comportement>   clone()                       const override {return std::make_unique<ComportementPeureuse>(*this);}; 
};

#endif