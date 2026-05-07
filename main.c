/*
Proiect inceput pe 07.04.2026
Total timp pierdut p'aici: ~15h
*/
#include <string.h>
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
	NODJOC* start = NULL;

	JOCVIDEO joc = {"ELDEN2"};

	insert(&start, joc);
	printf("\nN: %d ; ", get_num(start));

	joc = (JOCVIDEO){"ELDEN1"};

	insert(&start, joc);
	printf("\nN: %d ; ", get_num(start));

	joc = (JOCVIDEO){"ELDEN3"};
	insert_at(&start, joc, 2);
	printf("\nN: %d ; ", get_num(start));

	delete_at(&start, 1);//ELDEN2 -> sters
	printf("\nN: %d ; ", get_num(start));

	joc = (JOCVIDEO){"ELDENSET"};
	set_at(&start,joc,2);
	printf("\nN: %d ; \n", get_num(start));

	afisare(start);
	printf("\n");
	afisare_inv(start);

	free_lista(&start);
    return 0;
}
