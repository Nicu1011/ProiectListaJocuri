#include <stdlib.h>
#include <stdio.h>
#include "valuta.h"

pret_t citire_curs_valutar(MONEDA monedaPrincipala)
{
	int i = 0;
	pret_t moneda[NR_MONEDE];
	FILE *fin = fopen("cursuri_valutare.txt", "r");
	if(!fin){
		printf("Cursurile valutare nu au fost gasite!\n");

		printf("Se vor folosi cursurile valutare implicite.\n");
		fflush(stdout);

		fin = fopen("cursuri_valutare_default.txt", "r");

		if(!fin){
			printf("Eroare la citirea cursurilor valutare! (fisier)\n");
			fflush(stdout);
			exit(1);
		}
	}

	while(feof(fin) == 0){
		fscanf(fin, "%f%f%f%f", &moneda[i].RON, &moneda[i].EUR, &moneda[i].USD, &moneda[i].GBP);
		i++;
	}

	fclose(fin);
	return moneda[monedaPrincipala];
}
