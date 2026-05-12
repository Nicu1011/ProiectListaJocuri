#ifndef JOC_H_
#define JOC_H_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "valuta.h"
#include "tag.h"

#define FORMAT_LISTA_R "%49s %49s %49s %d %d %d %d-%d-%d %d-%d-%d %d-%d-%d %d_%d_%d %f %f "
#define FORMAT_LISTA_W "%49s %49s %49s %1d %2d %2d %02d-%02d-%04d %02d-%02d-%04d %02d-%02d-%04d %04d_%02d_%02d %6.2f %6.2f "
#define FORMAT_TAG "%d "
#define FORMAT_TAGLAST "%d"

typedef enum{
	NUME,
	DEZVOLTATOR,
	PUBLICANT,
	FAVORIT,
	CLASAMENT,
	NOTA,
	DATA_LANSARE,
	DATA_PRIMU_JOC,
	DATA_ULTIM_JOC,
	TIMPJUCAT,
	SPATIU_NECESAR,
	PRET,

	NR_PARAMETRI
} PARAMETRIJOC;
extern const char* NUMEPARAMETRI[NR_PARAMETRI];

struct timp{
	int ore;
	int min;
	int sec;
};
typedef struct timp TIMP;

struct data{
	int an;
	int luna;
	int zi;
};
typedef struct data DATA;

struct jocvideo{
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

};
typedef struct jocvideo JOCVIDEO;

struct nodjoc{
	JOCVIDEO joc;
	struct nodjoc* next;
	struct nodjoc* prev;

};
typedef struct nodjoc NODJOC;

//functii lista
void insert(NODJOC** start, const JOCVIDEO joc);
void insert_at(NODJOC** start, const JOCVIDEO joc, const int at_index);
void delete_at(NODJOC** start, const int at_index);
void afisare(NODJOC* start);
void afisare_inv(NODJOC* start);
NODJOC* nodget_last(NODJOC* start);
JOCVIDEO* pget_at(NODJOC* start, const int at_index);
JOCVIDEO get_at(NODJOC* start, const int at_index);
void set_at(NODJOC** start, JOCVIDEO joc, const int at_index);
int get_num(NODJOC* start);
void free_lista(NODJOC** start);

//functii pentru sortare
void sortare(NODJOC** start, int (*f)(JOCVIDEO, JOCVIDEO));
void swap_joc(JOCVIDEO* j1, JOCVIDEO* j2);
int cmp_nume(JOCVIDEO j1, JOCVIDEO j2);
int cmp_fav(JOCVIDEO j1, JOCVIDEO j2);
int cmp_nota(JOCVIDEO j1, JOCVIDEO j2);
int cmp_clasament(JOCVIDEO j1, JOCVIDEO j2);
int cmp_timpjucat(JOCVIDEO j1, JOCVIDEO j2);

//functii diverse
void swap_char(char* c1, char* c2);
void int_to_text(const int n, char* text);
void float_to_text(float n, const int zecimale, char* text);


#endif /* JOC_H_ */
