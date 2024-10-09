#ifndef _COMPORTEMENTPREVOYANTE_H
#define _COMPORTEMENTPREVOYANTE_H

#include "Comportement.h"


class ComportementPrevoyante : public Comportement {

    private :
        // (R,G,B) pour la couleur associée au comportement
        int rougeCouleur;
        int vertCouleur;
        int bleuCouleur;

    public :

        ComportementPrevoyante();
        void                            setBougeProprietes(Bestiole &b)     override;
        void                            setCouleur(Bestiole &b)             override;
        std::string                     getComportementType()               override;
        int*                            getCouleurSecondaire()              override; 
        std::unique_ptr<Comportement>   clone()                       const override {return std::make_unique<ComportementPrevoyante>(*this);}; 
};

#endif 
