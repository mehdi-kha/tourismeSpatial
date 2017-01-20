#include <stdlib.h>
#include <stdio.h>
#include "creer_destinations.h"
#include "lecture_voyageur.h"
#include "./Modele/modele.h"
#include "lecture_voyageur.h"
#include "./destinations/destinations.h"
#include "./croisieres/croisieres.h"
#include "lecture_choix_contraintes.h"


int main(void){

croisieres cs = newCroisieres();
creer_destinations("./Sujet/destinations.csv","libre",cs);
creer_destinations("./Sujet/croisiere_planetes.csv","planetes",cs);
creer_destinations("./Sujet/croisiere_vie.csv","vie",cs);
creer_destinations("./Sujet/croisiere_satellites.csv","satellites",cs);


/* TEST
croisiere tc1 = get_first_croisiere_org(cs);
printf("%s\n",get_croisiere_nom(tc1));
croisiere tc2 = get_next_croisiere(cs);
printf("%s\n",get_croisiere_nom(tc2));
croisiere tc3 = get_next_croisiere(cs);
printf("%s\n",get_croisiere_nom(tc3));


destination d = search_destination("Pluton",cs);
if(d==NULL)
	printf("KO\n");
else{
int q = get_quota(tc1, d);
printf("%d\n",q);
}
*/

info_voyageur iv=infoVoyageur();
lecture_voyageur(iv);


/*voyageur v1 = info_voyageurFirst(iv);
printf("%s - %d | ", get_nom_voyageur(v1),get_priorite(v1));
while(v1 = info_voyageurNext(iv))
	printf("%s - %d | ", get_nom_voyageur(v1),get_priorite(v1));

*/
choixVoyageurs(iv, cs);

int taille=0;

voyageur v1 = info_voyageurFirst(iv);
printf("%s - %d\n", get_nom_voyageur(v1),get_priorite(v1));

croisiere* choix = get_choix_croisiere(v1,&taille);
int i;
for(i=0;i<taille;i++){
	if(choix[i]==NULL)
		printf("err\n");
	printf("%s - %d ||", get_croisiere_nom(choix[i]) ,get_quota_croisiere(choix[i]));
}

croisiere c = getCroisiere("libre", cs); /*Va servir pour le parcours de toutes les croisieres*/

printf("%s %d\n",get_croisiere_nom(c),get_quota_croisiere(c));

creer_contraintes(cs); //Mehdi SegFault soit c'est ton code soit celui de steve. Fleme de lire ton code pour débogé. !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

traitementVoyageurs(cs, iv);

c = getCroisiere("libre", cs); /*Va servir pour le parcours de toutes les croisieres*/

printf("%s %d\n",get_croisiere_nom(c),get_quota_croisiere(c));

voyageur cv = get_first_voyageur(c); //Va servir pour le parcours de tous les voyageurs pour chaque croisière
if(cv==NULL)
	printf("nop\n");
printf("%s - %d\n", get_nom_voyageur(cv),get_priorite(cv));

while(cv = get_next_voyageur(c)){
	printf("%s - %d\n", get_nom_voyageur(cv),get_priorite(cv));
}
traitementDestinations(cs); //Mehdi SegFault soit c'est ton code soit celui de steve. Fleme de lire ton code pour débogé. !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


printf("Fin\n");

}
