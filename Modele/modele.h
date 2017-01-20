typedef struct croisiere* croisiere;
typedef struct croisieres* croisieres;
typedef struct destination* destination; 


typedef struct info_voyageur* info_voyageur;
typedef struct voyageur* voyageur;
typedef struct contrainte* contrainte;

/*______________________________________________________croisiere_________________________________________________________________*/




/*********************création*******************/

/*t
@ assigns un struct croisieres
@ requires
@ ensures Crée une structure contenant les différentes croisières.
*/
croisieres newCroisieres();

/*t
@ assigns un struct croisiere
@ requires
@ ensures Crée une croisière et l'ajoute à cs
*/
croisiere newCroisiere(char* nom, int quota, croisieres cs);

/*t
@ requires taille_chaine>0, zone<nombre de zones existantes
@ assigns Alloue une struct destination si la destination n'existait pas. Alloue un maillon.
@ ensures Ajoute une destination une croisiere
*/
void pushDestination(char* nomdest,int taille_chaine, int quota, croisiere, int zone, croisieres);

/*t
@ assigns Modifie la croisiere
@ requires un voyageur , une croisiere
@ ensures	retourne 0 si le voyageur à été ajouter et decrémente le quota, 1 sinon (si il n'y a plus de place dans la croisiere)
*/
int push_voyageur_croisiere(voyageur, croisiere);

/*******************Parcours*****************/

/*t
@ assigns 
@ requires 
@ ensures retourne la premiere croisiere organisee ou NULL si fin
*/
croisiere get_first_croisiere_org(croisieres);

/*t
@ assigns
@ requires
@ ensures retourne la croisiere organisee suivante et avance d'un pas ou NULL si fin
*/
croisiere get_next_croisiere(croisieres);

/*t
@ assigns
@ requires
@ ensures retourne le premier voyageur d'une croisière ou NULL s'il n'y en a pas
*/
voyageur get_first_voyageur(croisiere);

/*t
@ assigns
@ requires
@ ensures retourne le prochain voyageur d'une croisiere
*/
voyageur get_next_voyageur(croisiere);


/*******************Getter*******************/

/*t
@ assigns
@ requires
@ ensures Retourne le quota d'une croisiere associee à une destination
*/
int get_quota(croisiere, destination);

/*t
@ assigns
@ requires
@ ensures retourne le quota général d'une croisière
*/
int get_quota_croisiere(croisiere);

/*t
@ assigns
@ requires
@ ensures Retourne une croisiere dont le nom est nom
*/
croisiere getCroisiere(char* nom, croisieres cs);


/*t
@ assigns
@ requires
@ ensures retourne le nom d'une destination
*/
char* get_destination_nom(destination);

/*t
@ assigns
@ requires
@ ensures retourne le nom d'une croisiere
*/
char* get_croisiere_nom(croisiere);

/*
@ assigns
@ requires
@ ensures
*/

/*
@ assigns
@ requires
@ ensures
*/

/* TODO TEST */
/* Renvoie un tableau de destination correspondant aux destinations de la zone zone de la croisiere crois*/
/*!!!!!!!!!!!!!!!!!!!!!!!!FREE THE DESTINATION* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
destination* get_dest_zone(croisiere crois, int zone);

/*TODO TEST*/
/* Renvoie le nombre de destinations correspondant aux destinations de la zone zone de la croisiere crois*/
int get_nb_dest_crois(croisiere crois, int zone);

/*t
@ assigns
@ requires
@ ensures Retourne la destination dont le nom est nom
*/
destination search_destination(char* nom, croisieres cs);

/*t
@ assigns
@ requires
@ ensures Update le quota en fonction des destination inséré
*/
void update_quota_croisiere(croisiere c);


/*______________________________________________________________Voyageur_________________________________________________________*/


/**************création**************/

/*t
@ assigns	taille de info_voyageur
@ requires	-
@ ensures	retourne un pointeur vers un info_voyageur vide
*/
info_voyageur infoVoyageur();

/*t
@ assigns	taille de voyageur
@ requires	un voyageur
@ ensures	ajoute un voyageur à la liste chainée info_voyageur
*/
void addVoyageur_tri_prio(info_voyageur,char* nom, int taille_nom, char* prenom, int taille_prenom, int priorite);

/*TODO TEST
@ assigns
@ requires la croisiere existe
@ ensures 
*/
void addChoice(voyageur, char* tab_croisiere[], char* tab_destination[], int taille_tab_croisiere, int taille_tab_destination, croisieres cs );

/***********Parcours**************/

/*t
@ assigns	-
@ requires	un pointeur info_voyageur
@ ensures	retourne un poiteur vers le premier voyageur de la liste et place le voyageur courrant à celui ci.
*/

voyageur info_voyageurFirst(info_voyageur);
/*t
@ assigns	-
@ requires	un pointeur info_voyageur
@ ensures	retourne un poiteur vers le voyageur suivant et place le voyaeur courrant à celui ci, ou retourne NULL et met le current à NULL
*/
voyageur info_voyageurNext(info_voyageur);


/********************Getter*******************/

/*t
@ assigns -
@ requires char* nom,prenom	
@ ensures retourne le voyageur ou NULL si il n'existe pas
*/
voyageur get_voyageur(char* nom, char* prenom, info_voyageur);

/*t
@ assigns -
@ requires un voyageur
@ ensures	retourne le nom du voyageur
*/
char* get_nom_voyageur(voyageur);

/*t
@ assigns -
@ requires un voyageur
@ ensures	retourne le prenom du voyageur
*/
char* get_prenom_voyageur(voyageur);

/*t
@ assigns -
@ requires un voyageur
@ ensures	retourne la pririté du voyageur
*/
int get_priorite(voyageur);

/*TODO RETEST
@ assigns
@ requires
@ ensures retourne un tableau de croisiere choisit de taille "taille"  
*/
croisiere* get_choix_croisiere(voyageur, int* taille);

/*TODO TEST
@ assigns
@ requires
@ ensures Retourne un tableau de destination des choix d'un voyageur
*/
destination* get_choix_destination(voyageur); 

/* TO TEST
@ requires
@ assigns
@ ensures Retourne un tableau de taille NB_ZONE de destinations attribuées au voyageur
 */

destination* get_att_destination(voyageur);

/*	TODO TEST
@ assigns
@ requires
@ ensures Attribue la destination nomDestination au voyageur nomVoyageur
*/
void attribDest(voyageur nomVoyageur, destination nomDestination, int zone);

/*
@ requires
@ assigns
@ ensures Augmente le quota disponible pour la croisière currentCroisiere et la destination currentDestination
*/

void supprDestAtt(destination currentDestination, croisiere currentCroisiere, croisieres);

/*t
@ assigns
@ requires
@ ensures Retourne la zone d'une destination
*/
int getZone(destination, croisieres);

/* -------------------------------------------------------Contraintes-------------------------------------------------------*/


/*
@ assigns Un struct contrainte
@ requires
@ ensures Ajoute une contrainte de destination à une destination, et la renvoie
*/

void pushContrainte(destination nomDestination, destination destinationContrainte);

/*
@ requires
@ assigns
@ ensures Supprime une contrainte d'une destination
*/

void deleteContrainte(destination nomDestination, destination destinationContrainte);

/*
@ requires
@ assigns
@ ensures Renvoie 1 si la destination a une destination contrainte ou 0 sinon
*/

int isContrainte(destination nomDestination);

/*
@ requires
@ assigns
@ ensures Retourne la premiere contrainte de la liste de contraintes de nomDestination
*/

contrainte getContrainte(destination nomDestination);

/*
@ requires
@ assigns
@ ensures Retourne la destination correspondant à la contrainte
*/

destination getDestinationContrainte(contrainte);

/*
@ requires
@ assigns
@ ensures Renvoie la contrainte suivante
*/

contrainte getNextContrainte(contrainte);
