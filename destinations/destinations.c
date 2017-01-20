#include "destinations.h"
 


void traitementDestinations(croisieres cs){

  destination* choixDestinations = NULL; /*Tableau de taille 6 qui contient les 6 choix de destinations du voyageur traité pour une zone*/

  croisiere currentCroisiere = get_first_croisiere_org(cs); /*Va servir pour le parcours de toutes les croisieres*/
  voyageur currentVoyageur = get_first_voyageur(currentCroisiere); //Va servir pour le parcours de tous les voyageurs pour chaque croisière

  destination* destAtt = NULL; /*Contient les destinations attribuées*/
  int i;
  
  while(currentCroisiere != NULL){ /*Traitement de toutes les croisières*/

    while(currentVoyageur != NULL){ /*Traitement de chaque voyageur*/

      choixDestinations = get_choix_destination(currentVoyageur); /*Tableau des choix de destinations d'un voyageur*/

      //Vérification des quotas et affectation des destinations

      for(i=0;i<6;i++){ //Pour chaque zone
	if(get_quota(currentCroisiere, choixDestinations[i])>0){ /*Cas où il reste de la place pour la destination pour la croisiere en question*/
	  attribDest(currentVoyageur, choixDestinations[i], i+1); //i+1 est le numéro de la zone
	}
	
	else{
	  attribDest(currentVoyageur, destinationLibre(currentCroisiere,i+1),i+1);
	}
      }

      /*Verification des contraintes*/

      destAtt = get_att_destination(currentVoyageur);
      for(i=0;i<6;i++){
	if(getContrainte(destAtt[i])!=NULL)//S'il y a une contrainte pour une destination
	  traitementContrainte(currentVoyageur, destAtt[i], cs, currentCroisiere, destAtt);
      }
      
      currentVoyageur = get_next_voyageur(currentCroisiere); //Traitement du voyageur suivant
    }
    
    currentCroisiere = get_next_croisiere(cs); /*Passage à la croisière suivante*/

  }


}




void traitementContrainte(voyageur currentVoyageur, destination currentDestination, croisieres cs, croisiere currentCroisiere, destination* destAtt){
  
  contrainte currentContrainte = getContrainte(currentDestination); //Contrainte correspondant à la destination currentDestination
  destination destContrainte = getDestinationContrainte(currentContrainte); //Destination correspondant à la contrainte currentContrainte
  int zoneContrainte;
  while(currentContrainte!=NULL){//Tant qu'il y a des contraintes
    zoneContrainte = getZone(destContrainte, cs);
    supprDestAtt(destAtt[zoneContrainte-1], currentCroisiere, cs);//Incrémentation du nombre de places disponibles pour la destination
    attribDest(currentVoyageur, destContrainte, zoneContrainte); //modification de l'affectation des destinations
    currentContrainte = getNextContrainte(currentContrainte);
  }
}


destination destinationLibre(croisiere curCroisiere, int curZone){
  
  int sizeTabDest = get_nb_dest_crois(curCroisiere, curZone); /*Nombre de destinations pour la zone curZone de curCroisiere */
  destination* tabDest; //Contient les destinations de la zone curZone
  tabDest = get_dest_zone(curCroisiere, curZone);
  destination d = tabDest[0];
  int i = 0;
  while(get_quota(curCroisiere, d)==0 && i<sizeTabDest){
    i=i+1;
    d = tabDest[i];
  }
  if(get_quota(curCroisiere, d)!=0) /*Si il y a de la place dans d pour la croisière curCrois*/
    return d;
  return NULL;
  
}
