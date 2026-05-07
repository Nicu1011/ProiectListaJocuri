#ifndef JOC_H_
#define JOC_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "valuta.h"
#include "timp.h"
#include "tag.h"

#define FORMAT_LISTA_R "%49s %49s %49s %d %d %d %d-%d-%d %d-%d-%d %d-%d-%d %d_%d_%d %f %f "
#define FORMAT_LISTA_W "%49s %49s %49s %1d %2d %2d %02d-%02d-%04d %02d-%02d-%04d %02d-%02d-%04d %04d_%02d_%02d %6.2f %6.2f "
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
	int taguri[NR_TAGURI];

	int favorit;
	int clasament;
	int nota;

	DATA data_lansare, data_primu_joc, data_ultim_joc;
	TIMP timp_jucat;

	float spatiu_necesar; //GB

	VALUTA pret, pret_timp_jucat;

} JOCVIDEO;

struct nodjoc{
	JOCVIDEO joc;
	struct nodjoc* next;
	struct nodjoc* prev;
};
typedef struct nodjoc NODJOC;

//functii lista
void insert(NODJOC** start, JOCVIDEO joc);
void insert_at(NODJOC** start, const JOCVIDEO joc, const int at_index);
void delete_at(NODJOC** start, const int at_index);
void afisare(NODJOC* start);
void afisare_inv(NODJOC* start);
JOCVIDEO* pget_at(NODJOC* start, const int at_index);
JOCVIDEO get_at(NODJOC* start, const int at_index);
void set_at(NODJOC** start, JOCVIDEO joc, const int at_index);
int get_num(NODJOC* start);
void free_lista(NODJOC** start);

//functii pentru fisiere
void creaza_fisier(NODJOC** start);
#endif /* JOC_H_ */
