#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "modele.h"

int main(void){

	croisieres cs = newCroisieres();
	int qc1 = 5;
	int qc2=2;
	croisiere clibre = newCroisiere("Libre", 0, cs);

	croisiere tcnone = get_first_croisiere_org(cs);

	if( tcnone==NULL )
		printf("ok\n");
	else
		printf("ko\n");

	croisiere c1 = newCroisiere("Suck my dick", qc1, cs);
	croisiere c2 = newCroisiere("Suck my cock", qc2, cs);


	int test=strcmp(get_croisiere_nom(c2),"Suck my cock");
	if( test==0)
		printf("ok\n");
	else
		printf("ko\n");

	/*test si bien ajouter*/
	croisiere g = getCroisiere("Suck my cock", cs);
	if(c2==g)
		printf("ok\n");
	else
		printf("ko\n");

	/*test si renvoit NULL if not existe*/
	g = getCroisiere("Suck my", cs);
	if(NULL==g)
		printf("ok\n");
	else
		printf("ko\n");


	if(NULL == search_destination("random",cs))
		printf("ok\n");
	else
		printf("ko\n");


	pushDestination("d1.1", 2 , c1, 1, cs);

	if( 0==strcmp(get_destination_nom(search_destination("d1.1",cs)),"d1.1"))
		printf("ok\n");
	else
		printf("ko\n");

	if( NULL == search_destination("dnot",cs))
		printf("ok\n");
	else
		printf("ko\n");


	pushDestination("d1.2", 3 , c1, 1, cs);
	pushDestination("d2", 5 , c1, 2, cs);
	pushDestination("d3", 5 , c1, 3, cs);
	pushDestination("d4", 5 , c1, 4, cs);

	if(  0==strcmp(get_destination_nom(search_destination("d3",cs)),"d3"))
		printf("ok\n");
	else
		printf("ko\n");

	int q = get_quota(c1, search_destination("d2",cs));
	if( q==5 )
		printf("ok\n");
	else
		printf("ko\n");

	q = get_quota(c1, search_destination("d1.2",cs));
	if( q==3 )
		printf("ok\n");
	else
		printf("ko\n");

	pushDestination("d1.1", 1 , c2, 1, cs);
	pushDestination("d1.3", 2 , c2, 1, cs);

	q = get_quota(c2, search_destination("d1.1",cs));
	if( q==1 )
		printf("ok\n");
	else
		printf("ko\n");

	int z = getZone(search_destination("d2",cs),cs);
	if( z==2 )
		printf("ok\n");
	else
		printf("ko\n");

	z = getZone(search_destination("drandom",cs),cs);
	if( z==0 )
		printf("ok\n");
	else
		printf("ko\n");

	z = getZone(search_destination("d1.2",cs),cs);
	if( z==1 )
		printf("ok\n");
	else
		printf("ko\n");


	croisiere tc1 = get_first_croisiere_org(cs);

	if( tc1==c1 )
		printf("ok\n");
	else
		printf("ko\n");

	croisiere tc2 = get_next_croisiere(cs);

	if( tc2==c2 )
		printf("ok\n");
	else
		printf("ko\n");

	croisiere tcnull = get_next_croisiere(cs);

	if( tcnull==NULL )
		printf("ok\n");
	else
		printf("ko\n");
	
	printf("Voyageur :\n");

	info_voyageur iv=infoVoyageur();

	addVoyageur_tri_prio(iv, "MARCHAND", "damien", 10);
	addVoyageur_tri_prio(iv, "MARCHANDISE", "guy", 15);
	addVoyageur_tri_prio(iv, "MARCHANDE", "sophie", 12);
	addVoyageur_tri_prio(iv, "MARCHE", "toto", 2);

	voyageur v = get_voyageur("MARCHAND", "damien", iv);

	if( 0==strcmp("MARCHAND", get_nom_voyageur(v)))
		printf("ok\n");
	else
		printf("ko\n");

	if( 0==strcmp("damien", get_prenom_voyageur(v)))
		printf("ok\n");
	else
		printf("ko\n");

	int tprio = get_priorite(v);

	if( tprio == 10)
		printf("ok\n");
	else
		printf("ko\n");

	v = get_voyageur("MARCHANDISE", "guy", iv);

	if( 0==strcmp("MARCHANDISE", get_nom_voyageur(v)))
		printf("ok\n");
	else
		printf("ko\n");

	if( 0==strcmp("guy", get_prenom_voyageur(v)))
		printf("ok\n");
	else
		printf("ko\n");

	tprio = get_priorite(v);

	if( tprio == 15)
		printf("ok\n");
	else
		printf("ko\n");

	printf("PARCOUR\n");
	voyageur v1 = info_voyageurFirst(iv);
	if( 0==strcmp("MARCHE", get_nom_voyageur(v1)))
		printf("ok\n");
	else
		printf("ko\n");

	voyageur v2 = info_voyageurNext(iv);

	if( 0==strcmp("MARCHAND", get_nom_voyageur(v2)))
		printf("ok\n");
	else
		printf("ko\n");
	voyageur v3 = info_voyageurNext(iv);

	if( 0==strcmp("MARCHANDE", get_nom_voyageur(v3)))
		printf("ok\n");
	else
		printf("ko\n");
	voyageur v4 = info_voyageurNext(iv);
	if( 0==strcmp("MARCHANDISE", get_nom_voyageur(v4)))
		printf("ok\n");
	else
		printf("ko\n");
	voyageur v5 = info_voyageurNext(iv);

	if(v5==NULL)
		printf("ok\n");
	else
		printf("ko\n");





/*************************************CHOIX**********************************************/
	char* chc[2];
	char* chd[12];

	chc[0]="Suck my dick";
	chc[1]="Suck my cock";

	chd[0]="01";
	chd[1]="02";
	chd[2]="03";
	chd[3]="04";

	chd[4]="05";
	chd[5]="06";
	chd[6]="07";
	chd[7]="08";

	chd[8]="09";
	chd[9]="10";
	chd[10]="11";
	chd[11]="12";
	printf("CHOIX\n");
	addChoice( v , chc, chd, 2, 3, cs);
	int t;
	croisiere* cr = get_choix_croisiere(v, &t);
	int i;

	for(i=0;i<t;i++){
		if(0==strcmp(chc[i],get_croisiere_nom(cr[i])))
			printf("ok\n");
		else
			printf("ko\n");
	}


	printf("PARCOUR AFFECTATION\n");

	v = get_first_voyageur(c1);

	if(v==NULL)
		printf("ok\n");
	else
		printf("ko\n");


	push_voyageur_croisiere(v2, c1);
	push_voyageur_croisiere(v3, c1);

	v = get_first_voyageur(c1);

	if(v==v2)
		printf("ok\n");
	else
		printf("ko\n");


	v = get_next_voyageur(c1);

	if(v==v3)
		printf("ok\n");
	else
		printf("ko\n");


	v = get_next_voyageur(c1);

	if(v==NULL)
		printf("ok\n");
	else
		printf("ko\n");

	if(get_quota_croisiere(c1)==qc1-2)
		printf("ok\n");
	else
		printf("ko\n");












	return 0;
}
