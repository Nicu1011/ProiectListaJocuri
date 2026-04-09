/*
Proiect inceput pe 07.04.2026
Total timp pierdut p'aici: ~13h
*/

#include <stdio.h>
#include "joc.h"
#include "timp.h"
//
//void meniu_principal()
//{
//	printf("--------------- Meniu ------------------\n");
//	printf("\n");
//	printf("0. Iesire\n");
//	printf("1. Meniu lista\n");
//	printf("2. Acesarea backup-urilor listelor\n");
//	printf("\n");
//	printf("------------------------------------------");
//}
//
//void meniu_lista()
//{
//	printf("------------- MeniuListe ----------------\n");
//	printf("\n");
//	printf("1. Salvare lista\n");
//	printf("2. Afisare lista\n");
//	printf("3. Adaugare in lista\n");
//	printf("4. Stergere din lista\n");
//	printf("\n");
//	printf("------------------------------------------\n");
//}

int main()
{
	LISTAJOC lista_joc = fcitire_lista_jocuri("lista_jocuri_default.txt");

	CURS curs;
	fcitire_curs_valutar("a.txt", curs);
	for(int i=0; i<NR_MONEDE; i++)
	{
		for(int j=0; j<NR_MONEDE; j++)
			printf("%6.2f ", curs[i][j]);
		printf("\n");
		fflush(stdout);
	}

	fcreare_lista_jocuri("test.txt", lista_joc);

	printf("%s_%s_%d", creaza_timestamp_data(FORMAT_DATA), creaza_timestamp_ora(FORMAT_ORA), f_citire_nr_linii("lista_jocuri_default.txt"));

    return 0;
}
