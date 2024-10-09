#ifndef _AQUARIUM_H_
#define _AQUARIUM_H_

#include <iostream>
#include <CImg.h>

using namespace std;
using namespace cimg_library;

class Milieu;

class Aquarium : public CImgDisplay {

private :
   
   Milieu            *milieu;                         // Un aquarium contient un milieu (i.e. environnement accueillant les bestioles)
   unsigned long     ticks = 0;                       // Nombre de steps actuels de la simulation (s'incrémente à chaque step) 
   int               delay;                           // Delay pour l'affichage

   int               identiteToDelete;                // Identité de la bestiole à supprimer via appui sur touche (cf cpp file)
   int               identiteToModifComportement;     // Indetité de la bestiole à modifier comportement via appui sur touche (cf cpp file)

public :

   Aquarium(int width, int height, int _delay);
   ~Aquarium();

   Milieu&           getMilieu()       {return *milieu;};
   unsigned long     getTicks() const  {return ticks;};
   void              run();
   void              collectEtSaveStateToCSV(const string& filename, unsigned long ticks);   // Pour sauvegarder l'état actuel de la simulation dans un fichier csv
   void              writeConstantsToCSV(const string& filename);                            // Pour sauvegarder les constantes de la simulation dans un fichier csv
};

#endif
