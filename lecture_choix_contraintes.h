#define MAX_LIGNE 100
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Modele/modele.h"
#include <assert.h>
 
void creer_contraintes();
char** str_split(char* a_str, const char a_delim);
void choixVoyageurs(info_voyageur v,croisieres cs);
