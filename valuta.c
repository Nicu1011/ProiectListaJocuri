#include <stdlib.h>
#include <stdio.h>
#include "valuta.h"

void fcitire_curs_valutar(const char* nume_fisier, float curs[NR_MONEDE][NR_MONEDE])
{
	int i = 0;

	FILE* fin = fopen(nume_fisier, "r");
	if(!fin)
	{
		printf("Cursurile valutare specificate nu au fost gasite!\n");

		printf("Se vor folosi cursurile valutare implicite...\n");
		fflush(stdout);

		fin = fopen("cursuri_valutare_default.txt", "r");
		if(!fin)
		{
			printf("Eroare la citirea cursurilor valutare! (fisier)\n");
			fflush(stdout);
			exit(1);
		}
	}

	while(feof(fin) == 0)
	{
		for(int j=0; j<NR_MONEDE; j++)
		{
			fscanf(fin, "%f", &curs[i][j]);
		}
		i++;
	}
	fclose(fin);
}

void convertire_valuta_v(const CURS curs, const VALUTA val, VALUTA val_conv, const MONEDA moneda_principala)
{
	for(int i=0; i<NR_MONEDE; i++)
		val_conv[i] = val[i] * curs[moneda_principala][i];

}

float convertire_valuta_f(const CURS curs, const float val, const MONEDA moneda_in, const MONEDA moneda_out)
{
	float val_conv;
	val_conv = val * curs[moneda_in][moneda_out];
	return val_conv;
}
