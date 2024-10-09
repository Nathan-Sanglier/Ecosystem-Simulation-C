#ifndef _COMPORTEMENTKAMIKAZE_H
#define _COMPORTEMENTKAMIKAZE_H

#include "Comportement.h"
#include "Constantes.h"

class ComportementKamikaze : public Comportement {
    private :

        static const double     ACC_FACTEUR;

        // utile pour track la phase d'accélération
        bool                    accStarted;

        // (R,G,B) pour la couleur associée au comportement 
        int                     rougeCouleur;
        int                     vertCouleur;
        int                     bleuCouleur;

    public :

        ComportementKamikaze();
        void                            setBougeProprietes(Bestiole &b)    override;
        void                            setCouleur(Bestiole &b)            override;
        std::string                     getComportementType()              override;
        int*                            getCouleurSecondaire()             override;
        std::unique_ptr<Comportement>   clone()                      const override {return std::make_unique<ComportementKamikaze>(*this);}; 
};

#endif 
