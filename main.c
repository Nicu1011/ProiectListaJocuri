/*
Proiect inceput pe 07.04.2026
Total timp pierdut p'aici: ~10h
*/

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
	VALUTA pr, conv;
	VALUTA* curs_valutar = citire_curs_valutar("abc.txt");

	pr.RON = 200.0, pr.EUR=0, pr.USD=0, pr.GBP=0;
	printf("%.2f %.2f %.2f %.2f\n", pr.RON, pr.EUR, pr.USD, pr.GBP);
	conv = convertire_valuta_p(curs_valutar, pr, RON);
	printf("%.2f %.2f %.2f %.2f\n", conv.RON, conv.EUR, conv.USD, conv.GBP);

	float eur_pret = 60.00;
	float ron_pret;
	ron_pret = convertire_valuta_f(curs_valutar, eur_pret, EUR, RON);
	printf("%.2f\n", ron_pret);
	fflush(stdout);

    return 0;
}
