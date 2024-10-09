main : main.cpp Constantes.o Aquarium.o Bestiole.o Milieu.o Carapace.o Camouflage.o Yeux.o Oreilles.o \
        Nageoires.o ComportementGregaire.o ComportementKamikaze.o ComportementPrevoyante.o \
        ComportementMultiple.o ComportementPeureuse.o BestioleBuilder.o Director.o Builder.h
	
	g++ -Wall -std=c++14 -o main main.cpp Constantes.o Aquarium.o Bestiole.o Milieu.o Carapace.o Camouflage.o Yeux.o Oreilles.o \
	    Nageoires.o ComportementGregaire.o ComportementKamikaze.o ComportementPrevoyante.o \
	    ComportementMultiple.o ComportementPeureuse.o BestioleBuilder.o Director.o -I . -lX11 -lpthread
# main : main.cpp Aquarium.o Bestiole.o Milieu.o Carapace.o Camouflage.o Yeux.o Oreilles.o \
#         Nageoires.o ComportementGregaire.o ComportementKamikaze.o ComportementPrevoyante.o \
#         ComportementMultiple.o ComportementPeureuse.o 
	
# 	g++ -Wall -std=c++14 -o main main.cpp Aquarium.o Bestiole.o Milieu.o Carapace.o Camouflage.o Yeux.o Oreilles.o \
# 	    Nageoires.o ComportementGregaire.o ComportementKamikaze.o ComportementPrevoyante.o \
# 	    ComportementMultiple.o ComportementPeureuse.o -I . -lX11 -lpthread

Constantes.o : Constantes.h Constantes.cpp
	g++ -Wall -std=c++14  -c Constantes.cpp -I .

Aquarium.o : Aquarium.h Aquarium.cpp
	g++ -Wall -std=c++14  -c Aquarium.cpp -I .

Milieu.o : Milieu.h Constantes.h Bestiole.h Director.h Milieu.cpp
	g++ -Wall -std=c++14  -c Milieu.cpp -I .

Camouflage.o : Constantes.h Camouflage.h Camouflage.cpp
	g++ -Wall -std=c++14  -c Camouflage.cpp -I .

Carapace.o : Constantes.h Carapace.h Carapace.cpp
	g++ -Wall -std=c++14  -c Carapace.cpp -I .

Oreilles.o : Constantes.h Oreilles.h Oreilles.cpp
	g++ -Wall -std=c++14  -c Oreilles.cpp -I .

Yeux.o : Constantes.h Yeux.h Yeux.cpp
	g++ -Wall -std=c++14  -c Yeux.cpp -I .

Nageoires.o : Constantes.h Nageoires.h Nageoires.cpp
	g++ -Wall -std=c++14  -c Nageoires.cpp -I .

ComportementPeureuse.o : Constantes.h Comportement.h ComportementPeureuse.h ComportementPeureuse.cpp
	g++ -Wall -std=c++14  -c ComportementPeureuse.cpp -I .

ComportementGregaire.o : Comportement.h ComportementGregaire.h ComportementGregaire.cpp
	g++ -Wall -std=c++14  -c ComportementGregaire.cpp -I .

ComportementKamikaze.o : Constantes.h Comportement.h ComportementKamikaze.h ComportementKamikaze.cpp
	g++ -Wall -std=c++14  -c ComportementKamikaze.cpp -I .

ComportementPrevoyante.o : Comportement.h ComportementPrevoyante.h ComportementPrevoyante.cpp
	g++ -Wall -std=c++14  -c ComportementPrevoyante.cpp -I .

ComportementMultiple.o : Constantes.h Comportement.h ComportementMultiple.h ComportementMultiple.cpp
	g++ -Wall -std=c++14  -c ComportementMultiple.cpp -I .

Bestiole.o : Constantes.h Oreilles.h Yeux.h Nageoires.h Carapace.h Camouflage.h Bestiole.h Bestiole.cpp
	g++ -Wall -std=c++14  -c Bestiole.cpp -I .

BestioleBuilder.o : Builder.h BestioleBuilder.h BestioleBuilder.cpp
	g++ -Wall -std=c++14  -c BestioleBuilder.cpp -I .

Director.o : Builder.h Director.h Director.cpp
	g++ -Wall -std=c++14  -c Director.cpp -I .

clean:
	rm -rf *.o main

