#include "lecture_choix_contraintes.h"


void creer_contraintes(croisieres cs)
{ 
    FILE* fichier=fopen("./Sujet/contraintes.csv","r");
    if(fichier==NULL){
        printf("erreur : fopen : creer_contraintes\n");
        exit(1);
    }
    /*char temp[MAX_LIGNE];
    char une_destination[MAX_LIGNE];
    int j=0,i=0;
    char *les_destinations[2];
    while(fgets(temp,MAX_LIGNE,fichier))
    {
        /*while(temp[j]!='\n')
        {
            if(temp[j]!=',')
            {
                une_destination[j]=temp[j];
                j++;
            }
            else
            {
                une_destination[j]='\0';
                les_destinations[i]=malloc(sizeof(char)*strlen(une_destination));
                strcpy(les_destinations[i],une_destination);
                i++;
                j=0;
            }
        }*/
        //pushContrainte(search_destination(les_destinations[0],cs),search_destination(les_destinations[1],cs));
        //i=0;
    //}
    //fclose(fichier);
}

char** str_split(char* a_str, const char a_delim)
{
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}

void choixVoyageurs(info_voyageur v,croisieres cs)
{
    char temp[1000];
    FILE* fichier=fopen("./Sujet/souhaits_voyageurs.csv","r");
    if(fichier==NULL){
        printf("erreur : fopen : in choixVoyageurs\n");
        exit(1);
    }
    int i=0,j=0;
    char *nom,*prenom;
    char* croisiere_p[100];
    char *croisiere_l[100];
    while(fgets(temp,1000,fichier))
    {
        char** infos=str_split(temp,',');
        nom=infos[0];
        prenom=infos[1];
        voyageur vo=get_voyageur(nom,prenom,v);
        if(fichier==NULL){
            printf("erreur : voyageur lu inconnu : in choixVoyageurs");
            exit(1);
        }
        if(vo==NULL){
            printf("erreur : voyageur inconnu : in choixVoyageurs");
        }

        croisiere_p[0]=infos[2];
        croisiere_p[1]=infos[3];
        int j=0;
        croisiere_l[j]=infos[4];
        while(croisiere_l[j])
        {
            j++;
            croisiere_l[j]=infos[j];
        }
        addChoice(vo, croisiere_p, croisiere_l, 2,24 ,cs);
    }
}
