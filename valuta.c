#include "valuta.h"

const char* NUMEMONEDA[NR_MONEDE] = {
		"RON",
		"EUR",
		"USD",
		"GBP"
};

void citeste_fisier_curs(float curs[NR_MONEDE][NR_MONEDE], const char* nume_fisier)
{
	if(nume_fisier == NULL)
		nume_fisier = "cursuri_valutare_default.txt";

	FILE* fin = fopen(nume_fisier, "r");
	if(fin == NULL)
		exit(1);

	for(int i=0; i<NR_MONEDE; i++)
		for(int j=0; j<NR_MONEDE; j++)
			fscanf(fin, "%f", &curs[i][j]);

	fclose(fin);
}

void convertire_valuta(const float curs[NR_MONEDE][NR_MONEDE], float val[NR_MONEDE], const MONEDA moneda_principala)
{
	float de_conv = val[moneda_principala];
	for(int i=0; i<NR_MONEDE; i++)
		val[i] = de_conv * curs[moneda_principala][i];
}
