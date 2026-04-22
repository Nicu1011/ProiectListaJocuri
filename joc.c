#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "joc.h"

int f_citire_nr_linii(const char* nume_fisier)
{
	if(!nume_fisier)
		return 0;

	int n = 0;

	FILE* fin = fopen(nume_fisier, "r");
	if(!fin)
	{
		printf("Eroare la deschiderea fisierului pentru a citi nr de linii!");
		exit(5);
	}
	fseek(fin, 0, SEEK_SET);

	int c;

	while((c = fgetc(fin)) != EOF)
		if(c == '\n')
			n++;

	if(c == EOF)
		n++;

	fclose(fin);

	return n;
}

LISTAJOC fcitire_lista_jocuri(const char* nume_fisier)
{
	if(!nume_fisier)
		nume_fisier = "lista_jocuri_default.txt";

	int i = 0, j;
	LISTAJOC lista = {0};

	lista.n = f_citire_nr_linii(nume_fisier);
	JOCVIDEO* lista_jocuri = (JOCVIDEO*)malloc(sizeof(JOCVIDEO) * lista.n);

	FILE* fin = fopen(nume_fisier, "r");
	if(!fin){
		printf("Eroare la citirea listei pentru jocuri! (fisier)\n");
		fflush(stdout);
		exit(2);
	}

	while(feof(fin) == 0){

		fscanf(fin, FORMAT_LISTA_R, lista_jocuri[i].nume, lista_jocuri[i].dezvoltator, lista_jocuri[i].publicant,
				&lista_jocuri[i].favorit, &lista_jocuri[i].clasament, &lista_jocuri[i].nota,
				&lista_jocuri[i].data_lansare.zi, &lista_jocuri[i].data_lansare.luna, &lista_jocuri[i].data_lansare.an,
				&lista_jocuri[i].data_primu_joc.zi, &lista_jocuri[i].data_primu_joc.luna, &lista_jocuri[i].data_primu_joc.an,
				&lista_jocuri[i].data_ultim_joc.zi, &lista_jocuri[i].data_ultim_joc.luna, &lista_jocuri[i].data_ultim_joc.an,
				&lista_jocuri[i].timp_jucat.ore, &lista_jocuri[i].timp_jucat.min, &lista_jocuri[i].timp_jucat.sec,
				&lista_jocuri[i].spatiu_necesar, &lista_jocuri[i].pret[EUR]
				);
		for(j = 0; j < NR_TAGURI; j++)
				fscanf(fin, FORMAT_TAG, &lista_jocuri[i].taguri[j]);
		i++;
	}

	lista.jocuri = lista_jocuri;
	lista.n = i;

	fclose(fin);
	return lista;
}

void fcreare_lista_jocuri(const char* nume_fisier, const LISTAJOC lista)
{
	int i, j;
	int n = lista.n;
	JOCVIDEO* lista_jocuri = lista.jocuri;

	FILE* fout = fopen(nume_fisier, "w");
	if(!fout){
		printf("Eroare la crearea listei pentru jocuri! (fisier)\n");
		fflush(stdout);
		exit(3);
	}

	for(i = 0; i < n; i++)
	{
		fprintf(fout, FORMAT_LISTA_W,
				lista_jocuri[i].nume, lista_jocuri[i].dezvoltator, lista_jocuri[i].publicant,
				lista_jocuri[i].favorit, lista_jocuri[i].clasament, lista_jocuri[i].nota,
				lista_jocuri[i].data_lansare.zi, lista_jocuri[i].data_lansare.luna, lista_jocuri[i].data_lansare.an,
				lista_jocuri[i].data_primu_joc.zi, lista_jocuri[i].data_primu_joc.luna, lista_jocuri[i].data_primu_joc.an,
				lista_jocuri[i].data_ultim_joc.zi, lista_jocuri[i].data_ultim_joc.luna, lista_jocuri[i].data_ultim_joc.an,
				lista_jocuri[i].timp_jucat.ore, lista_jocuri[i].timp_jucat.min, lista_jocuri[i].timp_jucat.sec,
				lista_jocuri[i].spatiu_necesar, lista_jocuri[i].pret[EUR]
				);

		for(j = 0; j < NR_TAGURI; j++)
			fprintf(fout, FORMAT_TAG, lista_jocuri[i].taguri[j]);
		if(i+1 < n)
			fprintf(fout, "\n");
	}

	fclose(fout);
}

void eliberare_lista_jocuri(LISTAJOC lista)
{
	free(lista.jocuri);
	lista.n = 0;
}
