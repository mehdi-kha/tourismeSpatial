#include <string.h>
#include <stdlib.h>
 
#include "modele.h"

int NB_ZONE=6;
int NB_CROISIERE=3;

typedef struct contrainte* contrainte;
typedef struct destination _destination;
typedef struct croisiere _croisiere;
typedef struct croisieres _croisieres;
typedef struct maillon* maillon;

struct contrainte {
  destination dest_suivante; 
  contrainte next_contrainte;
};


struct croisieres
{
  croisiere* liste;
  int size; /*Nombre de croisières*/
  int current; /*Indice de la croisière courante*/
};


struct maillon //Liste de destinations
{
  destination dest;
  struct maillon* next;
};


struct croisiere
{
  int indice; /*Indice de la croisière dans le tableau des quotas de croisières d'une destination*/
  char* nom;
  int quota;
  int quota_total; //Inchangé, nombre total de places
  maillon* destination; /*Tableau de maillons, une case par zone*/
  voyageur* v_selectionnes;
  int parcours_v_selectionnes; //Indice dans v_selectionnes du voyageur traité
};

struct destination
{
  char* nom;
  int* quota;
  contrainte contrainte;
};


croisiere get_first_croisiere_org(croisieres cs) //Retourne la première croisiere organisée, celle en case 1 de cs
{
  if(cs->size<2)
    return NULL;
  cs->current=1;
  return cs->liste[1];
}

croisiere get_next_croisiere(croisieres cs)
{
  (cs->current)++;
  if (cs->size == cs->current)
    {
      return NULL;
    }
  return cs->liste[cs->current];
}

int get_quota(croisiere c, destination d)
{
  return (d->quota)[c->indice];
}

int get_quota_croisiere(croisiere c)
{
  return c->quota;
}

int push_voyageur_croisiere(voyageur v, croisiere c)
{
  if(c->quota <= 0)
    return 1;
  if( c->v_selectionnes == NULL ) //Si c n'a été attribuée à aucun voyageur
    c->v_selectionnes=calloc(c->quota_total, sizeof(voyageur));
  c->v_selectionnes[(c->quota_total) - (c->quota)]=v;
  (c->quota)--;
  return 0;
}

voyageur get_first_voyageur(croisiere c)
{
  if(c->v_selectionnes ==NULL) //si aucun voyageur n'a été attribué à cette croisiere
    return NULL;
  c->parcours_v_selectionnes=0; //Indice du premier voyageur
  return ((c->v_selectionnes)[0]);
}
voyageur get_next_voyageur(croisiere c)
{
  (c->parcours_v_selectionnes)++; //Passage à l'indice suivant
  if ((c->parcours_v_selectionnes) > (c->quota_total - c->quota))
    {
      return NULL;
    }
  return ((c->v_selectionnes)[c->parcours_v_selectionnes]);
}

croisieres newCroisieres()
{
  croisieres cs = malloc(sizeof(_croisieres));
  cs->liste=NULL;
  cs->size=0;
  cs->current=0;
  return cs;
}



croisiere newCroisiere(char* nom, int quota, croisieres cs)
{
  croisiere c = malloc(sizeof(_croisiere));
  c->nom=nom;
  c->quota_total=quota;
  c->quota=quota;
  c->destination=NULL;
  c->v_selectionnes=NULL;
  c->parcours_v_selectionnes=0;
	
  cs->liste=realloc(cs->liste, ((cs->size)+1)*sizeof(croisiere));
  cs->liste[cs->size]=c;
  cs->size=cs->size+1;
	
  return c;
}

destination search_destination(char* nom, croisieres cs){
  int i,z;
  for (i = 0; i < cs->size ; i++) //Parcours de toutes les croisières
    {
      croisiere c = cs->liste[i]; //Récupération de la croisière qui correspond
      if( c->destination != NULL){ //Vérification du fait qu'il y ait des destinations affectées à la croisière
	       for (z = 0; z < NB_ZONE ; z++)
	       {
	           maillon m = (c->destination)[z];
				
	           while(m != NULL){
	             if( 0 == strcmp( (m->dest)->nom, nom))
		              return m->dest;
	             m=m->next;
	           }
	       }
      }
    }
  return NULL;
}


void pushDestination(char* nomdest,int taille_chaine, int quota, croisiere c, int zone, croisieres cs)
{
  zone=zone-1; //Décalage d'indice dans le tableau de destinations
  destination d = search_destination(nomdest,cs);
  if(d==NULL){ //S'il la destination n'est pas déjà attribuée
    d = malloc(sizeof(_destination));
    d->quota=malloc(sizeof(int)*(NB_CROISIERE+1));
    d->nom=malloc(taille_chaine*sizeof(char));
    int i;
    strcpy(d->nom,nomdest);
  }
  d->quota[c->indice]=quota;
  maillon m = malloc(sizeof(struct maillon));
  if(c->destination == NULL){
    c->destination = calloc( NB_ZONE, sizeof(maillon));

  }
  m->next=(c->destination)[zone];
  m->dest=d;
  (c->destination)[zone]=m;
	
}

croisiere getCroisiere(char* nom, croisieres cs)
{
  int i;
  for (i = 0; i < cs->size; i++)
    {
      if(0==strcmp(((cs->liste)[i])->nom, nom))
	        return (cs->liste)[i];
    }
  return NULL;
}

char* get_destination_nom(destination d)
{
  return d->nom;	
}

char* get_croisiere_nom(croisiere c)
{
  return c->nom;
}

/********************************************************************************************************************************************/

struct info_voyageur
{
  voyageur first;
  voyageur current;
};

typedef struct info_voyageur _info_voyageur;

struct voyageur
{
  char* nom;
  char* prenom;
  int priorite;
  croisiere* croisiere;
  destination* choix_destination;
  destination* destination_affectee;
  voyageur suivant;
  int nb_choix;
};

typedef struct voyageur _voyageur;

info_voyageur infoVoyageur()
{
  info_voyageur iv = (info_voyageur) malloc(sizeof( _info_voyageur ));
  iv->first=NULL;
  iv->current=NULL;
  return iv;
}

voyageur info_voyageurFirst(info_voyageur iv)
{
  iv->current=iv->first;
  return iv->first;
}


voyageur info_voyageurNext(info_voyageur iv)
{

  iv->current = (iv->current)->suivant;
  return iv->current;

}


void addVoyageur_tri_prio(info_voyageur iv, char* nom, int taille_nom, char* prenom, int taille_prenom, int priorite)
{
  voyageur v=iv->first; //Récupération du premier voyageur
  voyageur ancien = v; //Ancien temporaire
  while(  v != NULL && priorite <= v->priorite)
    {
      ancien=v;
      v=v->suivant;
    }
  voyageur new = malloc(sizeof( struct voyageur ));
  new->nom=malloc(taille_nom*sizeof(char));
  int i;
  for(i=0;i<taille_nom;i++)
    new->nom[i]=nom[i];

  new->prenom=malloc(taille_prenom*sizeof(char));
  for(i=0;i<taille_prenom;i++)
    new->prenom[i]=prenom[i];

  new->priorite=priorite;
  new->croisiere=NULL;
  new->choix_destination=NULL;
  new->destination_affectee=NULL;
  new->suivant=v;
  new->nb_choix=0;


  if(iv->first == NULL)
    iv->first=new;
  else
    if(priorite > (iv->first)->priorite)
      iv->first=new;
    else
      ancien->suivant=new;
}

void addChoice(voyageur v, char** tab_croisiere, char** tab_destination, int taille_tab_croisiere, int taille_tab_destination, croisieres cs )
{
  int i;
  v->nb_choix=taille_tab_croisiere;
  v->croisiere=malloc(taille_tab_croisiere*sizeof(croisiere));
  for (i = 0; i < taille_tab_croisiere; i++)
    {
      croisiere c = getCroisiere(tab_croisiere[i],cs);  //ici vérif NULL
      (v->croisiere)[i]=c;
    }

  v->choix_destination=malloc(NB_ZONE*NB_CROISIERE*sizeof(destination));
  for (i = 0; i < NB_CROISIERE; i++)
    {
		
      int z;
      for (z = 0; z < NB_ZONE; z++)
	     {
	       destination d = search_destination(tab_destination[i*NB_ZONE+z],cs);
	       (v->choix_destination)[i*NB_ZONE+z]=d;
	     }
    }
}

voyageur get_voyageur(char* nom, char* prenom, info_voyageur iv)
{
  voyageur v=iv->first;
  while(v != NULL)
    {
      if (strcmp(nom,v->nom)==0 && strcmp(prenom,v->prenom)==0)
	{
	  return v;
	}
      v=v->suivant;
    }
  return NULL;
}

char* get_nom_voyageur(voyageur v)
{
  return v->nom;
}

char* get_prenom_voyageur(voyageur v)
{
  return v->prenom;
}


int get_priorite(voyageur v){
  return v->priorite;
}

void supprDestAtt(destination currentDestination, croisiere currentCroisiere, croisieres mesCroisieres){
  int z = getZone(currentDestination, mesCroisieres); //Numéro de la zone à modifier
  currentDestination -> quota[z-1] = (currentDestination -> quota[z-1])+1;
}

int getZone(destination d, croisieres cs){
  int i,z;
  for (i = 0; i < cs->size ; i++)
    {
      croisiere c = cs->liste[i];
      if( c->destination != NULL){
	for (z = 0; z < NB_ZONE ; z++)
	  {
	    maillon m = (c->destination)[z];
				
	    while(m != NULL){
	      if( (m->dest)==d )
		return z;
	      m=m->next;
	    }
	  }
      }
    }
  return 0;
}

croisiere* get_choix_croisiere(voyageur v, int* taille)
{
  *taille = v->nb_choix;
  return v->croisiere;
}

destination* get_choix_destination(voyageur v)
{
  return v->choix_destination;
}


void attribDest(voyageur v, destination d, int zone){
  int i;
  if(NULL==v->destination_affectee)
    v->destination_affectee=malloc(NB_ZONE*sizeof(destination));

  v->destination_affectee[zone-1]=d;

}

destination* get_att_destination(voyageur v){
  return v->destination_affectee;
}

destination* get_dest_zone(croisiere crois, int zone){

  if(NULL==crois->destination){
    return NULL;
  }
  if(NULL==crois->destination[zone-1]){
    return NULL;
  }
  maillon m=crois->destination[zone-1];
  int taille = get_nb_dest_crois(crois, zone);
  destination* tab = malloc(taille*sizeof(struct destination));
  int i;
  for(i=0; m!=NULL ;i++){
    tab[i]=m->dest;
    m=m->next;

  }

  return tab;
}

int get_nb_dest_crois(croisiere crois, int zone){
  int i;

  if(NULL==crois->destination){
    return 0;
  }
  if(NULL==crois->destination[zone-1]){
    return 0;
  }
  maillon m=crois->destination[zone-1];

  for(i=0; m!=NULL ;i++){
    m=m->next;

  }

  return i;
}

/*--------- CONTRAINTES ---------*/

void pushContrainte(destination nomDestination, destination destinationContrainte){

  contrainte c = malloc(sizeof(struct contrainte)); /*Nouvelle contrainte*/
  contrainte cNext = getContrainte(nomDestination); /*Contrainte suivante s'il y en a une*/
  c->dest_suivante = destinationContrainte;
  c->next_contrainte = cNext;
  nomDestination->contrainte = c;
    
}


void deleteContrainte(destination nomDestination, destination destinationContrainte){

  contrainte cTemp = getContrainte(nomDestination); /*Pointeur sur la prochaine contrainte*/
  contrainte cTemp2 = cTemp; /*"Suit" cTemp pour effectuer la liaison lors de la suppression*/
  
  while (cTemp->dest_suivante != destinationContrainte){
    cTemp2 = cTemp;
    cTemp = cTemp->next_contrainte; /*Passage à la contrainte suivante si la destination contrainte assocée à cTemp n'est pas celle cherchée*/
  }

  if(NULL != cTemp){
    cTemp2->next_contrainte = cTemp->next_contrainte;
    free(cTemp);
  }
  

}

int isContrainte(destination nomDestination){
  if(getContrainte(nomDestination) != NULL)
    return 1;
  return 0;
}

contrainte getContrainte(destination nomDestination){
  return nomDestination->contrainte;
}

destination getDestinationContrainte(contrainte c){
  return c->dest_suivante;
}

contrainte getNextContrainte(contrainte c){
  return c->next_contrainte;
}

void update_quota_croisiere(croisiere c)
{
  int nb = get_nb_dest_crois(c, 1);
  destination* ds = get_dest_zone(c, 1);
  int i,sum=0;
  for (i = 0; i < nb; i++)
  {
    sum=sum+get_quota(c, ds[i]);

  }
  c->quota=sum;
  c->quota_total=sum;
  free(ds);
}