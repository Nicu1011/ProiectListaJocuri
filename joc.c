#include <stdio.h>
#include <stdlib.h>
#include "joc.h"

const char *NUMETAG[NR_TAGURI] = {
		"SINGLEPLAYER",
		"MULTIPLAYER",
		"PVE",
		"PVP",
		"COOP",
		"FIRST_PERSON",
		"THIRD_PERSON",
		"RPG",
		"MMORPG",
		"OPEN_WORLD",
		"SOULS_LIKE",
		"FANTASY",
		"DIFFICULT",
		"ATMOSPHERIC",
		"SANDBOX",
		"SHOOTER",
		"FPS",
		"SURVIVAL",
		"STORY_RICH"
};

int n_list = 0;

JOCVIDEO* citire_lista_jocuri(char* str_file){
	int i = 0;

	JOCVIDEO lista_jocuri[MAX_LIST];

	FILE* fin = fopen(str_file, "r");
	if(!fin){
		printf("Lista jocurilor personale nu a fost gasita!\n");

		printf("Se va folosi lista jocurilor implicite.\n");
		fflush(stdout);

		fin = fopen("lista_jocuri_default.txt", "r");

		if(!fin){
			printf("Eroare la citirea listei pentru jocuri! (fisier)\n");
			fflush(stdout);
			exit(2);
		}
	}

	while(feof(fin) == 0){

		fscanf(fin, "%s %s %s %d %d %d",
				lista_jocuri[i].nume, lista_jocuri[i].dezvoltator, lista_jocuri[i].publicant,
				&lista_jocuri[i].favorit, &lista_jocuri[i].clasament, &lista_jocuri[i].nota);

		fscanf(fin, "%d-%d-%d %d-%d-%d %d-%d-%d",
				&lista_jocuri[i].data_lansare.zi, &lista_jocuri[i].data_lansare.luna, &lista_jocuri[i].data_lansare.an,
				&lista_jocuri[i].data_primu_joc.zi, &lista_jocuri[i].data_primu_joc.luna, &lista_jocuri[i].data_primu_joc.an,
				&lista_jocuri[i].data_ultim_joc.zi, &lista_jocuri[i].data_ultim_joc.luna, &lista_jocuri[i].data_ultim_joc.an);

		fscanf(fin, "%d:%d:%d",
				&lista_jocuri[i].timp_jucat.ore, &lista_jocuri[i].timp_jucat.min, &lista_jocuri[i].timp_jucat.sec);

		fscanf(fin, "%f %f",
				&lista_jocuri[i].spatiu_necesar, &lista_jocuri[i].pret.EUR);
		i++;
	}
	n_list = i;

	JOCVIDEO* p_lista = lista_jocuri;

	return p_lista;
}
