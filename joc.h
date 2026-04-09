#ifndef JOC_H_
#define JOC_H_


#include "valuta.h"
#include "tag.h"

#define FORMAT_LISTA_R "%s %s %s %d %d %d %d-%d-%d %d-%d-%d %d-%d-%d %d_%d_%d %f %f "
#define FORMAT_LISTA_W "%20s %20s %20s %1d %2d %2d %02d-%02d-%04d %02d-%02d-%04d %02d-%02d-%04d %04d_%02d_%02d %6.2f %6.2f "
#define FORMAT_TAG "%d "

typedef struct{
	int ore;
	int min;
	int sec;

} TIMP;

typedef struct{
	int an;
	int luna;
	int zi;

} DATA;

typedef struct{
	char nume[50];
	char dezvoltator[50], publicant[50];
	int taguri[NR_TAGURI];//index -> ENUM cu indexul tagului
	// valoare in sine e 0 daca nu are tag si 1 daca are acel tag

	int favorit;
	int clasament;
	int nota;

	DATA data_lansare, data_primu_joc, data_ultim_joc;
	TIMP timp_jucat;

	float spatiu_necesar; //GB

	VALUTA pret, pret_timp_jucat;

} JOCVIDEO;

typedef struct{
	JOCVIDEO* jocuri;
	int n;
} LISTAJOC;

#define MAX_LIST 50

int f_citire_nr_linii(const char* nume_fisier);

LISTAJOC fcitire_lista_jocuri(const char* nume_fisier);
//citeste un fisier cu numele 'nume_fisier' si returneaza un pointer catre un vector de JOCVIDEO
//de asemenea salveaza si in n_list cate valori a gasit in fisier
void fcreare_lista_jocuri(const char* nume_fisier, const LISTAJOC lista);
//creaza un fisier cu numele 'nume_fisier'


LISTAJOC calc_pret_timp(LISTAJOC lista);
//calculeaza pretul pe timpul jucat si returneaza lista rezultat;
#endif /* JOC_H_ */
