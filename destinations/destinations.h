#include <stdlib.h> 
#include <stdio.h>
#include "../Modele/modele.h"

/*@requires: currentDestination a des contraintes
@assigns:
@ensures: change les destinations du voyageur en suivant les contraintes de la destination du deuxième argument*/

void traitementContrainte(voyageur currentVoyageur, destination currentDestination, croisieres mesCroisieres, croisiere currentCroisiere, destination*);

/*@ requires:
@ assigns:
@ ensures: traite la liste des voyageurs pour toutes les croisières et leur affecte les destinations*/

void traitementDestinations(croisieres cs);

/*
@ requires
@ assigns
@ ensures Renvoie une destination libre pour la croisiere et la zone en question et NULL si aucune destination n'est libre
*/

destination destinationLibre(croisiere,int zone);
