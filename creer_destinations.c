
#include "creer_destinations.h"
#include <stdlib.h>
#include <stdio.h> 

void creer_destinations(char* nomfichier, char* nomcroisiere, croisieres cs)

{
	FILE *fichier=fopen(nomfichier,"r");

	croisiere libre=newCroisiere(nomcroisiere, 50, cs);

	char *planete=NULL,*quota=NULL;
	int c=0,compteur=0,k=0,i=0,j=0,z=1,v=1;
 	while((c=fgetc(fichier))!= EOF)
	{
		if((c!=',') && (c!='\n') && (k%2)==0)
		{
			planete=(char*)realloc(planete,(i+1)*sizeof(char));
            		planete[i++]=c;
			v=0;
		}
        	else if((c!=',') && (c!='\n') && (k%2)==1)
        	{
            		quota=(char*)realloc(quota,(j+1)*sizeof(char));
			quota[j++]=c;
			v=0;
		}
		else if((c==',') && (k%2==0))
		{
            		k++;
			v=1;
		}
		else if((c==',') && (k%2!=0))
        	{

			if(v==0){   		
				planete[i]='\0';
            			quota[j]='\0';
            			pushDestination(planete, i,atoi(quota),libre,z,cs);
			}
			z++;
            		k=0;
            		i=0;
            		j=0;
			v=1;
        	}
		else if(c=='\n'){
			if(v==0){
				planete[i]='\0';
            			quota[j]='\0';
            			pushDestination(planete, i, atoi(quota),libre,z,cs);
			}
			z=1;
            		k=0;
            		i=0;
            		j=0;
			v=1;
		}
	}
    free(planete);
    free(quota);
    fclose(fichier);
}
