CC = gcc  

all: test

./Modele/modele.o: ./Modele/modele.h
creer_destinations.o: creer_destinations.h ./Modele/modele.h
lecture_voyageur.o: lecture_voyageur.h
main.o: ./Modele/modele.h creer_destinations.h lecture_voyageur.h ./destinations/destinations.h ./croisieres/croisieres.h lecture_choix_contraintes.h

./destinations/destinations.o: ./destinations/destinations.h
./croisieres/croisieres.o: ./croisieres/croisieres.h

lecture_choix_contraintes.o: lecture_choix_contraintes.h

clean:
	rm *.o

test: main.o ./Modele/modele.o creer_destinations.o lecture_voyageur.o ./destinations/destinations.o ./croisieres/croisieres.o lecture_choix_contraintes.o
	$(CC) $^ -o $@
