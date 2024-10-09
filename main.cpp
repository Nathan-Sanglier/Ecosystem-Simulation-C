#include "Aquarium.h"
#include "Milieu.h"
#include "Bestiole.h"
#include "Comportement.h"
#include "ComportementGregaire.h"
#include "ComportementPeureuse.h"
#include "ComportementKamikaze.h"
#include "ComportementPrevoyante.h"
#include "ComportementMultiple.h"

#include <iostream>

using namespace std;


int main() {

   Aquarium ecosysteme(640, 480, 30); // Création de l'aquarium
   // Peuplement du milieu
   ecosysteme.getMilieu().peupler(Constantes::NB_BESTIOLES_INIT);

   /*
   Grégaire    :  Orange

   Kamikaze    :  Red

   Multiple    :  Purple

   Peureuse    :  Light Blue

   Prévoyante  :  Green
   */

   // mise en route de la simulation
   ecosysteme.run();

   return 0;
}
