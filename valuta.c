#include <stdlib.h>
#include <stdio.h>
#include "valuta.h"

VALUTA* citire_curs_valutar(char* str_file)
{
	int i = 0;

	VALUTA* moneda = (VALUTA*)malloc(sizeof(VALUTA) * NR_MONEDE);
	FILE* fin = fopen(str_file, "r");
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
	return moneda;
}

VALUTA convertire_valuta_p(VALUTA* curs_valutar, VALUTA val, MONEDA moneda_principala){
	VALUTA val_convertit;

	switch(moneda_principala){
	case RON:
		val_convertit.RON = val.RON;
		val_convertit.EUR = val.RON * curs_valutar[moneda_principala].EUR;
		val_convertit.USD = val.RON * curs_valutar[moneda_principala].USD;
		val_convertit.GBP = val.RON * curs_valutar[moneda_principala].GBP;
		break;

	case EUR:
		val_convertit.EUR = val.EUR;
		val_convertit.RON = val.EUR * curs_valutar[moneda_principala].RON;
		val_convertit.USD = val.EUR * curs_valutar[moneda_principala].USD;
		val_convertit.GBP = val.EUR * curs_valutar[moneda_principala].GBP;
		break;

	case USD:
		val_convertit.USD = val.USD;
		val_convertit.RON = val.USD * curs_valutar[moneda_principala].RON;
		val_convertit.EUR = val.USD * curs_valutar[moneda_principala].EUR;
		val_convertit.GBP = val.USD * curs_valutar[moneda_principala].GBP;
		break;
	case GBP:

		val_convertit.GBP = val.GBP;
		val_convertit.RON = val.GBP * curs_valutar[moneda_principala].RON;
		val_convertit.EUR = val.GBP * curs_valutar[moneda_principala].EUR;
		val_convertit.USD = val.GBP * curs_valutar[moneda_principala].USD;
		break;
	default:
		printf("Problema la convertirea valutei! (p_switch");
		exit(4);
	}

	return val_convertit;
}

float convertire_valuta_f(VALUTA* curs_valutar, float val, MONEDA moneda_in, MONEDA moneda_out){
	float val_conv;

	switch(moneda_out){
	case RON:
		val_conv = val * curs_valutar[moneda_in].RON;
		break;
	case EUR:
		val_conv = val * curs_valutar[moneda_in].EUR;
		break;
	case USD:
		val_conv = val * curs_valutar[moneda_in].USD;
		break;
	case GBP:
		val_conv = val * curs_valutar[moneda_in].GBP;
		break;
	default:
		printf("Problema la convertirea valutei! (f_switch");
		exit(5);
	}

	return val_conv;
}

