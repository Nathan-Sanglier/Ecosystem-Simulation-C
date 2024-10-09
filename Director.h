#ifndef _DIRECTOR_H_
#define _DIRECTOR_H_


#include <random>
#include <iostream>
#include <memory>
#include "Builder.h"

/*
Classe permettant de set un builder qui va servir à construire une bestiole; fait partie du DP Builder
Director permet de créer une bestiole via le builder en fonction des données qui lui sont passées
*/

class Director {

    private:

        std::unique_ptr<Builder>    builder;

    public:

        void                        setBuilder(std::unique_ptr<Builder> b);
        std::unique_ptr<Bestiole>   make(const std::vector<int> dataInit);
};

#endif 