# BE Simulation d'écosysteme

## Description du projet 

Le projet permet la simulation d'un écosystème rempli de Bestioles capable de **proliférer** et de **mourir**. Chaque Bestiole a un **comportement**  et a (ou non) différents **capteurs** (Yeux, ... ) et différents **accessoires**. Les Bestioles se déplacent au sein de l'environnement et elles peuvent intéragir entre elles.

## Download and usage

Clonez ou téléchargez le reopsitory Github. Avant de lancer la simulation, vous devez installer la librarie `X11`, nécéssaire pour l'affichage de l'interface graphique. Placez-vous dans le répertoire où se trouve le code, puis dans le terminal tapez les commandes suivantes:

    sudo apt-get install libx11-dev 

Vous pouvez ensuite lancer la simulation à l'aide des commandes:

`Commandes linux & MacOS:`

    make
    ./main 

Remarque : la commande './main' est à utiliser à chaque fois que vous souhaitez relancer une simulation.

## Accès au données de la simulation

Les données de la simulation sont retranscrites dans un fichier .csv
ainsi que ses constantes associées.

Le format des deux fichiers est le suivant: 

*constantes_ + date de lancement de la simulation + .csv*

*suivi_aquarium_ + date de lancement de la simulation + .csv*

## Modification des constantes de la simulation 

L'utilisateur peut changer les constantes de la simulation en modifiant le fichier *Constantes.cpp*. 
NB : il faut de nouveau utiliser la commande 'make' dans l'invite de commande pour que les changements soient pris en compte. 

Les differentes constantes modifiables sont présentées dans l'Annexe

## Durant la simulation 

L'utilisateur peut utiliser son clavier pour agir sur les bestioles : 
- appuyer sur 'a' ou 'A' pour ajouter une bestiole (aux propriétés (plus à ce sujet plus bas) aléatoires)
- appuyer sur 'c' ou 'C' puis saisir au clavier l'identifiant d'une bestiole pour changer son comportement (nouveau comportement aléatoire)
- appuyer sur 'm' ou 'M' puis saisir au clavier l'identifiant d'une bestiole pour la faire mourir.
NB : pour que l'appui sur une touche ait un effet, il faut sélectionner la fenêtre de simulation. Donc après avoir saisi un identifiant sur l'invite de commandes, ne pas oublier de resélectionner la fenêtre de simulation pour continuer à pouvoir agir dessus.  

Lors de l'appui sur n'importe quelle touche du clavier, l'identifiant de chaque bestiole apparaît sur la simulation. 
Pour quitter la simulation appuyer sur "Echap". 

## Annexe

### Les Bestioles

Véritables stars de la simulation elles partagent toutes des attributs communs qu'importe leur comportement, leurs capteurs ou encore leur accessoires. Les Bestioles sont des entités capables de naître par génération spontanée, par du clonage. 

- Constantes associées : 

        const double NAISSANCE_PROBA                        = 0.01;
        const double CLONAGE_PROBA                          = 0.01;

        const bool NAISSANCE_SPONTANEE                      = false;
        const bool CLONAGE                                  = false;

Cela étant, nos chères bestioles ne sont pas immortelles et nous leur avons prévues soit de mourir de vieillesse ou par collision dans d'atroces souffrances...

- Constantes associées : 

        const double BESTIOLE_MIN_AGE                       = 500;
        const double BESTIOLE_MAX_AGE                       = 1500; 
        const bool MORT_PAR_VIEILLESSE                      = false;
        const bool MORT_PAR_COLLISION                       = true;
        const double BESTIOLE_PROBA_MORT_COLLISION          = 0.3;
Notons qu'on laisse le choix à l'utilisateur de faire pénéter la mort dans l'environment...

Les bestioles apparaissent de manière déterminée à l'initialisation, ont une taille et une vitesse aussi déterminées.

- Constantes associées :

        const double NB_BESTIOLES_INIT                      = 10;

        const double BESTIOLE_AFF_SIZE                      = 12.;
        const double BESTIOLE_MAX_VITESSE                   = 8.;


### Les Comportements 
Les Bestioles peuvent avoir un comportement parmi les 5 comportements disponibles dans la simulation: 

Comportement **Grégaire**: 

Une bestiole, dite **grégaire**, ajuste sa direction sur la direction moyenne des bestioles environnantes.
- Représentation: Bestiole de couleur **Orange**

 -   Constante associée              
 
    const double GREG_PROP                              = 0;

Comportement **Peureuse**: 

Lorsque le nombre de bestioles autour d’une bestiole, dite **peureuse**, devient trop important, celle-ci fuit à vive allure dans la direction opposée avant de reprendre sa vitesse de croisière.

- Représentation: Bestiole de couleur **Bleu clair**

 -   Constantes associées            
 
    const int    PEUREUSE_MAX_VOISINS                   = 2;
    const double PEUREUSE_ACC_FACTEUR                   = 5.;
    const int    PEUREUSE_ACC_DUREE                     = 15;
    
    const double PEUR_PROP                              = 1;


Comportement **Kamikaze**: 

Une bestiole, dite **kamikaze**, est attirée par la bestiole la plus proche et tente de l’attaquer en cherchant à provoquer une collision.
- Représentation: Bestiole de couleur **Rouge**


 -   Constantes associées            
 
    const double KAMIKAZE_ACC_FACTEUR                   = 1.7;
    const int    KAMIKAZE_ACC_DUREE                     = 200;
    
    const double KAM_PROP                               = 0;



Comportement **Prévoyante**: 

Une bestiole, dite **prévoyante**, estime les trajectoires des bestioles autour d’elle et ajuste sa trajectoire pour éviter d’ ́eventuelles collisions.
- Représentation: Bestiole de couleur **Vert**

 -   Constante associée           
 
    const double PREV_PROP                              = 0;



Comportement **Multiples**: 

une bestiole, dite à personnalités **multiples**, adopte successivement d’autres comportements choisis aléatoirement au cours du temps. Néanmoins, elle reste une bestiole à personnalités multiples.

- Représentation: Bestiole de couleur **Violet** mais sa tête a la couleur de son comportement actuel.  (Gregaire, Kamikaze, Peureuse, Prévoyante )

 -   Constantes associées            
 
    const double MULT_PROP                              = 0;


### Les Capteurs
Les bestioles peuvent (ou pas) être dotées d'un ou plusieurs capteurs disponibles dans la simulation à savoir des Yeux et des Oreilles qui leur permettront de détecter plus ou moins efficacement les autres bestioles aux alentours. 

Capteur  **Yeux**: 

- Représentation: la bestiole a des antennes.

 -   Constantes associées            
 
    const double YEUX_RANGE_MAX                         = 100.; 
    const double YEUX_ANGLE_MAX                         = M_PI;
    const double YEUX_DETECTION_MAX                     = 0.8;

    const double YEUX_RANGE_MIN                         = 100.; 
    const double YEUX_ANGLE_MIN                         = M_PI / 4;
    const double YEUX_DETECTION_MIN                     = 0.4;
    
    const double YEUX_PROBA                             = 1;



Capteur  **Oreilles**: 

- Représentation: la bestiole a des pics autour de son corps.

 -   Constantes associées            
 
    const double OREILLES_RANGE_MAX                     = 50.; 
    const double OREILLES_DETECTION_MAX                 = 0.8;

    const double OREILLES_RANGE_MIN                     = 50; 
    const double OREILLES_DETECTION_MIN                 = 0.8;
    
    const double OREILLES_PROBA                         = 1;


### Les Accessoires
Les bestioles peuvent (ou pas) avoir un ou plusieurs Accessoires disponibles dans la simulation à savoir une **Carapace**, qui réduit la vitesse des bestioles mais augmente leur résistance, un **Camouflage**, qui rend la détection des bestioles plus difficile par leurs pairs, et des **Nageoires** qui améliore la vitesse des bestioles.

Capteur  **Carapace**: 

- Représentation: la bestiole a un rond noir sur son corps.

 -   Constantes associées:            
 
    const double CARAPACE_MORT_REDUC_MAX                = 5.;
    const double CARAPACE_VITESSE_REDUC_MAX             = 3.;
    
    const double CARAPACE_PROBA                         = 0;

    // imposed
    const double CARAPACE_VITESSE_REDUC_MIN             = 1.; 
    const double CARAPACE_MORT_REDUC_MIN                = 1.; 

Capteur  **Camouflage**: 

- Représentation: la bestiole est plus transparente.

 -   Constantes associées:            
 
    const double CAMOUFLAGE_MIN                         = 0.2;
    const double CAMOUFLAGE_MAX                         = 0.8;
    
    const double CAMOUFLAGE_PROBA                       = 0;

Capteur  **Nageoires**: 

- Représentation: la bestiole a de nageoires.

 -   Constantes associées:            
 
    const double VITESSE_BOOST_MIN                      = 1.;
    const double VITESSE_BOOST_MAX                      = 2.5;
    
    const double NAGEOIRES_PROBA                        = 0;


