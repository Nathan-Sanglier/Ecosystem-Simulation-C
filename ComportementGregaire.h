#ifndef _COMPORTEMENTGREGAIRE_H
#define _COMPORTEMENTGREGAIRE_H

#include "Comportement.h"

// Implémentation de l'interface Comportement
class ComportementGregaire : public Comportement {

    private :

        // (R,G,B) pour la couleur associée au comportement 
        int rougeCouleur;
        int vertCouleur;
        int bleuCouleur;

    public :

        ComportementGregaire();
        void                            setBougeProprietes(Bestiole &b)     override;
        void                            setCouleur(Bestiole &b)             override;
        std::string                     getComportementType()               override;
        int*                            getCouleurSecondaire()              override;
        std::unique_ptr<Comportement>   clone()                       const override {return std::make_unique<ComportementGregaire>(*this);};            
};

#endif 
