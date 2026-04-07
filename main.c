#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "joc.h"

void get_timp(){
	time_t timp = time(NULL);
	struct tm *timpLocal = localtime(&timp);

	printf("Data: %02d-%02d-%d\n", timpLocal->tm_mon + 1, timpLocal->tm_mday, timpLocal->tm_year + 1900);
	printf("Ora: %02d:%02d:%02d\n", timpLocal->tm_hour, timpLocal->tm_min, timpLocal->tm_sec);
	fflush(stdout);
}

void meniu_principal()
{
	printf("--------------- Meniu ------------------\n");
	printf("\n");
	printf("0. Iesire\n");
	printf("1. Meniu lista\n");
	printf("2. Acesarea backup-urilor listelor\n");
	printf("\n");
	printf("------------------------------------------");
}

void meniu_lista()
{
	printf("------------- MeniuListe ----------------\n");
	printf("\n");
	printf("1. Salvare lista\n");
	printf("2. Afisare lista\n");
	printf("3. Adaugare in lista\n");
	printf("4. Stergere din lista\n");
	printf("\n");
	printf("------------------------------------------\n");
}

int main()
{
	citire_lista_jocuri("lista_jocuri.txt");
	int i=0;
	for(i=0; i<lista_n; i++)
	{
		printf("%s %s %d-%d-%d\n",
				lista_jocuri[i].nume, lista_jocuri[i].dezvoltator,
				lista_jocuri[i].data_lansare.zi, lista_jocuri[i].data_lansare.luna, lista_jocuri[i].data_lansare.an);
	}
    return 0;
}
