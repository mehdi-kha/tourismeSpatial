#include "croisieres.h" 

void traitementVoyageurs(croisieres cs, info_voyageur iv){
  	voyageur currentVoyageur = info_voyageurFirst(iv);

	int taille=0;
	while(currentVoyageur != NULL) {

		croisiere* choix = get_choix_croisiere(currentVoyageur,&taille); /* taille 2 parce que il y a 2 choix croisieres*/

		if (get_quota_croisiere(choix[0])>0)
		{
			if(push_voyageur_croisiere(currentVoyageur,choix[0])!=0){
				printf("Erreur lors de l'insertion d'un voyageur dans une croisière \n");
			}
		}
		else if (get_quota_croisiere(choix[1])>0)
		{
			if(push_voyageur_croisiere(currentVoyageur,choix[1])!=0){
				printf("Erreur lors de l'insertion d'un voyageur dans une croisière \n");
			}
		}
		else
		{
			if(push_voyageur_croisiere(currentVoyageur,getCroisiere("libre", cs))){
				printf("Erreur lors de l'insertion d'un voyageur dans une croisière \n");
			}
			
		}
		
		currentVoyageur = info_voyageurNext(iv);
}	

}