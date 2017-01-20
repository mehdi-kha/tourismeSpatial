#include <stdlib.h>
#include <stdio.h>
#include "lecture_voyageur.h" 

void lecture_voyageur(info_voyageur iv)

{
	FILE *fichier=fopen("./Sujet/priorites.csv","r");

	char *nom=NULL,*prenom=NULL,*priorite=NULL;
	int c=0,k=0,i=0,j=0,m=0;
 	while((c=fgetc(fichier))!= EOF)
	{
		if((c!=',') && (c!='\n') && (k%3)==0)
		{
			nom=(char*)realloc(nom,(i+1)*sizeof(char));
            		nom[i++]=c;
		}
        	else if((c!=',') && (c!='\n') && (k%3)==1)
        	{
            		prenom=(char*)realloc(prenom,(j+1)*sizeof(char));
			prenom[j++]=c;
		}
        	else if((c!=',') && (c!='\n') && (k%3)==2)
        	{
            		priorite=(char*)realloc(priorite,(m+1)*sizeof(char));
			priorite[m++]=c;
		}
		else if((c==','))
		{
            		k++;
		}
		else if(c=='\n'){
			nom[i]='\0';
            		prenom[j]='\0';
			priorite[m]='\0';
            		addVoyageur_tri_prio(iv, nom, i, prenom,j ,  atoi(priorite));

			m=0;
            		k=0;
            		i=0;
            		j=0;
		}

	}
    free(nom);
    free(prenom);
    free(priorite);
    fclose(fichier);
}
