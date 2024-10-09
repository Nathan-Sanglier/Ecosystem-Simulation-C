#include <utility>

#include "BestioleBuilder.h"
#include "ComportementGregaire.h"
#include "ComportementPeureuse.h"
#include "ComportementKamikaze.h"
#include "ComportementPrevoyante.h"
#include "ComportementMultiple.h"

// permet de reset le pointeur associé à la bestiole créée avant (nullptr), pour signifier su'on repart sur la création d'une nouvelle bestiole (cf Director.cpp)
void BestioleBuilder::reset() {
    bestiole.reset(); 
}

/*
Création de la bestiole en fonction du comportement d'entrée, donné par un nombre (un numéro pour chaque comportement); cf Director.cpp
C'est une bestiole basique, sans accessoires ni capteurs qui est créée
*/
void BestioleBuilder::initBestiole(int numComportement) {

    switch(numComportement) {
        case 1: {
            std::unique_ptr<ComportementGregaire> cGreg     = std::make_unique<ComportementGregaire>();
            bestiole                                        = std::make_unique<Bestiole>(std::move(cGreg));
            break;
        }
        case 2: {
            std::unique_ptr<ComportementPeureuse> cPeur     = std::make_unique<ComportementPeureuse>();
            bestiole                                        = std::make_unique<Bestiole>(std::move(cPeur));
            break;
        }
        case 3: {
            std::unique_ptr<ComportementKamikaze> cKam      = std::make_unique<ComportementKamikaze>();
            bestiole                                        = std::make_unique<Bestiole>(std::move(cKam));
            break;
        }
        case 4: {
            std::unique_ptr<ComportementPrevoyante> cPrev   = std::make_unique<ComportementPrevoyante>();
            bestiole                                        = std::make_unique<Bestiole>(std::move(cPrev));
            break;
        }
        case 5: {
            std::unique_ptr<ComportementMultiple> cMult     = std::make_unique<ComportementMultiple>();
            bestiole                                        = std::make_unique<Bestiole>(std::move(cMult));
            break;
        }
    }
}

// Méthodes pour ajouter capteurs / accessoires à la bestiole basique


void BestioleBuilder::addOreilles() {
    bestiole->setOreilles();
}


void BestioleBuilder::addYeux() {
    bestiole->setYeux();
}


void BestioleBuilder::addCarapace() {
    bestiole->setCarapace();
}


void BestioleBuilder::addCamouflage() {
    bestiole->setCamouflage();
}


void BestioleBuilder::addNageoires() {
    bestiole->setNageoires();
}

// Retourne la bestiole finale
std::unique_ptr<Bestiole> BestioleBuilder::getBestioleFinale() {
    return std::move(bestiole);
}